#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <algorithm>

#include <model/project/Project.h>
#include <model/material/DVD.h>
#include <model/people/Crew.h>

#include <controller/project/ProjectController.h>
#include <view/project/ProjectView.h>

#include "../mock/MockProject.h"
#include "../mock/MockProjectView.h"

#include "TestCase.h"

using TrekStar::People::Crew;
using TrekStar::Material::DVD;
using TrekStar::Project::Project;
using TrekStar::Project::ProjectView;
using TrekStar::Project::ProjectController;
using TrekStar::Material::Material;
using TrekStarTests::Tests::TestCase;

using ::testing::NiceMock;

namespace TrekStarTest {
    namespace Tests {
        class ProjectTest: public TestCase
        {
        public:
            // Default state of a project every time a test is ran.
            ProjectTest() : TestCase(),
                            project("Project", "A summary of a project", false, true, {"hello", "keyword"}),
                            releasedProject("Project 2", "A summary of a project", true, false, {"keyword", "keyword 2"})
            {
                releasedProject.ReleaseProject();
            }


            NiceMock<MockProject> mockProject;

            Project project;
            Project releasedProject;
            std::shared_ptr<DVD> material = std::make_shared<DVD>();
            std::shared_ptr<Crew> crewMember = std::make_shared<Crew>();

        };

        TEST_F(ProjectTest, ProjectCanBeReleasedWhenNotPlayingInTheatres)
        {
            project.SetPlayingInTheatres(false);
            project.ReleaseProject();

            ASSERT_TRUE(project.GetReleased());
        }

        TEST_F(ProjectTest, ProjectCantBeReleasedWhenStillInTheatres)
        {
            project.SetPlayingInTheatres(true);

            ASSERT_THROW(project.ReleaseProject(), std::domain_error);
        }

        TEST_F(ProjectTest, ProjectCanHaveKeywordsAssociatedWithIt)
        {
            std::vector<std::string> keyword{"Action"};

            project.SetKeywords(keyword);

            ASSERT_EQ(1, project.GetKeywords().size());
            ASSERT_EQ(keyword.at(0), project.GetKeywords().at(0));
        }

        TEST_F(ProjectTest, CanAddMaterialsWhenValid)
        {
            releasedProject.ReleaseProject();

            releasedProject.AddMaterial(material);

            EXPECT_EQ(releasedProject.GetMaterials().size(), 1);
        }

        TEST_F(ProjectTest, CantAddMaterialsWhenNotReleased)
        {
            std::shared_ptr<DVD> material = std::make_shared<DVD>();

            EXPECT_THROW(project.AddMaterial(material), std::domain_error);
        }

        TEST_F(ProjectTest, CanRemoveMaterialWhenAssociatedWithProject)
        {
            releasedProject.AddMaterial(material);

            releasedProject.RemoveMaterial(material);

            EXPECT_EQ(releasedProject.GetMaterials().size(), 0);
        }

        TEST_F(ProjectTest, CantRemoveMaterialWhenNotAssociatedWithProject)
        {
            ASSERT_THROW(project.RemoveMaterial(material), std::out_of_range);
        }

        TEST_F(ProjectTest, CanAddACrewMemberToAProject)
        {
            project.AddCrew(crewMember);

            EXPECT_EQ(project.GetCrew().size(), 1);
        }

        TEST_F(ProjectTest, ProjectDetectsAnActorCorrectly)
        {
            std::shared_ptr<Crew> actor = std::make_shared<Crew>(1, "bob", "actor");

            project.AddCrew(actor);

            std::string name("bob");
            std::string wrongName("fred");
            ASSERT_NO_THROW(project.FindActor(name));
            ASSERT_THROW(project.FindActor(wrongName), std::out_of_range);
        }

        TEST_F(ProjectTest, CantRemoveACrewMemberWhenNotPresent)
        {
            std::shared_ptr<Crew> unassignedCrew = std::make_shared<Crew>();

            ASSERT_THROW(project.RemoveCrew(unassignedCrew), std::out_of_range);
        }

        TEST_F(ProjectTest, BoxOfficeReportsCanBeAdded)
        {
            std::shared_ptr<TrekStar::Project::BoxOfficeReport> report =
                    std::make_shared<TrekStar::Project::BoxOfficeReport>(1, 5000, 500);

            project.AddBoxOfficeReport(report);

            ASSERT_EQ(project.GetBoxOfficeReports().size(), 1);
        }

        TEST_F(ProjectTest, TotalBoxOfficeRevenueIsCalculated)
        {
            std::vector<std::shared_ptr<TrekStar::Project::BoxOfficeReport>> reports
                            {std::make_shared<TrekStar::Project::BoxOfficeReport>(1, 5000, 500),
                             std::make_shared<TrekStar::Project::BoxOfficeReport>(3, 5000, 500)};

            project.AddBoxOfficeReports(reports);

            ASSERT_EQ(project.GetTotalBoxOfficeRevenue(), 10000);
        }

        TEST_F(ProjectTest, ReportCannotBeAddedForTheSameWeek)
        {
            std::shared_ptr<TrekStar::Project::BoxOfficeReport> report =
                std::make_shared<TrekStar::Project::BoxOfficeReport>(1, 5000, 500);

            std::shared_ptr<TrekStar::Project::BoxOfficeReport> report2 =
                std::make_shared<TrekStar::Project::BoxOfficeReport>(1, 5000, 500);

            project.AddBoxOfficeReport(report);

            ASSERT_THROW(project.AddBoxOfficeReport(report2), std::domain_error);
        }

        TEST_F(ProjectTest, TwoReportsForTheSameWeekCannotBeAdded)
        {
            std::vector<std::shared_ptr<TrekStar::Project::BoxOfficeReport>> reports
                {std::make_shared<TrekStar::Project::BoxOfficeReport>(1, 5000, 500),
                 std::make_shared<TrekStar::Project::BoxOfficeReport>(1, 5000, 500)};

            ASSERT_THROW(project.AddBoxOfficeReports(reports), std::domain_error);
        }

        TEST_F(ProjectTest, ControllerPresentsProjectDetails)
        {
            EXPECT_CALL(mockProject, GetTitle()).Times(1);
            EXPECT_CALL(mockProject, GetSummary()).Times(1);
            EXPECT_CALL(mockProject, GetReleased()).Times(1);
            EXPECT_CALL(mockProject, GetPlayingInTheatres()).Times(1);

            ProjectView projectView(mockProject);
            ProjectController controller(mockProject, projectView);

            controller.ShowAll();
        }

        TEST_F(ProjectTest, DuplicateKnownFormatsAreNotAdded)
        {
            std::shared_ptr<DVD> material = std::make_shared<DVD>();
            std::shared_ptr<DVD> material2 = std::make_shared<DVD>();
            material->SetFormat("dvd");
            material2->SetFormat("dvd");

            releasedProject.AddMaterial(material);
            ASSERT_EQ(1, releasedProject.GetMaterialFormats().size());
            releasedProject.AddMaterial(material2);
            ASSERT_EQ(1, releasedProject.GetMaterialFormats().size());
        }
    }
}