#include "pch.h"

#include "maintenanceMode.h"
#include "CommandHandler.h"
#include "userInput.h"
#include "../view/project/ProjectView.h"
#include "../controller/project/ProjectController.h"
#include "../view/material/MaterialView.h"
#include "../controller/material/MaterialController.h"
#include "../information/listInformation.h"

namespace TrekStar
{
    namespace Command
    {
        void maintenanceMode(const std::string & FILE_PATH, std::vector<TrekStar::Project::Project> & projects)
        {
            TrekStar::Command::CommandHandler commandHandler = TrekStar::Command::CommandHandler (
                    {
                            {1, "Add Project"},
                            {2, "Update Project"},
                            {3, "Remove Project"},
                            {4, "Add Project Materials"},
                            {5, "Update Project Materials"},
                            {6, "Remove Project Materials"},
                            {7, "Add Project Crew"},
                            {8, "Update Project Crew"},
                            {9, "Remove Project Crew"},
                            {10, "Add Box Office Report"},
                            {11, "Remove Box Office Report"},
                            {12, "Cancel"}
                    },
                    "Maintenance Mode"
            );

            int commandInput = 0;
            while ( commandInput != 12 )
            {
                commandHandler.displayCommands();
                commandInput = commandHandler.getUserInput();
                commandHandler.clearConsole();

                if ( commandHandler.isValidCommand(commandInput) && commandInput != 12 )
                {
                    if ( commandInput == 1 )
                    {
                        TrekStar::Project::Project currentProject;

                        TrekStar::Project::ProjectView view(currentProject);
                        TrekStar::Project::ProjectController controller(currentProject, view);

                        controller.AddNew();

                        projects.push_back(currentProject);
                    }
                    else
                    {
                        std::cout << std::string(80, '-') << std::endl;
                        TrekStar::Information::displayAllProjects(projects);
                        std::cout << std::string(80, '-') << std::endl;

                        int projectIndex = TrekStar::Command::GetIndexInput(projects.size(), "Project ID");
                        commandHandler.clearConsole();

                        TrekStar::Project::ProjectView view(projects.at(projectIndex));
                        TrekStar::Project::ProjectController controller(projects.at(projectIndex), view);

                        if ( commandInput == 2 )
                        {
                            controller.UpdateProject();
                        }
                        else if ( commandInput == 3 )
                        {
                            projects.erase(projects.begin() + projectIndex);
                        }
                        else if ( commandInput == 4 )
                        {
                            controller.AddMaterial();
                        }
                        else if ( commandInput == 5 )
                        {
                            controller.UpdateMaterials();
                        }
                        else if ( commandInput == 6 )
                        {
                            controller.RemoveMaterial();
                        }
                        else if ( commandInput == 7 )
                        {
                            controller.AddCrew();
                        }
                        else if ( commandInput == 8 )
                        {
                            controller.UpdateCrew();
                        }
                        else if ( commandInput == 9 )
                        {
                            controller.RemoveCrew();
                        }
                        else if ( commandInput == 10 )
                        {
                            controller.AddBoxOfficeReport();
                        }
                        else if ( commandInput == 11 )
                        {
                            controller.RemoveBoxOfficeReport();
                        }
                    }
                }
                else
                {
                    std::cout << "Invalid command..." << std::endl;
                }
            }
        }
    }
}