#include "pch.h"
#include "Project.h"

#include "BoxOfficeReport.h"
#include "../people/Crew.h"
#include "../material/Material.h"

namespace TrekStar
{
    namespace Project
    {
        Project::Project(const std::string & title, const std::string & summary, bool released, bool playingInTheatres, const std::vector<std::string> & keywords)
        {
            this->title = title;
            this->summary = summary;
            this->released = released;
            this->playingInTheatres = playingInTheatres;
            this->keywords = keywords;
        }

        Project::Project(const SerialisedProject & project)
        {
            this->id = project.id;
            this->title = project.title;
            this->searchableTitle = project.title;
            this->searchableTitle.erase(remove_if(this->searchableTitle.begin(), this->searchableTitle.end(), isspace), this->searchableTitle.end());
            std::transform(this->searchableTitle.begin(), this->searchableTitle.end(), this->searchableTitle.begin(), ::tolower);
            this->summary = project.summary;
            this->released = project.released;
            this->playingInTheatres = project.playingInTheatres;
            this->keywords = project.keywords;
            this->crew = project.crew;
            this->boxOfficeReports = project.boxOfficeReports;
        }

        Project::~Project() = default;

        unsigned int Project::GetId() const
        {
            return this->id;
        }

        std::string Project::GetTitle() const
        {
            return this->title;
        }

        std::string Project::GetSearchableTitle() const
        {
            return this->searchableTitle;
        }

        std::string Project::GetSummary() const
        {
            return this->summary;
        }

        std::vector<std::shared_ptr<Material::Material>> Project::GetMaterials() const
        {
            return materials;
        }

        bool Project::GetReleased() const
        {
            return this->released;
        }

        bool Project::GetPlayingInTheatres() const
        {
            return this->playingInTheatres;
        }

        std::vector<std::string> Project::GetKeywords() const
        {
            return this->keywords;
        }

        std::vector<std::string> Project::GetMaterialFormats() const
        {
            return this->materialFormats;
        }

        void Project::SetTitle(const std::string & title)
        {
            this->title = title;
            this->searchableTitle = title;
            this->searchableTitle.erase(remove_if(this->searchableTitle.begin(), this->searchableTitle.end(), isspace), this->searchableTitle.end());
            std::transform(this->searchableTitle.begin(), this->searchableTitle.end(), this->searchableTitle.begin(), ::tolower);
        }

        void Project::SetSummary(const std::string & summary)
        {
            this->summary = summary;
        }

        void Project::SetReleased(const bool & released)
        {
            this->released = released;
        }

        void Project::SetPlayingInTheatres(const bool & playingInTheatres)
        {
            this->playingInTheatres = playingInTheatres;
        }

        void Project::SetKeywords(const std::vector<std::string> & keywords)
        {
            this->keywords = keywords;
        }

        /**
        *  Set a keyword at a specific index.
        *
        *  @param keywordNo: index of keyword, keyword : keyword to be added
        *  @return void
        */
        void Project::SetKeyword(const unsigned int & keywordNo, const std::string & keyword)
        {
            this->keywords.at(keywordNo) = keyword;
        }

        /**
        *  Add material(s) to a project
        *
        *  @throws std::domain_error
        *  @param materials : collection of materials
        *  @return void
        */
        void Project::AddMaterials(const std::vector<std::shared_ptr<Material::Material>> & materials)
        {
            if ( !this->CanAddMaterial() )
            {
                throw std::domain_error("Material cannot be added.");
            }

            std::string materialFormat;
            for ( const auto & material: materials )
            {
                this->AddMaterialFormat(material->GetFormat());
                this->materials.push_back(material);
            }
        }

        void Project::AddMaterial(const std::shared_ptr<Material::Material> & material)
        {
            if ( !this->CanAddMaterial() )
            {
                throw std::domain_error("Material cannot be added.");
            }

            this->AddMaterialFormat(material->GetFormat());
            this->materials.push_back(material);
        }

        void Project::RemoveMaterial(const std::shared_ptr<Material::Material> & material)
        {
            auto search = std::find(materials.begin(), materials.end(), material);

            if ( search == materials.end() )
            {
                throw std::out_of_range("Material not found.");
            }

            materials.erase(search);
        }

        bool Project::CanAddMaterial() const
        {
            return this->released && !this->playingInTheatres;
        }

        /**
        *  Retrieve Crew Members of a project.
        *
        *  @return All of the crew members associated with a project.
        */
        std::vector<std::shared_ptr<People::Crew>> Project::GetCrew() const
        {
            return this->crew;
        }

        /**
         *  Adds a crew member to the project.
         *
         *  @param crewMember : the crew member to be removed
         *  @return void
         */
        void Project::AddCrew(const std::shared_ptr<TrekStar::People::Crew> & crewMember)
        {
            this->crew.push_back(crewMember);
        }

        /**
         *  Adds a number of crew members to the project.
         *
         *  @param crewMember : the crew member(s) to be removed
         *  @return void
         */
        void Project::AddCrew(const std::vector<std::shared_ptr<People::Crew>> & crew)
        {
            for ( const auto & crewMember: crew )
            {
                this->crew.push_back(crewMember);
            }
        }

        /**
         *  Removes a single crew member from a project.
         *
         *  @param crewMember : the crew member(s) to be removed
         *  @return void
         */
        void Project::RemoveCrew(const std::shared_ptr<TrekStar::People::Crew> & crewMember)
        {
            auto search = std::find(crew.begin(), crew.end(), crewMember);

            if ( search == crew.end() )
            {
                throw std::out_of_range("Crew Member not found.");
            }

            crew.erase(search);
        }

        /**
         *  Mark a project as released enforcing business rules.
         *
         *  @return void
         */
        void Project::ReleaseProject()
        {
            if (this->playingInTheatres)
            {
                throw std::domain_error("A Project cannot be released whilst still playing in theatres.");
            }

            this->released = true;
        }

        SerialisedProject Project::ExportToSerialised() const
        {
            return SerialisedProject
                {
                    this->id,
                    this->title,
                    this->summary,
                    this->released,
                    this->playingInTheatres,
                    this->keywords,
                    this->crew,
                    this->boxOfficeReports
                };
        }

        /**
         *  Determine whether a materials' format is already known to the project.
         *
         *  @param materialFormat : format to be compared
         *  @return bool
         */
        bool Project::MaterialFormatExists(const std::string & materialFormat) const
        {
            return std::find(this->materialFormats.begin(), this->materialFormats.end(), materialFormat) != this->materialFormats.end();
        }

        /**
         *  Adds a material format to the project.
         *
         *  @param materialFormat : format to be added
         *  @return void
         */
        void Project::AddMaterialFormat(const std::string & materialFormat)
        {
            if ( !MaterialFormatExists(materialFormat) )
            {
                this->materialFormats.push_back(materialFormat);
            }
        }

        bool Project::operator>(const Project & project) const
        {
            return this->GetTitle() > project.GetTitle();
        }

        bool Project::operator<(const Project & project) const
        {
            return this->GetTitle() < project.GetTitle();
        }

        bool Project::operator>=(const Project & project) const
        {
            return this->GetTitle() >= project.GetTitle();
        }

        bool Project::operator<=(const Project & project) const
        {
            return this->GetTitle() <= project.GetTitle();
        }

        bool Project::operator==(unsigned int id) const
        {
            return this->GetId() == id;
        }

        bool Project::operator==(const std::string & title) const
        {
            return this->GetSearchableTitle() == title;
        }

        bool Project::operator<(const std::string & title) const
        {
            return this->GetSearchableTitle() < title;
        }

        /**
         *  Retrieve the box office reports for a project.
         *
         *  @return vector of box office reports.
         */
        std::vector<std::shared_ptr<BoxOfficeReport>> Project::GetBoxOfficeReports() const
        {
            return this->boxOfficeReports;
        }

        /**
         *  Add a box office report to the project.
         *
         *  @param report : report to be added
         *  @return void
         */
        void Project::AddBoxOfficeReport(const std::shared_ptr<BoxOfficeReport> & report)
        {
            for(const auto & existingReport: this->boxOfficeReports)
            {
                if (report->GetWeekNumber() == existingReport->GetWeekNumber())
                {
                    throw std::domain_error("Box office reports cannot be added for the same week.");
                }
            }

            this->boxOfficeReports.push_back(report);
        }

        /**
         *  Add box office report(s) to the project.
         *
         *  @throws std::domain_error
         *  @param reports : report(s) to be added
         *  @return void
         */
        void Project::AddBoxOfficeReports(const std::vector<std::shared_ptr<BoxOfficeReport>> & reports)
        {
            for(const auto & report : reports)
            {
                for(const auto & existingReport: this->boxOfficeReports)
                {
                    if (report->GetWeekNumber() == existingReport->GetWeekNumber())
                    {
                        throw std::domain_error("Box office reports cannot be added for the same week.");
                    }
                }
                this->boxOfficeReports.push_back(report);
            }
        }

        /**
         *  Retrieve the total revenue from all box office reports.
         *
         *  @return unsigned long long int : sum of all revenues.
         */
        unsigned long long int Project::GetTotalBoxOfficeRevenue() const
        {
            unsigned long long int initial = 0;

            for (const auto & report: this->boxOfficeReports)
                initial += report->GetRevenue();

            return initial;
        }

        /**
         *  Remove a report from the project.
         *
         *  @throws std::out_of_range
         *  @param boxOfficeReport : report to be removed.
         *  @return void
         */
        void Project::RemoveBoxOfficeReport(const std::shared_ptr<BoxOfficeReport> & boxOfficeReport)
        {
            auto search = std::find(this->boxOfficeReports.begin(), this->boxOfficeReports.end(), boxOfficeReport);

            if ( search == this->boxOfficeReports.end() )
            {
                throw std::out_of_range("Box office report not found.");
            }

            this->boxOfficeReports.erase(search);
        }

        /**
         *  Find whether an actor is employed
         *
         *  @throws std::out_of_range
         *  @param actorName : name of actor to be found.
         *  @return std::shared_ptr<People::Crew>
         */
        std::shared_ptr<People::Crew> Project::FindActor(std::string & actorName)
        {
            std::string parsedName;
            std::transform(actorName.begin(), actorName.end(), actorName.begin(), ::tolower);
            bool found{false};

            for (const auto & crewMember: this->crew)
            {
                std::string name = crewMember->GetName();
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);

                std::string jobTitle = crewMember->GetJobTitle();
                std::transform(jobTitle.begin(), jobTitle.end(), jobTitle.begin(), ::tolower);

                if ( jobTitle == "actor" && name == actorName)
                {
                    found = true;
                    return crewMember;
                }
            }

            if ( ! found ){
                throw std::out_of_range("Actor is not part of project");
            }

            return nullptr;
        }

        void to_json(json & j, const SerialisedProject & project)
        {
            j = json
                {
                    {"id", project.id},
                    {"title", project.title},
                    {"summary", project.summary},
                    {"released", project.released},
                    {"playingInTheatres", project.playingInTheatres},
                    {"keywords", project.keywords}
                };
        }

        void from_json(const json & json, SerialisedProject & project)
        {
            json.at("id").get_to(project.id);
            json.at("title").get_to(project.title);
            json.at("summary").get_to(project.summary);
            json.at("released").get_to(project.released);
            json.at("playingInTheatres").get_to(project.playingInTheatres);
            json.at("keywords").get_to(project.keywords);
        }
    }
}

