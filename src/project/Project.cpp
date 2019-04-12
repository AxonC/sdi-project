#include <iostream>
#include <algorithm>
#include <sstream>     // for std::stringstream

#include "Project.h"

namespace TrekStar {
    namespace Project {
        Project::Project(std::string title, std::string summary, bool released, bool playingInTheatres)
        {
            this->title = title;
            this->summary = summary;
            this->released = released;
            this->playingInTheatres = playingInTheatres;
        }

        Project::Project(std::string & title)
        {
            this->title = title;
        }

        Project::Project(const std::string & name, const std::string & summary, bool released)
        {
            this->title = name;
            this->summary = summary;
            this->released = released;
        }

        Project::Project(const SerialisedProject & project)
        {
            this->title = project.title;
            this->summary = project.summary;
            this->released = project.released;
            this->playingInTheatres = project.playingInTheatres;
        }

        Project::~Project() = default;

        std::string Project::GetTitle() const
        {
            return this->title;
        }

        std::string Project::GetSummary() const
        {
            return this->summary;
        }

        bool Project::GetReleased() const
        {
            return this->released;
        }

        bool Project::GetPlayingInTheatres() const
        {
            return this->playingInTheatres;
        }

        std::pair<std::string, std::string> Project::GetTitleSummary() const
        {
            return {this->title, this->GetSummary()};
        }

        bool Project::CanAddMaterial() const
        {
            return this->released && !this->playingInTheatres;
        }

        bool Project::AddMaterials(const std::shared_ptr<Material::Material> & material)
        {
            if (!this->CanAddMaterial()) {
                return false;
            }

            materials.push_back(material);

            return true;
        }

        void Project::AddMaterials(const std::vector<std::shared_ptr<Material::Material>> & materials)
        {
            if (!this->CanAddMaterial()) {
                throw std::domain_error("Material cannot be added.");
            }

            for(const auto &material: materials)
            {
                this->materials.push_back(material);
            }
        }

        void Project::RemoveMaterial(const std::shared_ptr<Material::Material> & material)
        {
            auto search = std::find(materials.begin(), materials.end(), material);

            if(search == materials.end()) {
                throw std::out_of_range("Material not found.");
            }

            materials.erase(search);
        }

        std::vector<std::shared_ptr<Material::Material>> Project::GetMaterials() const
        {
            return materials;
        }

        void Project::ReleaseProject()
        {
            this->released = true;
        }

        std::vector<std::shared_ptr<People::Crew>> Project::GetCrew() const
        {
            return this->crew;
        }

        void Project::AddCrew(const std::shared_ptr<TrekStar::People::Crew> & crewMember)
        {
            this->crew.push_back(crewMember);
        }

        void Project::RemoveCrew(const std::shared_ptr<TrekStar::People::Crew> & crewMember)
        {
            auto search = std::find(crew.begin(), crew.end(), crewMember);

            if(search == crew.end()) {
                throw std::out_of_range("Crew Member not found.");
            }

            crew.erase(search);
        }

        void from_json(const json & json, SerialisedProject & project)
        {
            json.at("title").get_to(project.title);
            json.at("summary").get_to(project.summary);
            json.at("released").get_to(project.released);
            json.at("playingInTheatres").get_to(project.playingInTheatres);
        }
    }
}

