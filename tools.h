#ifndef DATA_SIMULATOR_TOOLS_H
#define DATA_SIMULATOR_TOOLS_H

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>

// �ұ߱��ʽ��x�������ţ�������������
// �磺i = 5; _LOG_ERROR("i = " << i);
#define _LOG_ERROR(x) std::cout << "[ERROR]"<< __FILE__ << ":" << __LINE__ << "  " << x << std::endl;
#define _LOG_INFO(x) std::cout << "[INFO]"<< __FILE__ << ":" << __LINE__ << "  " << x << std::endl;


// �����࣬����һЩ���ߺ���
class Tools
{
public:
	// time_tת��Ϊ14��19λʱ���ʽ���ַ���
	static std::string time2str(time_t time, const std::string& pattern = "");

	// 14λ��19λʱ���ʽ���ַ���ת��Ϊtime_t
	static time_t str2time(const std::string& str);

	/**
	 * ���������Ԫ������Ϊһ���ַ���
	 * @param first ���е�һ��Ԫ�ص�λ��
	 * @param last �������һ��Ԫ�ص���һλ��
	 * @param delimiter �ָ���
	 * @param mark ���η�
	 * @return ���ؽ���ַ���
	 **/
	// svec = {1, 2, 3, 4};
	// str  = range2str(svec.begin(), svec.end(), ",", "'");
	// str == "'1','2','3','4'";
	template<class InputIterator>
		static std::string range2str(InputIterator first, InputIterator last, const std::string& delimiter = "", const std::string& mark = "");

	// ���ַ���ת��Ϊ�ַ����������Կհ��ַ���Ϊ�ָ���
	static void str2vec(const std::string& str, std::vector<std::string>& vec);

	// ��ֵת��Ϊ�ַ���
	template<class Number>
		static std::string number2str(Number val);

	/**
	 * �ַ���ת��Ϊ��ֵ
	 * @param str ��Ҫת�����ַ���
	 * @param ����ΪNumber����������ֻ��Ϊ���ṩ���������ƶ�Number�ľ�������
	 * @return ����ת�������ֵ
	 **/
	// ʹ�÷���һ��int i = str2number("1234", i);
	// ʹ�÷�������double d = str2number<double>(".1234");
	template<class Number>
		static Number str2number(const std::string& str, Number = Number());
	template<class Number>
		static Number str2number(const char* str, Number = Number());
	static int str2int(const std::string& str) { return str2number<int>(str); }
	static double str2double(const std::string& str) { return str2number<double>(str); }

	// ���ر�mark��������str
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

