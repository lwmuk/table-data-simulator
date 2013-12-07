#ifndef DATA_SIMULATOR_CONSTANT_H
#define DATA_SIMULATOR_CONSTANT_H

#include "data.h"

// ����������
class Constant : public Data
{
public:
	Constant(const std::string& name, const std::string& val);

	std::string data() const { return m_value; }

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

private:
	std::string m_value;
};

#endif

