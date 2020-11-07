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

#include "EWDiGraph.h"

#include "RunTimeTest.h"

using namespace std;


int main()
{

	ifstream in("..\\datas\\tinyEWD.txt");
	EWDiGraph DG(in);
	cout << DG << "\n\n\n";





	
		
}