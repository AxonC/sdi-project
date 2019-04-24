#include <iostream>

#include "ProjectView.h"
#include "../material/MaterialView.h"
#include "../../controller/material/MaterialController.h"
#include "../../command/CommandHandler.h"
#include "../../command/userInput.h"

using TrekStar::Material::MaterialController;
using TrekStar::Material::MaterialView;

namespace TrekStar
{
    namespace Project
    {
        ProjectView::ProjectView(ProjectInterface& model) : BaseView()
        {
            this->model = &model;
        }

        void ProjectView::PresentAll()
        {
            auto model = this->GetModel();

            std::string released = "no";
            std::string playingInTheatres = "no";

            if ( model->GetReleased() )
            {
                released = "yes";
            }

            if ( model->GetPlayingInTheatres() )
            {
                playingInTheatres = "yes";
            }

            std::cout << std::string(80, '-') << std::endl;
            std::cout << "Project " << std::to_string(model->GetId()) << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            std::cout << "Title               : " << model->GetTitle() << std::endl;
            std::cout << "Summary             : " << model->GetSummary() << std::endl;
            std::cout << "Released            : " << released << std::endl;
            std::cout << "Playing in theatres : " << playingInTheatres << std::endl;

            std::cout << "Keywords            : ";
            if ( model->GetKeywords().empty() )
            {
                std::cout << "No keywords...";
            }
            else
            {
                this->DisplayVectorAsCSV(model->GetKeywords());
            }
            std::cout << std::endl;

            std::cout << "Available on        : ";
            if ( model->GetMaterialFormats().empty() )
            {
                std::cout << "No material formats...";
            }
            else
            {
                this->DisplayVectorAsCSV(model->GetMaterialFormats());
            }
            std::cout << std::endl;
        }

        void ProjectView::PresentList()
        {
            auto model = this->GetModel();

            std::cout << "Title: " << model->GetTitle() << std::endl;
        }

        void ProjectView::PresentKeywords()
        {
            unsigned int counter = 0;
            for ( const auto & keyword: this->GetModel()->GetKeywords() )
            {
                counter++;
                std::cout << "Keyword #" << counter << ": " << keyword << std::endl;
            }
        }

        void ProjectView::PresentMaterialsList()
        {
            for ( const auto & material: this->GetModel()->GetMaterials() )
            {
                MaterialView view(*material);
                MaterialController controller(*material, view);

                controller.ShowList();
            }
        }

        std::string ProjectView::GetNewTitle()
        {
            std::string currentTitle = this->GetModel()->GetTitle();

            if ( currentTitle.empty() )
            {
                std::cout << "Title: ";
            }
            else
            {
                std::cout << "Title [current: " << currentTitle << "]: ";
            }

            return TrekStar::Command::GetStringInput();
        }

        std::string ProjectView::GetNewSummary()
        {
            std::string currentSummary = this->GetModel()->GetSummary();

            if ( currentSummary.empty() )
            {
                std::cout << "Summary: ";
            }
            else
            {
                std::cout << "Summary [current: " << currentSummary << "]: ";
            }

            return TrekStar::Command::GetStringInput();
        }

        bool ProjectView::GetNewReleased()
        {
            std::string released = "no";
            if ( this->GetModel()->GetReleased() )
            {
                released = "yes";
            }

            std::cout << "Released [current: " << released << "]: ";
            return TrekStar::Command::GetBoolInput();
        }

        bool ProjectView::GetNewPlayingInTheatres()
        {
            std::string playingInTheatres = "no";
            if ( this->GetModel()->GetPlayingInTheatres() )
            {
                playingInTheatres = "yes";
            }

            std::cout << "Playing In Theatres [current: " << playingInTheatres << "]: ";
            return TrekStar::Command::GetBoolInput();
        }

        unsigned int ProjectView::GetKeywordNo()
        {
            return TrekStar::Command::GetIndexInput(this->GetModel()->GetKeywords().size(), "Keyword");
        }

        std::string ProjectView::GetNewKeyword(const unsigned int & keywordNo)
        {
            std::cout << "Keyword #" << keywordNo + 1 << " [current: " << this->GetModel()->GetKeywords().at(keywordNo) << "]: ";
            return TrekStar::Command::GetStringInput();
        }

        unsigned int ProjectView::GetUpdateOption()
        {
            TrekStar::Command::CommandHandler commandHandler = TrekStar::Command::CommandHandler (
                    {
                            {1, "Edit Title"},
                            {2, "Edit Summary"},
                            {3, "Edit Released"},
                            {4, "Edit Playing In Theatres"},
                            {5, "Edit Existing Keywords"},
                            {6, "Cancel"}
                    },
                    "Update Project"
            );

            commandHandler.displayCommands();
            int commandInput = commandHandler.getUserInput();
            commandHandler.clearConsole();

            return commandInput;
        }

        unsigned int ProjectView::GetMaterialSelection()
        {
            unsigned int materialSelection;

            std::cout << "Material ID: ";
            std::cin >> materialSelection;

            return materialSelection;
        }

        ProjectInterface* ProjectView::GetModel()
        {
            return dynamic_cast<ProjectInterface*>(this->model);
        }

        void ProjectView::DisplayVectorAsCSV(const std::vector<std::string> & stringVector)
        {
            if ( !stringVector.empty() )
            {
                std::copy(std::begin(stringVector), std::prev(std::end(stringVector)), std::ostream_iterator<std::string>(std::cout, ", "));
                std::cout << stringVector.back();
            }
        }
    }
}
