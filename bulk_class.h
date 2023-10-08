#ifndef BULK_CLASS
#define BULK_CLASS

#include <string>
#include <queue>

class Bulk
{
public:
	Bulk(int N);
	~Bulk();

	void setCmd(std::string);

private:
	int m_N;
	int m_inclBlock = 0;
	std::queue<std::string> q_cmd;

	void printBulk();
};

#endif

