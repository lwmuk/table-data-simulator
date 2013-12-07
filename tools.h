#ifndef DATA_SIMULATOR_TOOLS_H
#define DATA_SIMULATOR_TOOLS_H

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>

// 右边表达式中x不带括号，方便输入内容
// 如：i = 5; _LOG_ERROR("i = " << i);
#define _LOG_ERROR(x) std::cout << "[ERROR]"<< __FILE__ << ":" << __LINE__ << "  " << x << std::endl;
#define _LOG_INFO(x) std::cout << "[INFO]"<< __FILE__ << ":" << __LINE__ << "  " << x << std::endl;


// 工具类，包含一些工具函数
class Tools
{
public:
	// time_t转换为14或19位时间格式化字符串
	static std::string time2str(time_t time, const std::string& pattern = "");

	// 14位或19位时间格式化字符串转换为time_t
	static time_t str2time(const std::string& str);

	/**
	 * 将容器里的元素连接为一个字符串
	 * @param first 序列第一个元素的位置
	 * @param last 序列最后一个元素的下一位置
	 * @param delimiter 分隔符
	 * @param mark 修饰符
	 * @return 返回结果字符串
	 **/
	// svec = {1, 2, 3, 4};
	// str  = range2str(svec.begin(), svec.end(), ",", "'");
	// str == "'1','2','3','4'";
	template<class InputIterator>
		static std::string range2str(InputIterator first, InputIterator last, const std::string& delimiter = "", const std::string& mark = "");

	// 将字符串转换为字符串向量，以空白字符作为分隔符
	static void str2vec(const std::string& str, std::vector<std::string>& vec);

	// 数值转换为字符串
	template<class Number>
		static std::string number2str(Number val);

	/**
	 * 字符串转换为数值
	 * @param str 需要转换的字符串
	 * @param 类型为Number的匿名参数只是为了提供给编译器推断Number的具体类型
	 * @return 返回转换后的数值
	 **/
	// 使用方法一：int i = str2number("1234", i);
	// 使用方法二：double d = str2number<double>(".1234");
	template<class Number>
		static Number str2number(const std::string& str, Number = Number());
	template<class Number>
		static Number str2number(const char* str, Number = Number());
	static int str2int(const std::string& str) { return str2number<int>(str); }
	static double str2double(const std::string& str) { return str2number<double>(str); }

	// 返回被mark括起来的str
	template<class Input>
		static std::string withMark(Input in, const std::string& mark = "'");

};



template<class InputIterator>
	std::string Tools::range2str(InputIterator first, InputIterator last, const std::string& delimiter, const std::string& mark)
{
	std::ostringstream oss;
	InputIterator it = --last;
	++last;
	while (first != last)
	{
		oss << mark << *first << mark;
		if (first != it)
		{
			oss << delimiter;
		}
		++first;
	}

	return oss.str();
}

template<class Number>
	std::string Tools::number2str(Number val)
{
	std::ostringstream oss;
	oss << val;

	return oss.str();
}

template<class Number>
	Number Tools::str2number(const std::string& str, Number)
{
	if (str.empty())
	{
		return Number();
	}

	std::stringstream sst;
	sst << str;
	Number num;
	sst >> num;
	
	return num;
}

template<class Number>
	Number Tools::str2number(const char* str, Number)
{
	return Tools::str2number<Number>(std::string(str));
}

template<class Input>
	std::string Tools::withMark(Input in, const std::string& mark)
{
	std::ostringstream oss;
	oss << mark << in << mark;

	return oss.str();
}

#endif

