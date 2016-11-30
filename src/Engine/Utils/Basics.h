#pragma once

#include <memory>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS
#else
#define UNIX
#endif

#define SINGLETON(className) \
public: \
	className(className const&) = delete; \
	void operator=(className const&) = delete; \
	static className& instance() { static className _i; return _i; } \
private: \
	explicit className(); \
	~className();

#define MAKE_SMART(class) using sp ## class = std::shared_ptr<class>;
#define SMART(class,...) std::make_shared<class>(__VA_ARGS__);