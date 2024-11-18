#include "bipartite_matching.h"
#include "input_parser.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    try {
        // Parse input file to create BipartiteMatching object
        InputParser parser(argv[1]);
        BipartiteMatching bm = parser.parse();

        // Open output file and compute matchings
        std::ofstream outputFile(argv[2]);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Error: Unable to open output file!");
        }

        // Write maximum matching and pairs to the output file
        outputFile << "Maximum Bipartite Matching: " << bm.maxMatching() << std::endl;
        bm.getMatchings(outputFile);
        
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
