#ifndef DATA_SIMULATOR_TIMER_H
#define DATA_SIMULATOR_TIMER_H

#include "data.h"
#include <ctime>

// ʱ���������
class Timer : public Data
{
public:
	Timer(const std::string& name, const std::string& begin, const std::string& end, int cycle);

	virtual ~Timer() {}

	virtual bool next();

protected:
	time_t m_current;
	time_t m_end;
	unsigned int m_cycle;
	bool m_first;
};

// 14λʱ���������
class Timer14 : public Timer
{
public:
	Timer14(const std::string& name, const std::string& begin, const std::string& end, int cycle);

	std::string data() const;

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

};

// 19λʱ���������
class Timer19 : public Timer
{
public:
	Timer19(const std::string& name, const std::string& begin, const std::string& end, int cycle);

	std::string data() const;

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

};

#endif

