#pragma once
#include <stdexcept>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

class Edge {
	int _v, _w;
	double _weight;
public:
	Edge(int v, int w, double weight) : _v(v), _w(w), _weight(weight){}
	double weight() const { return _weight; }
	int v() const { return _v; }
	int w() const { return _w; }
	int either() const { return _v; }
	int other (int i) const {
		if (i == _v)return _w;
		else if (i == _w) return _v;
		else throw std::logic_error("Inconsistent Edge");
	}
	bool operator<(const Edge& that) const { return this->weight() < that.weight(); }
	bool operator>(const Edge& that) const { return this->weight() > that.weight(); }
	bool operator==(const Edge& that) const { return this->weight() == that.weight(); }
	bool operator!=(const Edge& that) const { return this->weight() != that.weight(); }
};

std::ostream& operator<< (std::ostream& out, const Edge& e) {
	out << '[' << e.v() << " - " << e.w() << " :" << e.weight() << ']';
	return out;
}

class EWGraph {
	int V;
	int E = 0;
	std::vector<std::vector<Edge>> adj;
public:
	EWGraph(int v) : V(v), adj(v) {}

	EWGraph(std::istream& In) {
		int _E;
		In >> V >> _E;
		adj.resize(V);
		for (int i = 0; i < _E; ++i) {
			int v, w;
			double weight;
			In >> v >> w >> weight;
			EWGraph::addEdge(v, w, weight);
		}
	}

	void addEdge(int v, int w, double weight) {
		adj[v].emplace_back(v, w, weight);
		adj[w].emplace_back(w, v, weight);
		++E;
	}

	const std::vector<Edge>& getAdj(int v) const { return adj[v]; }
	int getV() const { return V; }
	int getE() const { return E; }
};

std::ostream& operator<< (std::ostream& out, const EWGraph& G) {
	auto len = std::to_string(G.getV()).length();
	out << "V = " << G.getV() << "; E = " << G.getE() << "\n";
	for (int v = 0; v < G.getV(); ++v) {
		out << std::setw(len) << v << " : ";
		for (auto i : G.getAdj(v))
			out << i << ", ";
		out << "\n";
	}
	return out;
}