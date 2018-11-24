#pragma once

#include <string>
#include <sstream>

void log(char level, std::string component, std::string message);

void emuPanic(std::string component, std::string message, const char *expr = nullptr, const char *file = nullptr, int line = 0);
void emuPanic(std::string component, std::stringstream message, const char *expr = nullptr, const char *file = nullptr, int line = 0);

#define FAIL_IF(expr, component, message) (void)(!(expr) || (emuPanic(component, message, #expr, __FILE__, __LINE__), 0))
