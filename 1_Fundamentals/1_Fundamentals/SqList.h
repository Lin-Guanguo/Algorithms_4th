#pragma once
#include <memory>

template<typename Value>
class SqList
{
	struct Node;
	struct Node_holder
	{
		Node_holder(Node* n) : next(n){}
		Node* next;
	};
	struct Node : public Node_holder
	{
		template<typename... Args>
		Node(Node* n, Args&&... args) : Node_holder(n),
			value(std::forward<decltype(args)>(args)...){}
		Value value;
	};
	Node_holder* head;
public:
	SqList()
	{
		head = new Node_holder{ nullptr };
	}

	~SqList()
	{
		if(head->next) destory_last_node(head->next);
		delete(head);
	}

	class iterator;
	template<typename... Args>
	void emplace_after(iterator iter, Args&&... args)
	{
		auto oldnext = iter.node->next;
		iter.node->next = new Node(oldnext, std::forward<decltype(args)>(args)...);
	}

	template<typename... Args>
	void emplace_front(Args&&... args) { emplace_after(before_begin(), std::forward<decltype(args)>(args)...); }
	void push_front(const Value& v) { emplace_front(v); }
	void push_front(Value&& v) { emplace_front(std::move(v)); }
	
	void erase_after(iterator iter)
	{
		auto to_delete = iter.node->next;
		iter.node->next = iter.node->next->next;
		delete to_delete;
	}

	void erase_front() { erase_after(before_begin()); }

private:
	void destory_last_node(Node* x)
	{
		if (x->next) destory_last_node(x->next);
		delete x;
	}

public:
	class iterator
	{
		friend class SqList;
		Node_holder* node;
	public:
		iterator(Node_holder* x) : node(x){ }
		bool operator != (iterator that)
		{
			return this->node != that.node;
		}

		bool operator == (iterator that)
		{
			return this->node == that.node;
		}

		iterator operator++()
		{
			node = node->next;
			return *this;
		}

		iterator operator++(int)
		{
			auto old = *this;
			node = node->next;
			return old;
		}

		Value& operator*()
		{
			return ((Node*)(this->node))->value;
		}

		Value* operator->()
		{
			return &((Node*)(this->node))->value;
		}
	};

	iterator begin()
	{
		return iterator(head->next);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	iterator before_begin()
	{
		return iterator(head);
	}

};