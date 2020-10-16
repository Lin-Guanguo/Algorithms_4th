#pragma once
#include "Graph.h"

class DFS
{
private:
	std::vector<bool> marked;
public:
	DFS(const Graph& G, int v) : marked(G.getV(), false)
	{
		dfs(G, v);
	}

	DFS(const Graph& G, std::vector<int> vs) : marked(G.getV(), false)
	{
		for (int v : vs)
			dfs(G, v);
	}

	bool isMarked(int v) const { return marked[v]; }
	
private:
	void dfs(const Graph& G, int v)
	{
		marked[v] = true;
		for (int w : G.getAdj(v))
			if (marked[w] == false) dfs(G, w);
	}

};