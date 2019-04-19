#ifndef PROJECT_PROJECT_H
#define PROJECT_PROJECT_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "../../Model.h"
#include "../../lib/json.hpp"
#include "../people/Crew.h"
#include "../material/Material.h"

using json = nlohmann::json;
using TrekStar::People::Crew;
using TrekStar::People::SerializedCrew;

namespace TrekStar
{
    namespace Project
    {
        struct SerialisedProject
        {
            unsigned int id;
            std::string title;
            std::string summary;
            bool released;
            bool playingInTheatres;
            std::vector<std::string> keywords;
            std::vector<std::shared_ptr<Crew>> crew;
        };

        /**
         *  Trekstar Film Project Class
         */
        class Project: public Model
        {
        private:
            unsigned int id;
            std::string title;
            std::string summary;
            std::vector<std::shared_ptr<Material::Material>> materials;
            bool released = false;
            bool playingInTheatres = false;
            std::vector<std::string> keywords;
            std::vector<std::shared_ptr<People::Crew>> crew;
            bool CanAddMaterial() const;

        public:
            Project() = default;
            Project(const std::string & title, const std::string & summary, bool released, bool playingInTheatres, const std::vector<std::string> & keywords);
            explicit Project(const SerialisedProject & project);
            ~Project();

            unsigned int GetId() const;
            std::string GetTitle() const;
            std::string GetSummary() const;
            std::vector<std::shared_ptr<Material::Material>> GetMaterials() const;
            bool GetReleased() const;
            bool GetPlayingInTheatres() const;
            std::pair<std::string, std::string> GetTitleSummary() const;

            void AddMaterials(const std::vector<std::shared_ptr<Material::Material>> & materials);
            bool AddMaterials(const std::shared_ptr<Material::Material> & material);
            void RemoveMaterial(const std::shared_ptr<Material::Material> & material);

            std::vector<std::shared_ptr<People::Crew>> GetCrew() const;
            void AddCrew(const std::shared_ptr<People::Crew> &);
            void AddCrew(const std::vector<std::shared_ptr<Crew>> & crew);
            void RemoveCrew(const std::shared_ptr<People::Crew> &);

            void ReleaseProject();

            SerialisedProject ExportToSerialised() const;
        };

        void to_json(json & j, const SerialisedProject & project);
        void from_json(const json & json, SerialisedProject & project);
    }
}

#endif //PROJECT_PROJECT_H