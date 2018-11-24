#include <iostream>
#include <string>
#include <sstream>

#include "log.hpp"

using namespace std;

void log(char level, string component, string message) {
    cout << level << " [" << component << "] " << message << endl;
}

void emuPanic(string component, string message, const char *expr, const char *file, int line) {
    stringstream error;
    error << "PSEmu PANIC.";

    if (expr && file)
         error << " Assertion " << expr << " at " << file << ":" << line << " failed.";

    log('P', component, error.str());
    log('P', component, message);

    exit(-1);
}
