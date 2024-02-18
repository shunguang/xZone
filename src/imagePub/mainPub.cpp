// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

#include "UpdateCamSubscriber.h"
#include "ImagePublisher.h"
#include "libMsg/ImageTypeObject.h"
#include "libUtil/Util.h"

#include "libUtil/AppLog.h"
#include "libCfg/Cfg.h"

#include <mutex>
#include <shared_mutex>


using namespace app;

int main(int argc, char* argv[])
{

	std::cout << "inital path: " << boost::filesystem::initial_path() << std::endl;
	/*std::cout << "Have " << argc << " arguments:\n";
	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << "\n";
	}*/

	if (argc <= 1) {
		std::cout << "pass a config file" << std::endl;
		return 0;
	}

	CfgPtr cfg(new Cfg());
	cfg->readFromFile(argv[1]);

	std::printf("used cfg=<%s>\n", argv[1]);

	const std::string logFilename("logPub.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	bool use_environment_qos = true;

	std::shared_ptr<std::shared_mutex> mutex;

	// std::thread subscriber(createUpdateCamSubscriber, mutex, cfg, use_environment_qos);
	// subscriber.join();

	registerImageTypes();
	// pass hz frequency param
	// std::vector<std::thread> threads;

	if (const char* transport = std::getenv("XZONE_TRANSPORT")) {
		std::cout << "The transport in the config.xml isn't being used" << std::endl;
		std::cout << "The program will use whatever " << transport << " corresponds to" << std::endl;
		cfg->setTransport(*transport - '0');
		std::cout << std::endl << std::endl;
	}

	if (argc >= 3 && std::string(argv[2]) == "pcktsz") { // ./imagePub config.xml pcktsz
		std::cout << "Packet Size changes" << std::endl;
		if (argc == 4) {
			std::cout << "Max message packet size " << std::string(argv[3]) << std::endl;
			int max_message_size = std::stoi(std::string(argv[3]));
			ImagePublisher mypub(mutex, cfg, 20);
			if (mypub.init(cfg, use_environment_qos)) {
				mypub.runPacketSizeVariable(max_message_size);
			}
		}
		else {
			std::cout << "You must specify max_message size as the last argument (in bytes)" << std::endl;
		}
	} else {
		std::cout << "Frequency changes" << std::endl;
		const int numSamples = cfg->getCam().numSamples_;
		int frameNum = 1;
		for (double hz = cfg->getCam().frequency_.start; hz <= cfg->getCam().frequency_.end; hz += cfg->getCam().frequency_.step) {
			std::cout << "On frequency #" << hz << std::endl;

			ImagePublisher mypub(mutex, cfg, hz);

			if (mypub.init(cfg, use_environment_qos)) {
				mypub.runFrequency(std::ref(frameNum));
			}

			std::cout << "in MainPub finished frequency " << hz << std::endl << std::endl;
		}
	
	}

	app::endLogThread();
	return 0;
}

/*
{
		auto [start, step, end] = cfgCamPtr_->frequency_;
		for (uint32_t iFreq = start; nSamples < end; nSamples += step) {
		}
}

*/