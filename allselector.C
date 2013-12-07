#include "allselector.h"
#include "factory.h"
#include "datatype.h"
#include "tools.h"

static bool all = Factory::getInstance()->regData(DataType::All(), AllSelector::compatible, AllSelector::create);

AllSelector::AllSelector(const std::string& name, const std::vector<std::string>& args)
	: Data(name, INNERLOOP), m_index(-1)
{
	for (std::vector<std::string>::const_iterator iter = args.begin(); iter != args.end(); ++iter)
	{
		m_option.push_back(Tools::withMark(*iter));
	}
}

std::string AllSelector::data() const
{
	return m_option[m_index];
}

bool AllSelector::next()
{
	++m_index;
	if (m_index < m_option.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AllSelector::reset()
{
	m_index = -1;
}

bool AllSelector::compatible(const Config& cfg)
{
	if (cfg.size() < 2)
	{
		return false;
	}
	return cfg.front() == DataType::All();
}

Data* AllSelector::create(const Config& cfg)
{
	if (cfg.size() > 2)
	{
		return new AllSelector(cfg[1], Config(cfg.begin() + 2, cfg.end()));
	}
	return 0;
}

