/*
	DFS的三种顶点排序: 前序、后序、逆后续
*/

#pragma once
#include "Graph.h"
#include <list>
#include <forward_list>

class DepthFirstOrder {
private:
	std::vector<bool> marked;
	std::list<int> pre;
	std::list<int> post;
	std::list<int> reversePost;
public:
	DepthFirstOrder(const DiGraph& G) :
		marked(G.getV(), false), pre(), post(), reversePost() {
		for (int w = 0; w < G.getV(); ++w)
			if (!marked[w])
				DFS(G, w);
	}

	const std::list<int>& getPre() const { return pre; }
	const std::list<int>& getPost() const { return post; }
	const std::list<int>& getReversPost() const { return reversePost; }
private:
	void DFS(const DiGraph& G, int v) {
		pre.push_back(v);
		marked[v] = true;
		for (int w : G.getAdj(v))
			if (!marked[w])
				DFS(G, w);
		post.push_back(v);
		reversePost.push_front(v);
	}
};
