/*
	≈–∂œ”–ª∑Õº
*/

#pragma once
#include "Graph.h"
#include <stack>

class Cycle
{
private:
	std::vector<bool> marked;
	bool cycle = false;
public:
	Cycle(const Graph& G) : marked(G.getV(), false)
	{
		for (int i = 0; i < G.getV(); ++i)
			if (!marked[i])
				dfs(G, i, i);
	}

	bool hasCycle() const{ return cycle; }
private:
	void dfs(const Graph& G, int v, int from)
	{
		marked[v] = true;
		for (int w : G.getAdj(v))
			if (marked[w] == false)
				dfs(G, w, v);
			else if (w != from)
				cycle = true;
	}
};

class DirectedCycle
{
private:
	std::vector<bool> marked;
	bool cycle = false;
	std::vector<int> onCycle;
public:
	DirectedCycle(const Graph& G) : marked(G.getV(), false)
	{
		for (int i = 0; i < G.getV(); ++i)
			if (!marked[i] && !hasCycle()) {
				dfs(G, i);
			}
	}

	bool hasCycle() const { return cycle; }
	const std::vector<int>& getCycle() const { return onCycle; }
private:
	void dfs(const Graph& G, int v)
	{
		marked[v] = true;
		onCycle.push_back(v);
		for (int w : G.getAdj(v))
			if (hasCycle()) return;
			else if (marked[w] == false)
				dfs(G, w);
			else {
				auto CycleStart = std::find(onCycle.begin(), onCycle.end(), w);
				if (CycleStart != onCycle.end()) {
					cycle = true;
					std::move(CycleStart, onCycle.end(), onCycle.begin());
					onCycle.resize(onCycle.end() - CycleStart + 1);
					*--onCycle.end() = w;
					return;
				}
			}

		if(!hasCycle())
			onCycle.pop_back();
	}
};