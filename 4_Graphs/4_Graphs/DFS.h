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

class DFSPath
{
private:
	std::vector<int> pathTo;
public:
	DFSPath(const Graph& G, int v) : pathTo(G.getV(), -1)
	{
		pathTo[v] = v;
		dfs(G, v);
	}

	DFSPath(const Graph& G, std::vector<int> vs) : pathTo(G.getV(), -1)
	{
		for (int v : vs) {
			pathTo[v] = v;
			dfs(G, v);
		}
	}

	std::vector<int> getPath(int v)
	{
		if (pathTo[v] == -1) return {};

		std::vector<int> res{ v };
		while (pathTo[v] != v) {
			res.push_back(pathTo[v]);
			v = pathTo[v];
		}
		std::reverse(res.begin(), res.end());
		return res;
	}

private:
	void dfs(const Graph& G, int v)
	{
		for (auto i : G.getAdj(v))
			if (pathTo[i] == -1) {
				pathTo[i] = v;
				dfs(G, i);
			}
	}
};