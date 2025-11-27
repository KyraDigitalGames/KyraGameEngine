#ifndef KYRAGAMEENGINE_LOG_LOGMESSAGE_HPP
#define KYRAGAMEENGINE_LOG_LOGMESSAGE_HPP

#include <string>
#include <thread>

namespace kyra {

	enum class LogLevel {
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal
	};

	struct LogMessage {
		LogLevel level;
		std::string text;
		uint64_t frame;
		std::thread::id threadId;
	};

}

#endif