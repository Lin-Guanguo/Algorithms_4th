/*
	prim算法，延时实现
*/

#pragma once
#include "EWGraph.h"
#include <queue>

class LazyPrimMST
{
private:
	std::vector<bool> marked;
	std::vector<const Edge*> mst;

	static bool compEdgeP(const Edge* a, const Edge* b) { return *b < *a ; }
	std::priority_queue<const Edge*, std::vector<const Edge*>, decltype(compEdgeP)*> pq{ compEdgeP };
public:
	LazyPrimMST(const EWGraph& G) : marked(G.getV(), false) {
		visit(G, 0);
		while (!pq.empty()) {
			auto e = pq.top(); pq.pop();
			int v = e->either();
			int w = e->other(v);
			if (!marked[v]) visit(G, v);
			else if (!marked[w]) visit(G, w);
			else continue;
			mst.push_back(e);
		}
	}

	const std::vector<const Edge*>& getMst() const { return mst; }
private:
	void visit(const EWGraph& G, int v) {
		marked[v] = true;
		for (auto& e : G.getAdj(v))
			if (!marked[e.other(v)])
				pq.emplace(&e);
	}

};
