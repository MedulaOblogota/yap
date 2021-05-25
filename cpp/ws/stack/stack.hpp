typedef int DataType;

struct Stack
{
public:
	explicit Stack();
	~Stack();
	Stack(const Stack& other_);
	Stack& operator=(const Stack& other_);

	void Push(const DataType data);
	void Pop();
	DataType Top() const;
	size_t Count() const;
	bool IsEmpty() const;

	struct Node
	{
		// explicit Node();
		explicit Node(DataType data, const Node *next);

		DataType GetData() const;
		bool HasNext() const;
		const Node &GetNext() const;

		const DataType m_data;
		const Node* m_next;
	};
private:
	const Node *m_top;
	void EmptyIMP();
	void CopyIMP(const Stack& other_);
};
