#include "bulk_class.h"
#include <iostream>
#include <fstream>
#include <chrono>


Bulk::Bulk(int N): m_N(N)
{
}

Bulk::~Bulk()
{
}

void Bulk::setCmd(std::string cmd)
{
	if (cmd == "{")
	{
		if (!m_inclBlock)
		{
			printBulk();
		}
		++m_inclBlock;
		return;
	}

	if (cmd == "}")
	{
		if (m_inclBlock > 0) --m_inclBlock;
		if (!m_inclBlock)
		{
			printBulk();
		}
		return;
	}

	q_cmd.push(cmd);
	if (q_cmd.size() == m_N && !m_inclBlock)
	{
		printBulk();
	}
}

void Bulk::printBulk()
{
	if (q_cmd.empty()) return;

	std::ofstream fout;
	auto time = std::chrono::system_clock::now();
	fout.open("bulk" + std::to_string(time.time_since_epoch().count()) + ".log", std::ios_base::out);

	std::string cmd;
	std::cout << "bulk: ";
	while (!q_cmd.empty())
	{
		cmd = q_cmd.front();
		q_cmd.pop();
		std::cout << cmd << (!q_cmd.empty() ? ", " : "");
		fout << cmd << (!q_cmd.empty() ? ", " : "");
	}
	std::cout << "\n";
	fout.close();
}
