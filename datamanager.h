#ifndef DATA_SIMULATOR_DATA_MANAGER_H
#define DATA_SIMULATOR_DATA_MANAGER_H

#include "data.h"
#include <iostream>
#include <map>

// ���������������࣬���𴴽��������������������Լ���������

class DataManager
{
public:
	// ��ȡΨһʵ��
	static DataManager* getInstance();

	// ��������
	~DataManager();
	
	// ��������
	bool generateData(std::ostream& os = std::cout);

private:
	// ����������
	typedef std::vector<std::string> Row;

	// ����������
	typedef std::vector<Row> RowList;

	// ����������ָ���б�����
	typedef std::vector<Data*> DataPtrList;

	// ��������������
	bool initDataList();

	// �����ѭ��������������Ϊ��һ״̬
	bool outerNext();
	void outerData(Row& name, RowList& values);
	
	// ���ڲ�ѭ��������������Ϊ��һ״̬
	bool innerNext();
	void innerData(Row& name, RowList& values);

	// ��ѭ����������������
	void noLoopData(Row& name, Row& value);

	// ��������������
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

