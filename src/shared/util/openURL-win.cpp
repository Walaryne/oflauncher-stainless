//
// Created by Digit on 8/10/2020.
//

#include "openURL.h"

void openURL(const std::string &url) {
	std::string cmd = "start " + url;
	system(cmd.c_str());
}