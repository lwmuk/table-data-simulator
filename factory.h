#ifndef DATA_SIULATOR_FACTORY_H
#define DATA_SIULATOR_FACTORY_H

#include "data.h"
#include "tools.h"
#include <vector>
#include <string>

// ������
class Factory
{
public:
	// ��������������ĺ���ָ������
	typedef bool (*CompatibleFunc) (const Config& cfg);

	// ���������������ĺ���ָ������
	typedef Data* (*CreateFunc) (const Config& cfg);

	// ��ȡΨһʵ��
	static Factory* getInstance();

	// ��������������
	Data* create(const std::vector<std::string>& args);

	// ����������ע��
	bool regData(const std::string& name, CompatibleFunc com, CreateFunc create);

private:
	Factory();
	Factory(const Factory& rhs);
	Factory& operator=(const Factory& rhs);

private:
	struct DataItem
	{
		DataItem(const std::string& name, CompatibleFunc com, CreateFunc create)
			: m_name(name), m_compatibleFunc(com), m_createFunc(create) {}
		
		bool operator==(const DataItem& rhs) const
		{
			return m_name == rhs.m_name;
		}

		std::string m_name;
		CompatibleFunc m_compatibleFunc;
		CreateFunc m_createFunc;
	};
	typedef std::vector<DataItem> DataList;

	DataList m_dataList;
};

#endif

