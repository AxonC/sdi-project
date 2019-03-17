#include <iostream>
#include <fstream>
#include <vector>

#include "file/fileOperations.cpp"

int main()
{
    std::string fileDirectory = "/Users/Matt/Documents/School/NTU/OneDrive - Nottingham Trent University/Year 2/SOFT20091 Software Design & Implementation/Assessment/Coursework Assignment/sdi-project/src/data";
    std::vector<std::string> files;
    files = readDirectory("/Users/Matt/Documents/School/NTU/OneDrive - Nottingham Trent University/Year 2/SOFT20091 Software Design & Implementation/Assessment/Coursework Assignment/sdi-project/src/data");

    std::vector<TrekStar::Project::Project> projects = importProjects(fileDirectory, files);

    std::cout << "Welcome to TrekStar Management System | Console" << std::endl;

    std::string command = "";

    while ( command != "q" && command != "quit" )
    {
        std::cout << "Available commands: " << std::endl;
        std::cout << " list projects - lsp" << std::endl;
        std::cout << " quit          - q" << std::endl;

        std::cout << "> ";
        std::cin >> command;
    }

    return 0;
}
