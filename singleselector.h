#ifndef DATA_SIMULATOR_SINGLE_SELECTOR_H
#define DATA_SIMULATOR_SINGLE_SELECTOR_H

#include "data.h"
#include <vector>

// µ¥Ñ¡Æ÷
class SingleSelector : public Data
{
public:
	SingleSelector(const std::string& name, const std::vector<std::string>& args);

	std::string data() const;

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

private:
	std::vector<std::string> m_option;
};

#endif

