#pragma once
#include "Graph.h"


class TopologicalSort
{
private:
	std::vector<std::vector<int>> allRes;

public:
	TopologicalSort(const DiGraph& G)
	{
		std::vector<int> degree( G.getV(), 0);
		for (int i = 0; i < G.getV(); ++i)
			for (auto j : G.getAdj(i))
				degree[j]++;
		
		Sort(G, degree, {});
	}

	const std::vector<std::vector<int>>& getRes() const { return allRes; }
private:
	void Sort(const DiGraph& G, std::vector<int> degree, std::vector<int> res)
	{
		if (res.size() == G.getV()) {
			allRes.emplace_back(res);
			return;
		}

		for (int i = 0; i < G.getV(); ++i) {
			if (degree[i] == 0)
			{
				auto newDegree = degree;
				newDegree[i] = -1;
				for (auto j : G.getAdj(i))
					newDegree[j]--;

				auto newRes = res;
				newRes.push_back(i);

				Sort(G, newDegree, newRes);
			}
		}

	}
};