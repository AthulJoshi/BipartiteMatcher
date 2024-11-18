#include "input_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <regex>

InputParser::InputParser(const std::string& filename) : filename(filename) {}

BipartiteMatching InputParser::parse() {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Unable to open input file!");
    }

    int numProfessors, numStudents;
    inputFile >> numProfessors >> numStudents;
    inputFile.ignore(); // To consume the newline after the number of professors and students

    BipartiteMatching bm(numProfessors, numStudents);

    std::string line;
    std::regex edgePattern("Prof_(\\d+): Stu_(\\d+)");

    while (std::getline(inputFile, line)) {
        std::smatch match;
        if (std::regex_match(line, match, edgePattern)) {
            int professor = std::stoi(match[1].str()) - 1;  // Convert to 0-based index
            int student = std::stoi(match[2].str()) - 1;    // Convert to 0-based index
            bm.addEdge(professor, student);
        }
    }

    return bm;
}
