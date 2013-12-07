#include "config.h"
#include "tools.h"
#include <fstream>

ConfigManager* ConfigManager::getInstance()
{
	static ConfigManager* instance = 0;
	if (instance == 0)
	{
		instance = new ConfigManager;
	}
	return instance;
}

ConfigManager::ConfigManager()
{
	
}

ConfigManager::~ConfigManager()
{

}

bool ConfigManager::startup(const std::string& configFile)
{
	if (configFile.empty())
	{
		_LOG_ERROR("Config file not specified.");
		return false;
	}

	m_configFile = configFile;
	
	return loadConfig();
}

bool ConfigManager::loadConfig()
{
	std::ifstream fin(m_configFile.c_str());
	if (fin.bad())
	{
		_LOG_ERROR("Config file not existed.");
		return false;
	}

	std::string line;
	Config cfg;
	while (std::getline(fin, line))
	{
		if (line.empty() || line[0] == '#')
		{
			continue;
		}

		_LOG_INFO(line);

		Tools::str2vec(line, cfg);
		if (cfg.size() > 1 && cfg.front() == "table")
		{
			m_tableName = cfg[1];
			continue;
		}
		m_configList.push_back(cfg);
	}

	return true;
}

