//
// Created by walaryne on 6/14/20.
//

#include "OFSNet.h"
void OFSNet::test() {
	curl_easy easy;
	// Add some option to the curl_easy object.
	easy.add<CURLOPT_URL>("http://www.google.it");
	easy.add<CURLOPT_FOLLOWLOCATION>(1L);
	try {
		// Execute the request.
		easy.perform();

	} catch (curl_easy_exception &error) {
		// If you want to get the entire error stack we can do:
		curlcpp_traceback errors = error.get_traceback();
		// Otherwise we could print the stack like this:
		error.print_traceback();
	}
}