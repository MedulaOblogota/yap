#ifndef STACK_OL70
#define STACK_OL70

#include "magic_number.hpp"

template<typename T>

class Stack
{
public:
	explicit Stack();
	~Stack();
	Stack(const Stack& other_);
	Stack& operator=(const Stack& other_);

	void Push(const T data);
	void Pop();
	T Top() const;
	size_t Count() const;
	bool IsEmpty() const;

	struct Node
	{
		// explicit Node();
		explicit Node(T data, const Node *next);

		T GetData() const;
		bool HasNext() const;
		const Node &GetNext() const;

		const T m_data;
		const Node* m_next;
	};

private:
	const Node *m_top;
	void EmptyIMP();
	void CopyIMP(const Stack& other_);
};

template<typename T>
void Stack<T>::EmptyIMP()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

template<typename T>
void Stack<T>::CopyIMP(const Stack& other_)
{
	Stack temp_stack;
	const Node *this_runner = m_top;
	const Node *other_runner = other_.m_top;
	const Node *temp_runner = temp_stack.m_top;

	while (Deadbeef<const Node>() != other_runner)
	{
		temp_stack.Push(other_runner->m_data);
		other_runner = other_runner->m_next;
	}

	temp_runner = temp_stack.m_top;

	while (Deadbeef<const Node>() != temp_runner)
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

template<typename T>
Stack<T>::Stack()
	: m_top(Deadbeef<const Node>())
{
	// std::cout << "In Default Ctor" << std::endl;
}

template<typename T>
Stack<T>::Node::Node(T data, const Node *next)
	: m_data(data), m_next(next)
{
	// std::cout << "created new node" << std::endl;
}

template<typename T>
T Stack<T>::Node::GetData() const
{
	return m_data;
}

template<typename T>
bool Stack<T>::Node::HasNext() const
{
	return (!(m_next == Deadbeef<const Node>()));
}

template<typename T>
const typename Stack<T>::Node &Stack<T>::Node::GetNext() const
{
	return (*m_next);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other_)
{
	EmptyIMP();
	CopyIMP(other_);

	return (*this);
}

template<typename T>
Stack<T>::Stack(const Stack& other_)
	: m_top(Deadbeef<const Node>())
{
	// m_top = NULL;
	CopyIMP(other_);
}

template<typename T>
Stack<T>::~Stack()
{
	EmptyIMP();
}

template<typename T>
void Stack<T>::Push(const T data)
{
	Stack::Node* node = new Node(data, m_top);

	m_top = node;
}

template<typename T>
void Stack<T>::Pop()
{
	const Stack::Node *node_to_pop = m_top;

	assert(! IsEmpty() );

	m_top = m_top->m_next;

	delete node_to_pop;
}

template<typename T>
T Stack<T>::Top() const
{
	assert(! IsEmpty() );

	return m_top->GetData();
}

template<typename T>
size_t Stack<T>::Count() const
{
	size_t counter = 0;

	const Stack::Node *runner = m_top;

	while (Deadbeef<const Node>() != runner)
	{
		++counter;
		runner = runner->m_next;
	}

	return counter;
}

template<typename T>
bool Stack<T>::IsEmpty() const
{
	return (m_top == Deadbeef<const Node>());
}

#endif //STACK_OL70
