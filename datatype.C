#include "datatype.h"

#define defund(_name, _value) \
const std::string& DataType::_name() \
{ \
	static const std::string str(_value); \
	return str; \
}

defund(Rest, "rest");
defund(Constant, "constant");
defund(Time14, "time14");
defund(Time19, "time19");
defund(Integer, "integer");
defund(Double, "double");
defund(Single, "single");
defund(All, "all");

