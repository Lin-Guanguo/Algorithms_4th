/*
	计算连通分量
*/

#pragma once
#include "Graph.h"

class CC
{
private:
	int count = 0;
	std::vector<int> id;

public:
	CC(const Graph& G) : id(G.getV(), -1)
	{
		for(int i = 0; i < G.getV(); ++i)
			if (id[i] == -1) {
				dfs(G, i);
				++count;
			}
	}

	int getCount() const { return count; }
	const std::vector<int>& getId() const { return id; }
	int getId(int i) const { return id[i]; }
	bool isConnect(int v, int w) const { return id[v] == id[w]; }
private:
	void dfs(const Graph& G, int v)
	{
		id[v] = count;
		for (int i : G.getAdj(v))
			if (id[i] == -1)
				dfs(G, i);
	}
};