#include "BipartiteMatching.h"
#include <iostream>
#include <vector>

int main() {
    // File names for input and output
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";

    // Create an instance of BipartiteMatcher
    // The constructor parameters are: number of professors and number of students
    // Example: 3 professors and 4 students
    BipartiteMatcher matcher(3, 4);

    // Read graph data (professors, students, and edges) from the input file
    matcher.readGraphFromFile(inputFile);

    // Write the maximum matching results to the output file
    matcher.writeMatchingToFile(outputFile);

    std::cout << "Matching results written to " << outputFile << std::endl;

    return 0;
}
