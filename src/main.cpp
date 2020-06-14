#include "gui/OFSGui.h"
#include "net/OFSNet.h"
#include <iostream>

int main() {
	OFSGui g;
	if(!g.isOk()) {
		std::cout << g.getError() << std::endl;
		return 1;
	}
	OFSNet::test();
}
