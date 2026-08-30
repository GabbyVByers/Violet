
/*
 *   Source File [log.cpp]
 */

#include <Violet.h>

namespace Vi {

	void Log::error(const char* FILE, int LINE) {
		std::filesystem::path filepath{ FILE };
		std::string filename = filepath.filename().string();
		std::cerr << "\033[31mAn Error Occurred!\033[0m\n";
		std::cerr << std::format("\033[32mFILE: \033[0m'{}'\n", filename);
		std::cerr << std::format("\033[32mLINE: \033[0m{}\n", std::to_string(LINE));
	}

	void Log::error(const char* message) {
		std::cerr << "\033[31mError: \033[0m";
		std::cerr << message << std::endl;
	}

	void Log::error(const std::string& message) {
		std::cerr << "\033[31mError: \033[0m";
		std::cerr << message << std::endl;
	}
}

