#ifndef DATA_SIULATOR_FACTORY_H
#define DATA_SIULATOR_FACTORY_H

#include "data.h"
#include "tools.h"
#include <vector>
#include <string>

// 工厂类
class Factory
{
public:
	// 检查数据生成器的函数指针类型
	typedef bool (*CompatibleFunc) (const Config& cfg);

	// 创建数据生成器的函数指针类型
	typedef Data* (*CreateFunc) (const Config& cfg);

	// 获取唯一实例
	static Factory* getInstance();

	// 创建数据生成器
	Data* create(const std::vector<std::string>& args);

	// 数据生成器注册
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

