#include <fstream>
#include <queue>

#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
#include "CC.h"
#include "Cycle.h"
#include "TwoColor.h"
#include "TopologicalSort.h"
#include "DepthFirstOrder.h"
#include "SCC.h"

#include "EWGraph.h"
#include "LazyPrimMST.h"

#include "RunTimeTest.h"

using namespace std;


int main()
{

	ifstream in("..\\datas\\tinyEWG.txt");
	EWGraph G(in);

	cout << G;

	LazyPrimMST res(G);

	cout << "\n\n";
	for (auto e : res.getMst()) {
		cout << *e << ", ";
	}

	
		
}