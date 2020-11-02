/*
	˫ɫͼ
*/

#pragma once
#include "Graph.h"

class TwoColor
{
private:
	std::vector<short> color;
	bool twoColor = true;
public:
	TwoColor(const Graph& G) : color(G.getV(), -1)
	{
		for (int i = 0; i < G.getV(); ++i)
			if (color[i] == -1)
				dfs(G, i, 0);
	}

	bool isTwoColor() const { return twoColor; }
private:
	void dfs(const Graph& G, int v, short c)
	{
		color[v] = c;
		for (auto w : G.getAdj(v))
			if (color[w] == -1)
				dfs(G, w, !c);
			else if (color[w] == c)
				twoColor = false;
	}
};