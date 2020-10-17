#include <fstream>


#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
#include "TopologicalSort.h"


using namespace std;

int main()
{
	ifstream in(".\\data\\tinyDG.txt");
	DiGraph G(in);

	cout << G.toString() << endl << "##################" << endl;

	DFSPath dfs(G, { 0,7 });

	for (int i = 0; i < G.getV(); ++i) {
		auto path = dfs.getPath(i);
		for (auto j : path)
			cout << j << ", ";
		cout << endl;
	}
		
}