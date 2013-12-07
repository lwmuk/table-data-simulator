#ifndef DATA_SIMULATOR_DATA_TYPE_H
#define DATA_SIMULATOR_DATA_TYPE_H

#include <string>

// 数据类型
class DataType
{
public:
	#define defunc(name) static const std::string& name();

	defunc(Rest);
	defunc(Constant);
	defunc(Time14);
	defunc(Time19);
	defunc(Integer);
	defunc(Double);
	defunc(Single);
	defunc(All);
};

#endif

