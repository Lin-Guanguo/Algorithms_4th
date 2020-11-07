#pragma once
#include <stdexcept>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

class DEdge {
	int _v, _w;
	double _weight;
public:
	DEdge(int from, int to, double weight) : _v(from), _w(to), _weight(weight) {}
	double weight() const { return _weight; }
	int from() const { return _v; }
	int to() const { return _w; }
	bool operator<(const DEdge& that) const { return this->weight() < that.weight(); }
	bool operator>(const DEdge& that) const { return this->weight() > that.weight(); }
	bool operator==(const DEdge& that) const { return this->weight() == that.weight(); }
	bool operator!=(const DEdge& that) const { return this->weight() != that.weight(); }
};

std::ostream& operator<< (std::ostream& out, const DEdge& e) {
	out << '[' << e.from() << " - " << e.to() << " :" << e.weight() << ']';
	return out;
}

class EWDiGraph {
	int V;
	int E = 0;
	std::vector<std::vector<DEdge>> adj;
public:
	EWDiGraph(int v) : V(v), adj(v) {}

	EWDiGraph(std::istream& In) {
		int _E;
		In >> V >> _E;
		adj.resize(V);
		for (int i = 0; i < _E; ++i) {
			int v, w;
			double weight;
			In >> v >> w >> weight;
			EWDiGraph::addEdge(v, w, weight);
		}
	}

	void addEdge(int v, int w, double weight) {
		adj[v].emplace_back(v, w, weight);
		++E;
	}

	const std::vector<DEdge>& getAdj(int v) const { return adj[v]; }
	int getV() const { return V; }
	int getE() const { return E; }
};

std::ostream& operator<< (std::ostream& out, const EWDiGraph& G) {
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