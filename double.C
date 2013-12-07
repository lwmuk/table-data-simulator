#include "double.h"
#include "factory.h"
#include "datatype.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

static bool d = Factory::getInstance()->regData(DataType::Double(), Double::compatible, Double::create);

Double::Double(const std::string& name, double min, double max) :
	Data(name), m_min(min), m_max(max)
{
	srand(time(0));
}

std::string Double::Double::data() const
{
	double res = 0.0;
	if (m_max == m_min)
	{
		res = m_max;
	}
	else
	{
		int n = rand();
		res = fmod(n + sin(n), m_max - m_min) + m_min;
		if (res == m_min && n % 2 == 0)
		{
			res = m_max;
		}
	}

	return Tools::withMark(res);
}

bool Double::compatible(const Config& cfg)
{
	if (cfg.size() < 3)
	{
		return false;
	}
	return cfg.front() == DataType::Double();
}

Data* Double::create(const Config& cfg)
{
	if (cfg.size() > 3)
	{
		double min = Tools::str2double(cfg[2]);
		double max = Tools::str2double(cfg[3]);
		return new Double(cfg[1], std::min(min, max), std::max(min, max));
	}
	return 0;
}

