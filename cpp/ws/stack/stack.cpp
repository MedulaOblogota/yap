#include <iostream>
#include <new>
#include <cassert>
#include <cstdio>

#include "stack.hpp"
#include "tests.h"

void Stack::EmptyIMP()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

void Stack::CopyIMP(const Stack& other_)
{
	Stack temp_stack;
	const Node *this_runner = m_top;
	const Node *other_runner = other_.m_top;
	const Node *temp_runner = temp_stack.m_top;

	while (NULL != other_runner)
	{
		temp_stack.Push(other_runner->m_data);
		other_runner = other_runner->m_next;
	}

	temp_runner = temp_stack.m_top;

	while (NULL != temp_runner)
	{
		Push(temp_runner->m_data);
		temp_runner = temp_runner->m_next;
	}

	// const Node *first = m_top;
	// const Node *second = m_top->m_next;
	// const Node *tmp = NULL;
	//
	// first->m_next = tmp;
	//
	// while (NULL != second)
	// {
	// 	tmp = second->m_next;
	// 	second->m_next = first;
	// 	first = second;
	// 	second = tmp;
	// }
	//
	// m_top = first;
}

Stack::Stack()
	: m_top(NULL)
{
	// std::cout << "In Default Ctor" << std::endl;
}

Stack::Node::Node(DataType data, const Node *next)
	: m_data(data), m_next(next)
{
	// std::cout << "created new node" << std::endl;
}

DataType Stack::Node::GetData() const
{
	return m_data;
}

bool Stack::Node::HasNext() const
{
	return (!(m_next == NULL));
}

const Stack::Node &Stack::Node::GetNext() const
{
	return (*m_next);
}

Stack& Stack::operator=(const Stack& other_)
{
	EmptyIMP();
	CopyIMP(other_);

	return (*this);
}

Stack::Stack(const Stack& other_)
	: m_top(NULL)
{
	// m_top = NULL;
	CopyIMP(other_);
}

Stack::~Stack()
{
	EmptyIMP();
}

void Stack::Push(const DataType data)
{
	Stack::Node* node = new Node(data, m_top);

	m_top = node;
}

void Stack::Pop()
{
	const Stack::Node *node_to_pop = m_top;

	assert(! IsEmpty() );

	m_top = m_top->m_next;

	delete node_to_pop;
}

DataType Stack::Top() const
{
	assert(! IsEmpty() );

	return m_top->GetData();
}

size_t Stack::Count() const
{
	size_t counter = 0;

	const Stack::Node *runner = m_top;

	while (NULL != runner)
	{
		++counter;
		runner = runner->m_next;
	}

	return counter;
}

bool Stack::IsEmpty() const
{
	return (m_top == NULL);
}

int main()
{
	Stack stack;
	Stack new_stack;

	stack.Push(5);
	stack.Push(7);
	stack.Push(3);

	WrapperCompareInt("Top", (int)stack.Top() == 3, 1);

	stack.Pop();

	WrapperCompareInt("Top", (int)stack.Top() == 7, 1);

	WrapperCompareSizet("Count", stack.Count() == 2, 1);

	stack.Push(2);
	WrapperCompareInt("Top", (int)stack.Top() == 2, 1);
	WrapperCompareSizet("Count", stack.Count() == 3, 1);

	stack.Pop();
	stack.Pop();
	WrapperCompareInt("IsEmpty", stack.IsEmpty() == 0, 1);
	stack.Pop();
	WrapperCompareSizet("Count", stack.Count() == 0, 1);
	WrapperCompareInt("IsEmpty", stack.IsEmpty() == 1, 1);

	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	new_stack.Push(4);
	new_stack.Push(5);
	new_stack.Push(6);
	stack = new_stack;

	Stack new_new_stack(stack);
}
