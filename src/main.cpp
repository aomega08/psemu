#include <iostream>

#include "Emulator.hpp"
#include "types.hpp"

using namespace std;

int main() {
    Emulator psx;

    psx.loadBios("SCPH1001.BIN");
    psx.run();

	return 0;
}