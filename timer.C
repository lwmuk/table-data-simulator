#include "timer.h"
#include "tools.h"
#include "factory.h"
#include "datatype.h"
#include <cstdlib>

Timer::Timer(const std::string& name, const std::string& begin, const std::string& end, int cycle)
	: Data(name, OUTERLOOP), m_cycle(cycle), m_first(true)
{
	m_current = Tools::str2time(begin);
	m_end = Tools::str2time(end);
}

bool Timer::next()
{
	if (!m_first)
	{
		m_current += m_cycle;
	}
	else
	{
		m_first = false;
	}

	if (m_current <= m_end)
	{
		return true;
	}

	return false;
}

// 14位时间戳生成器

static bool time14 = Factory::getInstance()->regData(DataType::Time14(), Timer14::compatible, Timer14::create);

Timer14::Timer14(const std::string& name, const std::string& begin, const std::string& end, int cycle)
	: Timer(name, begin, end, cycle)
{

}

std::string Timer14::data() const
{
	return Tools::withMark(Tools::time2str(m_current));
}

bool Timer14::compatible(const Config& cfg)
{
	if (cfg.size() < 4)
	{
		return false;
	}
	return cfg.front() == DataType::Time14();
}

Data* Timer14::create(const Config& cfg)
{
	if (cfg.size() > 4)
	{
		return new Timer14(cfg[1], cfg[2], cfg[3], atoi(cfg[4].c_str()));
	}
	return 0;
}

// 19位时间戳生成器

static bool time19 = Factory::getInstance()->regData(DataType::Time19(), Timer19::compatible, Timer19::create);

Timer19::Timer19(const std::string& name, const std::string& begin, const std::string& end, int cycle)
	: Timer(name, begin, end, cycle)
{

}

std::string Timer19::data() const
{
	return Tools::withMark(Tools::time2str(m_current, "19"));
}

bool Timer19::compatible(const Config& cfg)
{
	if (cfg.size() < 4)
	{
		return false;
	}
	return cfg.front() == DataType::Time19();
}

Data* Timer19::create(const Config& cfg)
{
	if (cfg.size() > 4)
	{
		return new Timer19(cfg[1], cfg[2], cfg[3], atoi(cfg[4].c_str()));
	}
	return 0;
}

