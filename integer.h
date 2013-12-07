#ifndef DATA_SIMULATOR_NUMBER_H
#define DATA_SIMULATOR_NUMBER_H

#include "data.h"

// 随机数值生成器
class Integer : public Data
{
public:
	Integer(const std::string& name, int min, int max);

	std::string data() const;

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

private:
	int m_min;
	int m_max;
};

#endif

