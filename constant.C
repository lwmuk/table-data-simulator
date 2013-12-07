#include "constant.h"
#include "factory.h"
#include "datatype.h"
#include "tools.h"

static bool constant = Factory::getInstance()->regData(DataType::Constant(), Constant::compatible, Constant::create);

Constant::Constant(const std::string& name, const std::string& val)
	: Data(name), m_value(Tools::withMark(val))
{

}

bool Constant::compatible(const Config& cfg)
{
	if (cfg.size() < 2)
	{
		return false;
	}
	return cfg.front() == DataType::Constant();
}

Data* Constant::create(const Config& cfg)
{
	if (cfg.size() > 2)
	{
		return new Constant(cfg[1], cfg[2]);
	}
	return 0;
}

