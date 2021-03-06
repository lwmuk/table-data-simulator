#ifndef DATA_SIMULATOR_ALL_SELECTOR_H
#define DATA_SIMULATOR_ALL_SELECTOR_H

#include "data.h"
#include <vector>

// ȫѡ��
class AllSelector : public Data
{
public:
	AllSelector(const std::string& name, const std::vector<std::string>& args);

	std::string data() const;

	bool next();

	void reset();

	static bool compatible(const Config& cfg);

	static Data* create(const Config& cfg);

private:
	std::vector<std::string> m_option;
	int m_index;
};

#endif

