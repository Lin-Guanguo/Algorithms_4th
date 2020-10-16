#include <fstream>


#include "Graph.h"
#include "DFS.h"
#include "TopologicalSort.h"


using namespace std;

int main()
{
	ifstream in(".\\data\\topoSortDG.txt");
	DiGraph G(in);

	cout << G.toString() << endl << "##################" << endl;

	TopologicalSort topo(G);
	for (auto& i : topo.getRes())
	{
		for (auto j : i)
			cout << j << ", ";
		cout << endl;
	}
}