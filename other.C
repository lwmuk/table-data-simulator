#include "other.h"
#include "factory.h"
#include "tools.h"
#include "datatype.h"
#include <cstdlib>

static bool rest = Factory::getInstance()->regData(DataType::Rest(), Other::compatible, Other::create);

Other::Other(const std::string& name, int n, const std::string& val)
	: Data(name)
{
	std::vector<std::string> values(n, val);
	m_data = Tools::range2str(values.begin(), values.end(), ",", "'");
}

bool Other::compatible(const Config& cfg)
{
	if (cfg.size() < 3)
	{
		return false;
	}
	return cfg.front() == DataType::Rest();
}

Data* Other::create(const Config& cfg)
{
	if (cfg.size() > 3)
	{
		return new Other(cfg[1], atoi(cfg[2].c_str()), cfg[3]);
	}
	return 0;
}

