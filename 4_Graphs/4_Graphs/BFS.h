#pragma once
#include "Graph.h"
#include <queue>

class BFS
{
private:
	std::vector<bool> marked;
public:
	BFS(const Graph& G, int v) : marked(G.getV(), false)
	{
		bfs(G, v);
	}

	BFS(const Graph& G, std::vector<int> vs) : marked(G.getV(), false)
	{
		for (int v : vs)
			bfs(G, v);
	}

	bool isMarked(int v) const { return marked[v]; }
private:
	void bfs(const Graph& G, int v)
	{
		std::queue<int> queue;
		queue.push(v);
		while (!queue.empty()) {
			int w = queue.front(); queue.pop();
			marked[w] = true;
			for (auto i : G.getAdj(w)) {
				if (!marked[i]) queue.push(i);
			}
		}
	}
};

class BFSPath
{
private:
	std::vector<int> pathTo;
public:
	BFSPath(const Graph& G, int v) : pathTo(G.getV(), -1)
	{
		bfs(G, v);
	}

	BFSPath(const Graph& G, std::vector<int> vs) : pathTo(G.getV(), -1)
	{
		for (int v : vs)
			bfs(G, v);
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
	void bfs(const Graph& G, int v)
	{
		std::queue<int> queue;
		queue.push(v);
		pathTo[v] = v;
		while (!queue.empty()) {
			int w = queue.front(); queue.pop();
			for (auto i : G.getAdj(w)) {
				if (pathTo[i] == -1) {
					pathTo[i] = w;
					queue.push(i);
				}
			}
		}
	}
};