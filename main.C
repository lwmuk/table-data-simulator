#include "tools.h"
#include "datatype.h"
#include "factory.h"
#include "config.h"
#include "datamanager.h"
#include "constant.h"
#include "other.h"
#include "integer.h"
#include "double.h"
#include "singleselector.h"
#include "allselector.h"
#include "timer.h"
#include <iterator>
#include <fstream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout<< "Usage: simulator infile [outfile]" << std::endl;
		std::cout << "If the outfile not specified, std::cout will be used." << std::endl;
		std::cout << "Example: ./simulator example.cfg" << std::endl;
		return 0;
	}

	ConfigManager::getInstance()->startup(argv[1]);

	if (argc > 2)
	{
		std::ofstream fout(argv[2], std::ofstream::trunc | std::ofstream::out);
		DataManager::getInstance()->generateData(fout);
	}
	else
	{
		DataManager::getInstance()->generateData();
	}

	return 0;
}
