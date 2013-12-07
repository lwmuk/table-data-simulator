#ifndef DATA_SIMULATOR_DATA_MANAGER_H
#define DATA_SIMULATOR_DATA_MANAGER_H

#include "data.h"
#include <iostream>
#include <map>

// 数据生成器管理类，负责创建、管理数据生成器，以及生成数据

class DataManager
{
public:
	// 获取唯一实例
	static DataManager* getInstance();

	// 析构函数
	~DataManager();
	
	// 生成数据
	bool generateData(std::ostream& os = std::cout);

private:
	// 列数据类型
	typedef std::vector<std::string> Row;

	// 表数据类型
	typedef std::vector<Row> RowList;

	// 数据生成器指针列表类型
	typedef std::vector<Data*> DataPtrList;

	// 创建数据生成器
	bool initDataList();

	// 将外层循环数据生成器置为下一状态
	bool outerNext();
	void outerData(Row& name, RowList& values);
	
	// 将内层循环数据生成器置为下一状态
	bool innerNext();
	void innerData(Row& name, RowList& values);

	// 无循环数据生成器数据
	void noLoopData(Row& name, Row& value);

	// 清理数据生成器
	void delDataPtr(DataPtrList& lst);

	DataManager();
	DataManager(const DataManager& rhs);
	DataManager& operator=(const DataManager& rhs);

private:
	DataPtrList m_outerLoopList;
	DataPtrList m_innerLoopList;
	DataPtrList m_noLoopList;
};

#endif

