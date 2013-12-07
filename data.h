#ifndef DATA_SIMULATOR_DATA_H
#define DATA_SIMULATOR_DATA_H

#include <string>
#include <vector>

// 数据生成器基类
class Data
{
public:
	// 数据生成器的循环类型
	enum Loop {NOLOOP = 0, INNERLOOP, OUTERLOOP};

	Data(const std::string& name, Loop loop = NOLOOP) : m_name(name), m_loop(loop) {}

	virtual ~Data() {}

	// 用于循环类数据生成器准备下一次状态
	virtual bool next() { return false; }

	// 用于重置循环状态
	virtual void reset() {}

	// 用于生成数据
	virtual std::string data() const = 0;

	// 获取数据的字段名字
	const std::string& name() const { return m_name; }

	// 获取数据生成器的循环类型
	Loop loop() const { return m_loop; }

private:
	std::string m_name;
	Loop m_loop;
};

// 配置数据类型
typedef std::vector<std::string> Config;

#endif

