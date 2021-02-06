//
// Created by fenteale on 8/9/20.
//
#include "openURL.h"


void openURL(const std::string &url) {
	std::string cmd = "xdg-open " + url;
	system(cmd.c_str());
}