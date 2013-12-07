#include "tools.h"
#include <vector>
#include <sstream>
#include <iomanip>

std::string Tools::time2str(time_t time, const std::string& pattern)
{
	struct tm* pTm = localtime(&time);
	if (!pTm)
	{
		return std::string();
	}

	std::ostringstream oss;
	if (pattern.empty() || pattern == "14")
	{
		oss << std::setw(4) << std::setfill('0') << pTm->tm_year + 1900
			<< std::setw(2) << std::setfill('0') << pTm->tm_mon + 1
			<< std::setw(2) << std::setfill('0') << pTm->tm_mday 
			<< std::setw(2) << std::setfill('0') << pTm->tm_hour
			<< std::setw(2) << std::setfill('0') << pTm->tm_min
			<< std::setw(2) << std::setfill('0') << pTm->tm_sec;
	}
	else if (pattern == "19")
	{
		oss << std::setw(4) << std::setfill('0') << pTm->tm_year + 1900 << "-"
			<< std::setw(2) << std::setfill('0') << pTm->tm_mon + 1 << "-"
			<< std::setw(2) << std::setfill('0') << pTm->tm_mday << " "
			<< std::setw(2) << std::setfill('0') << pTm->tm_hour << ":"
			<< std::setw(2) << std::setfill('0') << pTm->tm_min << ":"
			<< std::setw(2) << std::setfill('0') << pTm->tm_sec;
	}

	return oss.str();
}

time_t Tools::str2time(const std::string& str)
{
	if (str.size() != 14 && str.size() != 19)
	{
		return 0;
	}

	int y, mon, d, h, min, sec;

	if (str.size() == 14)
	{
		y = str2int(str.substr(0, 4));
		mon = str2int(str.substr(4, 2));
		d = str2int(str.substr(6, 2));
		h = str2int(str.substr(8, 2));
		min = str2int(str.substr(10, 2));
		sec = str2int(str.substr(12, 2));
	}
	else
	{
		y = str2int(str.substr(0, 4));
		mon = str2int(str.substr(5, 2));
		d = str2int(str.substr(8, 2));
		h = str2int(str.substr(11, 2));
		min = str2int(str.substr(14, 2));
		sec = str2int(str.substr(17, 2));
	}

	time_t cur_time = time(0);
	struct tm* time_cur = localtime(&cur_time);
	struct tm new_time;
	new_time.tm_year = y - 1900;
	new_time.tm_mon = mon - 1;
	new_time.tm_mday = d;
	new_time.tm_hour = h;
	new_time.tm_min = min;
	new_time.tm_sec = sec;
	new_time.tm_isdst = time_cur->tm_isdst;

	return mktime(&new_time);
}

void Tools::str2vec(const std::string& str, std::vector<std::string>& vec)
{
	vec.clear();

	// 标记是否在双引号内
	bool inner = false;
	// 为了处理方便，在str后面加个空格符
	std::string tmp = str + ' ';
	std::string out;
	for (int i = 0; i < tmp.size() - 1; )
	{
		if (tmp[i] == '\\' && tmp[i+1] == '"')
		{
			out += '"';
			i += 2;
			continue;
		}
		else if (tmp[i] == '"')
		{
			if (inner)
			{
				inner = false;
				vec.push_back(out);
				out.clear();
			}
			else
			{
				inner = true;
			}
		}
		else if (inner)
		{
			out += tmp[i];
		}
		else if (tmp[i] == ' ' || tmp[i] == '\t')
		{
			if (!out.empty())
			{
				vec.push_back(out);
				out.clear();
			}
		}
		else
		{
			out += tmp[i];
		}

		++i;
	}

	if (!out.empty())
	{
		vec.push_back(out);
	}
}

