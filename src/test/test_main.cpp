#include "libUtil/util.h"

int test_mat_part1(int argc, char* argv[]);

using namespace std;
using namespace app;
int main(int argc, char* argv[])
{
	xmlCfgFilePath

		readCfg(xmlCfgFilePath)
	//const string logFilename("./log.txt");
	//const bool showInConsole = true;

	startLogThread(cfg.log.logFilename, cfg.log.showInConsole);

	APP_LOG( "test1,i=%d", 10);
	APP_ASSERT(2 == 2, "xyz=%d,egg=%s", 3, "passed");
	APP_EXIT("xyz=%d,efg=%s", 2, "quit");
	endLogThread();
	return 0;
}


readCfg( xmlCfgFilePath )
{

	//figure out config file
	string cfgFile = locateCfgFile(argc, argv);
	printf("used cfg=<%s>\n", cfgFile.c_str());

	//read cfg file
	CfgPtr cfg(new Cfg());
	try {
		cfg->readFromFile(cfgFile.c_str());
	}
	catch (const std::overflow_error& e) {
		printf("%s\n", e.what());
	}
	printf("cfg read successfully\n");

	//start log thread
	startLog(cfg);
}
