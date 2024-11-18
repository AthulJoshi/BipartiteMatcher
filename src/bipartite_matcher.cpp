#include "bipartite_matching.h"

BipartiteMatching::BipartiteMatching(int numProfessors, int numStudents)
    : numProfessors(numProfessors), numStudents(numStudents),
      adjList(numProfessors), matchProfessors(numProfessors, -1),
      matchStudents(numStudents, -1) {}

void BipartiteMatching::addEdge(int professor, int student) {
    adjList[professor].push_back(student);
}

int BipartiteMatching::maxMatching() {
    int matching = 0;
    for (int i = 0; i < numProfessors; ++i) {
        std::vector<bool> visited(numStudents, false);
        if (dfs(i, visited)) {
            ++matching;
        }
    }
    return matching;
}

bool BipartiteMatching::dfs(int u, std::vector<bool>& visited) {
    for (int v : adjList[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (matchStudents[v] == -1 || dfs(matchStudents[v], visited)) {
                matchProfessors[u] = v;
                matchStudents[v] = u;
                return true;
            }
        }
    }
    return false;
}

void BipartiteMatching::getMatchings(std::ostream& out) const {
    out << "Professor - Student Pairs:" << std::endl;
    for (int i = 0; i < numProfessors; ++i) {
        if (matchProfessors[i] != -1) {
            out << "Prof_" << i + 1 << " - Stu_" << matchProfessors[i] + 1 << std::endl;
        }
    }
}
