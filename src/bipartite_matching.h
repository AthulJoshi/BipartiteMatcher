#ifndef BIPARTITE_MATCHING_H
#define BIPARTITE_MATCHING_H

#include <vector>
#include <ostream>

class BipartiteMatching {
public:
    BipartiteMatching(int numProfessors, int numStudents);
    void addEdge(int professor, int student);
    int maxMatching();
    void getMatchings(std::ostream& out) const;

private:
    int numProfessors, numStudents;
    std::vector<std::vector<int>> adjList;
    std::vector<int> matchProfessors, matchStudents;
    bool dfs(int u, std::vector<bool>& visited);
};

#endif // BIPARTITE_MATCHING_H
