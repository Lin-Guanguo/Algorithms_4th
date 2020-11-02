/*
	强连通分量
*/

#pragma once
#include "Graph.h"
#include "DepthFirstOrder.h"

class KosarajuSCC {
private:
	std::vector<int> id;
	int count = 0;
public:
	KosarajuSCC(const DiGraph& G) : id(G.getV(), -1) {
		//反向图的逆后序DFS
		DepthFirstOrder order{ G.reverse() };
		for (auto w : order.getReversPost()) {
			if (id[w] == -1) {
				dfs(G, w);
				count++;
			}
		}
	}

	int getCount() const { return count; }
	const std::vector<int>& getId() const { return id; }
	int getId(int i) const { return id[i]; }
	bool isStronglyConnect(int v, int w) const { return id[v] == id[w]; }
private:
	void dfs(const Graph& G, int v)
	{
		id[v] = count;
		for (int i : G.getAdj(v))
			if (id[i] == -1)
				dfs(G, i);
	}

};
