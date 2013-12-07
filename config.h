#ifndef DATA_SIMULATOR_CONFIG_H
#define DATA_SIMULATOR_CONFIG_H

#include "data.h"

// 配置管理类，负责读取配置文件

class ConfigManager
{
public:
	// 获取唯一实例
	static ConfigManager* getInstance();

	// 析构函数
	~ConfigManager();

	// 启动函数
	bool startup(const std::string& configFile);

	// 获取配置列表
	const std::vector<Config>& configList() const { return m_configList; }

	// 获取表名
	const std::string& tableName() const { return m_tableName; }

private:
	// 读取配置
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

