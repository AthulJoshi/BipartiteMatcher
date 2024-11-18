#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "BipartiteMatching.h"

void readInputFile(const std::string& inputFile, std::vector<std::string>& vertexNames,
                   std::vector<std::string>& professors, std::vector<std::string>& students,
                   std::vector<std::pair<std::string, std::string>>& edges) {
    std::ifstream in(inputFile);
    if (!in) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        exit(1);
    }

    std::string line;

    // Read professors
    std::getline(in, line);
    std::istringstream ssProfessors(line);
    std::string name;
    while (ssProfessors >> name) {
        professors.push_back(name);
    }

    // Read students
    std::getline(in, line);
    std::istringstream ssStudents(line);
    while (ssStudents >> name) {
        students.push_back(name);
    }

    // Read edges
    while (std::getline(in, line)) {
        std::istringstream ssEdge(line);
        std::string prof, student;
        ssEdge >> prof >> student;
        edges.emplace_back(prof, student);
    }

    vertexNames.insert(vertexNames.end(), professors.begin(), professors.end());
    vertexNames.insert(vertexNames.end(), students.begin(), students.end());
    vertexNames.push_back("S");
    vertexNames.push_back("T");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::vector<std::string> vertexNames;
    std::vector<std::string> professors, students;
    std::vector<std::pair<std::string, std::string>> edges;

    readInputFile(inputFile, vertexNames, professors, students, edges);

    BipartiteMatching matcher(vertexNames.size(), vertexNames);

    // Add edges
    for (const auto& edge : edges) {
        matcher.addEdge(edge.first, edge.second);
    }

    // Connect source and sink
    matcher.connectSourceToLeftHalf("S", professors);
    matcher.connectSinkToRightHalf("T", students);

    // Run the algorithm
    matcher.fordFulkersonMaxFlow("S", "T");

    return 0;
}
