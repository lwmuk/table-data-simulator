#include "factory.h"
#include <algorithm>

Factory* Factory::getInstance()
{
	static Factory* instance = 0;
	if (instance == 0)
	{
		instance = new Factory;
	}
	return instance;
}

Factory::Factory()
{

}

Data* Factory::create(const Config& args)
{
	if (args.size() < 2)
	{
		_LOG_ERROR("Create worker failed.[Reason: arguement less than 2]");
		return 0;
	}

	DataList::const_iterator iter = m_dataList.begin();
	for ( ; iter != m_dataList.end(); ++iter)
	{
		if ((iter->m_compatibleFunc)(args))
		{
			return (iter->m_createFunc)(args);
		}
	}
	
	return 0;
}

bool Factory::regData(const std::string& name, CompatibleFunc com, CreateFunc create)
{
	DataItem data(name, com, create);
	DataList::const_iterator iter = std::find(m_dataList.begin(), m_dataList.end(), data);
	if (iter != m_dataList.end())
	{
		return false;
	}

	m_dataList.push_back(data);

	return true;
}


