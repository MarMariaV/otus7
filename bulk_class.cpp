#include "bulk_class.h"

Bulk::Bulk(int N): m_N(N)
{
    consolePrint = ConsolePrinter::create(&commandPrintPubl);
    filePrint = FilePrinter::create(&commandPrintPubl);
}

Bulk::~Bulk() = default;

void Bulk::setCmd(const std::string & cmd)
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

    q_cmd.push_back(cmd);

	if (q_cmd.size() == m_N && !m_inclBlock)
	{
		printBulk();
	}
}

void Bulk::printBulk()
{
	if (q_cmd.empty()) return;

    commandPrintPubl.setBulk(&q_cmd);

    q_cmd.clear();
}
