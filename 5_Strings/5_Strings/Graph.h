#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

class Graph
{
protected:
	int V;
	int E = 0;
	std::vector<std::vector<int>> adj;
public:
	Graph(int v) : V(v), adj(v) {}

	Graph(std::istream& In)
	{
		int _E;
		In >> V >> _E;
		adj.resize(V);
		for (int i = 0; i < _E; ++i) {
			int v, w;
			In >> v >> w;
			addEdge(v, w);
		}
	}

	virtual void addEdge(int v, int w)
	{
		adj[v].emplace_back(w);
		adj[w].emplace_back(v);
		++E;
	}

	const std::vector<int>& getAdj(int v) const
	{
		return adj[v];
	}

	int getV() const { return V; }
	int getE() const { return E; }

	std::string toString()
	{
		std::ostringstream ss;
		int len = std::to_string(V).length();
		ss << "V = " << V << "; E = " << E << "\n";
		for (int v = 0; v < V; ++v) {
			ss << std::setw(len) << v << " : ";
			for (auto i : adj[v])
				ss << i << ", ";
			ss << "\n";
		}
		return ss.str();
	}
};

class DiGraph : public Graph
{
public:
	DiGraph(int v) : Graph(v) {}

	DiGraph(std::istream& In) : Graph(0)
	{
		int _E;
		In >> V >> _E;
		adj.resize(V);
		for (int i = 0; i < _E; ++i) {
			int v, w;
			In >> v >> w;
			addEdge(v, w);
		}
	}

	virtual void addEdge(int v, int w)
	{
		adj[v].emplace_back(w);
		++E;
	}

	DiGraph reverse()
	{
		DiGraph R{ V };
		for (int v = 0; v < V; ++v)
			for (int w : adj[v])
				R.addEdge(w, v);
		return std::move(R);
	}
};