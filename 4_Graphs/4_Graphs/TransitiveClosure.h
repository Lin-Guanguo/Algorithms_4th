/*
	传递闭包
	有向图中两点可达性

	高效算法仍未发现
*/

#pragma once
#include "DFS.h"

class TransitiveClosure {
private:
	std::vector<DFS> all;
public:
	TransitiveClosure(const DiGraph& G) {
		all.reserve(G.getV());
		for(int w = 0; w < G.getV(); ++w)
			all.emplace_back(G, w);
	}

	bool reachable(int v, int w) const { return all[v].isMarked(w); }
};

