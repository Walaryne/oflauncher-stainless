#include "gui/OFSGui.h"
#include "net/OFSNet.h"
#include <iostream>

int main() {

    //Initialize cURL for usage program wide
    curl_global_init(CURL_GLOBAL_ALL);

	OFSGui g;
	if(!g.isOk()) {
		std::cout << g.getError() << std::endl;
		return 1;
	}
	OFSNet::test();
	while(g.loop()) {
	}
}
