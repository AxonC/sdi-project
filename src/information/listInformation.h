#ifndef SDI_PROJECT_LISTINFORMATION_H
#define SDI_PROJECT_LISTINFORMATION_H

#include "../model/material/DVD.h"
#include "../model/project/Project.h"
#include "../model/material/BoxSet.h"

namespace TrekStar
{
    namespace Information
    {
        void displayAllProjects(std::vector<TrekStar::Project::Project> & projects);

        void listProjects(std::vector<TrekStar::Project::Project> & projects, bool sortByTitle);

        void searchProjects(std::vector<TrekStar::Project::Project> & projects);
    }
}

#endif //SDI_PROJECT_LISTINFORMATION_H
