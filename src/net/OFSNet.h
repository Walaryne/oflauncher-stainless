//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSNET_H
#define OFLAUNCHER_STAINLESS_OFSNET_H
#include "curl_easy.h"
#include "curl_exception.h"

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;

class OFSNet {
public:
	static void test();
};


#endif //OFLAUNCHER_STAINLESS_OFSNET_H
