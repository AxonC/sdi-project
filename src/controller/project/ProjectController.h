#ifndef TREKSTAR_PROJECTCONTROLLER_H
#define TREKSTAR_PROJECTCONTROLLER_H

#include "../../model/project/Project.h"
#include "../../view/project/ProjectView.h"
#include "../../model/project/ProjectInterface.h"
#include "../BaseController.h"

namespace TrekStar
{
    namespace Project
    {
        class ProjectController : public BaseController
        {
        public:
            ProjectController() = default;
            ProjectController(ProjectInterface & model, ViewInterface & view);
            ~ProjectController() = default;

            void ShowAll() override;
            void ShowList() override;

            void UpdateProject();
            void AddNew();

            void ListMaterials();
            void AddMaterial();
            void UpdateMaterials();
            void RemoveMaterial();

            void ListCrew();
            void AddCrew();
            void UpdateCrew();
            void RemoveCrew();

            void ListBoxOfficeReports();
            void AddBoxOfficeReport();
            void RemoveBoxOfficeReport();

            bool ActorExists(std::string & searchCriteria);

        private:
            void UpdateTitle();
            void UpdateSummary();
            void UpdateReleased();
            void UpdatePlayingInTheatres();
            void AddKeywords();
            void UpdateKeyword();
            void LogMaterialAdd(const std::shared_ptr<Material::Material> & material);

            ProjectView* GetView();
            ProjectInterface* GetModel();
        };
    }
}

#endif //TREKSTAR_PROJECTCONTROLLER_H
