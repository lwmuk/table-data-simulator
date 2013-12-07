#include "integer.h"
#include "factory.h"
#include "datatype.h"
#include "tools.h"
#include <sstream>
#include <cstdlib>
#include <ctime>

static bool number = Factory::getInstance()->regData(DataType::Integer(), Integer::compatible, Integer::create);

Integer::Integer(const std::string& name, int min, int max) :
	Data(name), m_min(min), m_max(max)
{
	srand(time(0));
}

std::string Integer::Integer::data() const
{
	int res = 0;
	if (m_max == m_min)
	{
		res = m_max;
	}
	else
	{
		res = rand() % (m_max - m_min + 1) + m_min;
	}

	return Tools::withMark(res);
}

bool Integer::compatible(const Config& cfg)
{
	if (cfg.size() < 3)
	{
		return false;
	}
	return cfg.front() == DataType::Integer();
}

Data* Integer::create(const Config& cfg)
{
	if (cfg.size() > 3)
	{
		int min = Tools::str2int(cfg[2]);
		int max = Tools::str2int(cfg[3]);
		return new Integer(cfg[1], std::min(min, max), std::max(min, max));
	}
	return 0;
}

