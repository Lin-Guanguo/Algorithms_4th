#pragma once
#include "DFS.h"
#include <string>
#include <stack>

#include <iostream>

class NFA
{
private:
	DiGraph G;
	std::string regex;
public:
	NFA(std::string regex) : G(regex.length() + 1), regex(regex)
	{
		std::stack<int> ops;
		int M = regex.length();
		for (int i = 0; i < M; ++i) {
			int blockLeft = i;						//一个整体的首字符: 左括号 或 本字符, 
			char c = regex[i];

			if (c == '(' || c == '|')
				ops.push(i);
			else if (c == ')') {
				//char Or = ops.top(); ops.pop();		//弹出 '(' 或 '|'
				//if (regex[Or] == '|') {
				//	blockLeft = ops.top(); ops.pop();
				//	G.addEdge(blockLeft, Or + 1);
				//	G.addEdge(Or, i);
				//}
				int Or = ops.top(); ops.pop();		//多项 | 处理
				vector<int> Ors;
				while (regex[Or] == '|') {
					Ors.push_back(Or);
					Or = ops.top(); ops.pop();
				}
				blockLeft = Or;
				for (int Or : Ors) {
					G.addEdge(blockLeft, Or + 1);
					G.addEdge(Or, i);
				}
			}
			
			if (i < M - 1 && regex[i+1] == '*'){
				G.addEdge(blockLeft, i + 1);
				G.addEdge(i + 1, blockLeft);
			}

			if (c == '(' || c == '*' || c == ')')
				G.addEdge(i, i + 1);				//符号指向 后续字母 边
		}
	}

	bool recognizes(std::string txt)
	{
		std::vector<int> match{ 0 };
		std::vector<int> nextLocation; 
		for (int i = 0; ; ++i) {					//遍历txt，不管过程中有没有找到
			nextLocation.clear();
			DFS dfs( G, match );	
			for (int v = 0; v < G.getV(); ++v)		//∈转换, 所有下一步可达点
				if (dfs.isMarked(v)) nextLocation.push_back(v);

			if (i >= txt.length()) break;

			match.clear();
			for (int v : nextLocation)
				if (v < regex.length())
					if (regex[v] == txt[i] || regex[v] == '.')
						match.push_back(v + 1);		//匹配，走入下一步
		}
		//全不匹配后match, nextLocation 都为空

		for (int v : nextLocation) 
			if (v == regex.length())				//有到达regex结束状态
				return true;
		return false;
	}
};

class NFA_plus
{
private:
	std::string regex;
	DiGraph G;

	std::string expand(std::string regex)	//处理各种简写
	{
		return regex;
	}

public:
	NFA_plus(std::string o_regex) : regex(expand(o_regex)), G(regex.length() + 1)
	{
		std::stack<int> ops;
		int M = regex.length();
		for (int i = 0; i < M; ++i) {
			int blockLeft = i;						
			char c = regex[i];

			if (c == '(' || c == '|')
				ops.push(i);
			else if (c == ')') {
				int Or = ops.top(); ops.pop();	
				vector<int> Ors;
				while (regex[Or] == '|') {
					Ors.push_back(Or);
					Or = ops.top(); ops.pop();
				}
				blockLeft = Or;
				for (int Or : Ors) {
					G.addEdge(blockLeft, Or + 1);
					G.addEdge(Or, i);
				}
			}

			if (i < M - 1 && regex[i + 1] == '*') {
				G.addEdge(blockLeft, i + 1);
				G.addEdge(i + 1, blockLeft);
			}

			if (c == '(' || c == '*' || c == ')')
				G.addEdge(i, i + 1);		
		}
	}

	bool recognizes(std::string txt)
	{
		std::vector<int> match{ 0 };
		std::vector<int> nextLocation;
		for (int i = 0; i <= txt.length(); ++i) {
			nextLocation.clear();
			DFS dfs(G, match);
			for (int v = 0; v < G.getV(); ++v)	
				if (dfs.isMarked(v)) nextLocation.push_back(v);

			if (nextLocation.empty()) break;

			match.clear();
			for (int v : nextLocation)
				if (v < regex.length()) 
					if (regex[v] == txt[i] || regex[v] == '.')
						match.push_back(v + 1);	
		}


		for (int v : nextLocation)
			if (v == regex.length())
				return true;
		return false;
	}
};
