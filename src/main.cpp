#include "main.h"

void checkDirsExist() {
	if(!fs::exists("remote")) {
		fs::create_directory("remote");
	}
	if(!fs::exists("local")) {
		fs::create_directory("local");
	}
}

int main() {

    //Initialize cURL for usage program wide
    curl_global_init(CURL_GLOBAL_ALL);

	OFSNet net("http://127.0.0.1");

	checkDirsExist();

	//To Fenteale: This should be called the moment that the "Update" button is pressed.
	net.fetchDatabase();

	//To Fenteale: Later on you'll have direct access to two automated functions.
	//These will be updateGame and verifyIntegrity respectively.
	//I'll try to add some callbacks and stuff so you can use progress bars!

	OFSGui g;

	if(!g.isOk()) {
		std::cout << g.getError() << std::endl;
		return 1;
	}

	while(g.loop()) {
	}
}
