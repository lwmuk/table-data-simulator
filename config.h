#ifndef DATA_SIMULATOR_CONFIG_H
#define DATA_SIMULATOR_CONFIG_H

#include "data.h"

// ���ù����࣬�����ȡ�����ļ�

class ConfigManager
{
public:
	// ��ȡΨһʵ��
	static ConfigManager* getInstance();

	// ��������
	~ConfigManager();

	// ��������
	bool startup(const std::string& configFile);

	// ��ȡ�����б�
	const std::vector<Config>& configList() const { return m_configList; }

	// ��ȡ����
	const std::string& tableName() const { return m_tableName; }

private:
	// ��ȡ����
	bool loadConfig();

	ConfigManager();
	ConfigManager(const ConfigManager& rhs);
	ConfigManager& operator=(const ConfigManager& rhs);

private:
	std::string m_configFile;
	std::vector<Config> m_configList;
	std::string m_tableName;
};

#endif

