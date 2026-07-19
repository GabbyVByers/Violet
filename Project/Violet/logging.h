//
///* logging.h */
//
//#pragma once
//
//#include <stdexcept>
//
//#ifndef Vi
//#define Vi Vi
//#endif /* Vi */
//
//#ifndef assertCondition
//#define assertCondition assertCondition
//#endif /* assertCondition */
//
//namespace Vi {
//
//	class Log {
//	public:
//
//		static void assertCondition(const bool condition, const char* message = "") {
//			if (condition) return;
//			throw std::runtime_error(message);
//		}
//
//	private:
//		Log()                        = delete;
//		Log(const Log&)              = delete;
//		Log(Log&&)                   = delete;
//		void operator = (const Log&) = delete;
//		void operator = (Log&&)      = delete;
//	};
//}
//
//