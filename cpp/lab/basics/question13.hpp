struct X
{
	explicit X();
	explicit X(int a_, int b_);
	~X();
	X(const X& other_);
	X& operator=(const X& other_);

	int m_a;
	const int m_b;
};

struct Y
{
	explicit Y();
	explicit Y(int a_, int b_, int i_);

	X m_x;
	int m_i;
};
