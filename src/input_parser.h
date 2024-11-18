#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include "bipartite_matching.h"
#include <string>

class InputParser {
public:
    InputParser(const std::string& filename);
    BipartiteMatching parse();

private:
    std::string filename;
};

#endif // INPUT_PARSER_H
