#pragma once
#include "Graph.h"
#include "DepthFirstOrder.h"

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
		
		Sort(G, std::move(degree), {});
	}

	const std::vector<std::vector<int>>& getRes() const { return allRes; }
private:
	void Sort(const DiGraph& G, std::vector<int> degree, std::vector<int> res)
	{
		if (res.size() == G.getV()) {
			allRes.emplace_back(std::move(res));	//move确实能提高效率
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

				Sort(G, std::move(newDegree), std::move(newRes));
			}
		}
	}
};

class TopologicalSort_v2 {
	DepthFirstOrder order;
public:
	TopologicalSort_v2(const DiGraph& G) : order(G) {}
	const std::list<int>& getTopologicalSort() const {
		return order.getReversPost(); 
	}
};