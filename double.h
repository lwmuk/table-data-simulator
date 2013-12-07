#ifndef DATA_SIMULATOR_NUMBER_H
#define DATA_SIMULATOR_NUMBER_H

#include "data.h"

// ���������������
class Double : public Data
{
public:
	Double(const std::string& name, double min, double max);

	std::string data() const;

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

private:
	double m_min;
	double m_max;
};

#endif

