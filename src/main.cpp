#include <iostream>

#include "Memory.hpp"
#include "types.hpp"

using namespace std;

int main() {
    Memory memory;

    memory.loadBios("SCPH1001.BIN");

	return 0;
}