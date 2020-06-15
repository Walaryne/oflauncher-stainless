#include "main.h"

int main() {

    //Initialize cURL for usage program wide
    curl_global_init(CURL_GLOBAL_ALL);

	OFSGui g;

	if(!g.isOk()) {
		std::cout << g.getError() << std::endl;
		return 1;
	}

	while(g.loop()) {
	}
}
