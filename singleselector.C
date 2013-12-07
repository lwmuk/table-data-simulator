#include "singleselector.h"
#include "factory.h"
#include "datatype.h"
#include <ctime>
#include <cstdlib>

static bool single = Factory::getInstance()->regData(DataType::Single(), SingleSelector::compatible, SingleSelector::create);

SingleSelector::SingleSelector(const std::string& name, const std::vector<std::string>& args)
	: Data(name)
{
	for (std::vector<std::string>::const_iterator iter = args.begin(); iter != args.end(); ++iter)
	{
		m_option.push_back(Tools::withMark(*iter));
	}
	srand(time(0));
}

std::string SingleSelector::data() const
{
	if (m_option.empty())
	{
		return std::string();
	}
	size_t i = rand() % m_option.size();
	return m_option[i];
}

bool SingleSelector::compatible(const Config& cfg)
{
	if (cfg.size() < 2)
	{
		return false;
	}
	return cfg.front() == DataType::Single();
}

Data* SingleSelector::create(const Config& cfg)
{
	if (cfg.size() > 2)
	{
		return new SingleSelector(cfg[1], Config(cfg.begin() + 2, cfg.end()));
	}
	return 0;
}

