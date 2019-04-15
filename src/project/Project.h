#ifndef PROJECT_PROJECT_H
#define PROJECT_PROJECT_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "../material/Material.h"
#include "../people/Crew.h"
#include "../lib/json.hpp"

using json = nlohmann::json;
using TrekStar::People::Crew;
using TrekStar::People::SerializedCrew;

namespace TrekStar {
    namespace Project {
        struct SerialisedProject {
            std::string title;
            std::string summary;
            bool released;
            bool playingInTheatres;
            std::vector<std::shared_ptr<Crew>> crew;
        };

        /**
         *  Trekstar Film Project Class
         */
        class Project
        {
        public:
            Project() = default;
            Project(std::string title, std::string summary, bool released, bool playingInTheatres);
            Project(const std::string & title, const std::string & summary, bool released = false);
            explicit Project(std::string & title);
            explicit Project(const SerialisedProject & project);
            ~Project();

            std::string GetTitle() const;

            std::string GetSummary() const;
            bool GetReleased() const;
            bool GetPlayingInTheatres() const;
            void SetSummary(const std::string & contents);

            std::pair<std::string, std::string> GetTitleSummary() const;

            void AddMaterials(const std::vector<std::shared_ptr<Material::Material>> & materials);
            bool AddMaterials(const std::shared_ptr<Material::Material> & material);
            std::vector<std::shared_ptr<Material::Material>> GetMaterials() const;
            void RemoveMaterial(const std::shared_ptr<Material::Material> & material);

            std::vector<std::shared_ptr<People::Crew>> GetCrew() const;
            void AddCrew(const std::shared_ptr<People::Crew> &);
            void AddCrew(const std::vector<std::shared_ptr<Crew>> & crew);
            void RemoveCrew(const std::shared_ptr<People::Crew> &);

            void ReleaseProject();

            SerialisedProject ExportToSerialised() const;

        private:
            bool CanAddMaterial() const;

            std::string title;
            std::string summary;
            std::vector<std::shared_ptr<Material::Material>> materials;
            std::vector<std::shared_ptr<People::Crew>> crew;
            bool released{false};
            bool playingInTheatres{false};
        };


        void to_json(json & j, const SerialisedProject & project);
        void from_json(const json & json, SerialisedProject & project);
    }
}

#endif //PROJECT_PROJECT_H
