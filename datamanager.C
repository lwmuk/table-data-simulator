#include "datamanager.h"
#include "factory.h"
#include "config.h"

DataManager* DataManager::getInstance()
{
	static DataManager* instance = 0;
	if (instance == 0)
	{
		instance = new DataManager;
	}
	return instance;
}

DataManager::DataManager()
{
	
}

DataManager::~DataManager()
{
	delDataPtr(m_noLoopList);
	delDataPtr(m_innerLoopList);
	delDataPtr(m_outerLoopList);
}

void DataManager::delDataPtr(DataPtrList& lst)
{
	DataPtrList::iterator iter = lst.begin();
	
	for ( ; iter != lst.end(); ++iter)
	{
		delete (*iter);
		*iter = 0;
	}
}

bool DataManager::generateData(std::ostream& os)
{
	if (!initDataList())
	{
		return false;
	}

	std::string nameStr, valueStr;
	nameStr = "insert into " + ConfigManager::getInstance()->tableName() + " (";
	valueStr = "values (";

	Row oName;
	RowList oValues;
	outerData(oName, oValues);

	Row iName;
	RowList iValues;
	innerData(iName, iValues);

	Row nName;
	Row nValue;
	noLoopData(nName, nValue);

	Row tName;
	RowList tValues;
	tName.insert(tName.end(), oName.begin(), oName.end());
	tName.insert(tName.end(), iName.begin(), iName.end());
	tName.insert(tName.end(), nName.begin(), nName.end());
	nameStr += Tools::range2str(tName.begin(), tName.end(), ",") + ") ";

	int cnt = 0;
	RowList::const_iterator iter = oValues.begin();
	do
	{
		Row ov;
		if (iter != oValues.end())
		{
			ov.insert(ov.end(), iter->begin(), iter->end());
			++iter;
		}

		RowList::const_iterator it = iValues.begin();
		do
		{
			Row row(ov);
			if (it != iValues.end())
			{
				row.insert(row.end(), it->begin(), it->end());
				++it;
			}

			noLoopData(nName, nValue);
			row.insert(row.end(), nValue.begin(), nValue.end());
			
			os << nameStr << valueStr
				<< Tools::range2str(row.begin(), row.end(), ",")
				<< ");\n";
			++cnt;

		} while (it != iValues.end());

	} while (iter != oValues.end());

	_LOG_INFO("Generate data OK, total " << cnt << " records.");
	return true;
}

bool DataManager::initDataList()
{
	const std::vector<Config>& cfgs = ConfigManager::getInstance()->configList();
	std::vector<Config>::const_iterator iter = cfgs.begin();
	int ncnt = 0, icnt = 0, ocnt = 0;
	for ( ; iter != cfgs.end(); ++iter)
	{
		Data* data = Factory::getInstance()->create(*iter);
		if (data != 0)
		{
			switch (data->loop())
			{
				case Data::NOLOOP :
					m_noLoopList.push_back(data);
					++ncnt;
					break;
				case Data::INNERLOOP :
					m_innerLoopList.push_back(data);
					++icnt;
					break;
				case Data::OUTERLOOP :
					m_outerLoopList.push_back(data);
					++ocnt;
					break;
				default:
					break;
			}
		}
	}
	
	_LOG_INFO("Data productor stat.[NOLOOP: " << ncnt << ", INNERLOOP: " << icnt << ", OUTERLOOP: " << ocnt << "]");
	
	return true;
}

void DataManager::noLoopData(Row& name, Row& value)
{
	name.clear();
	value.clear();

	DataPtrList::const_iterator iter = m_noLoopList.begin();
	for ( ; iter != m_noLoopList.end(); ++iter)
	{
		name.push_back((*iter)->name());
		value.push_back((*iter)->data());
	}
}

bool DataManager::outerNext()
{
	if (m_outerLoopList.empty())
	{
		return false;
	}

	DataPtrList::const_iterator iter = m_outerLoopList.begin();
	for ( ; iter != m_outerLoopList.end(); ++iter)
	{
		if (!(*iter)->next())
		{
			return false;
		}
	}

	return true;
}

void DataManager::outerData(Row& name, RowList& values)
{
	name.clear();
	values.clear();

	bool first = true;
	while (outerNext())
	{
		Row row;
		DataPtrList::const_iterator iter = m_outerLoopList.begin();
		for ( ; iter != m_outerLoopList.end(); ++iter)
		{
			if (first)
			{
				name.push_back((*iter)->name());
			}

			row.push_back((*iter)->data());
		}

		first = false;
		values.push_back(row);
	}
}

bool DataManager::innerNext()
{
	if (m_innerLoopList.empty())
	{
		return false;
	}

	DataPtrList::const_iterator iter = m_innerLoopList.begin();
	for ( ; iter != m_innerLoopList.end(); ++iter)
	{
		if ((*iter)->next())
		{
			return true;
		}
	}

	return false;
}

void DataManager::innerData(Row& name, RowList& values)
{
	name.clear();
	values.clear();

	bool first = true;
	while (innerNext())
	{
		Row row;
		DataPtrList::const_iterator iter = m_innerLoopList.begin();
		for ( ; iter != m_innerLoopList.end(); ++iter)
		{
			if (first)
			{
				name.push_back((*iter)->name());
			}

			row.push_back((*iter)->data());
		}

		first = false;
		values.push_back(row);
	}
}

