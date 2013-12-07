#ifndef DATA_SIMULATOR_OTHER_H
#define DATA_SIMULATOR_OTHER_H

#include "data.h"

// 批量生成器
class Other : public Data
{
public:
	Other(const std::string& name, int n, const std::string& val);

	std::string data() const { return m_data; }

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

private:
	std::string m_data;
};

#endif

