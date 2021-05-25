class FDListener
{
public:
	enum FDType { READ, WRITE, EXCEPT };

	explicit FDListener(timeout_);
	~FDListener();

	std::vector< pair<fd_set, FDType> > Wait(std::vector< pair<fd_set, FDType> &vec_);
	void SetTimeout(timeout_);

private:
	struct timeval m_timeout;
};
