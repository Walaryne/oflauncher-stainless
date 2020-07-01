//
// Created by walaryne on 7/1/20.
//

#include "OFSUtil.h"

std::string OFSUtil::exp_env(const std::string &s) {
	if(s.find("${") == std::string::npos)
		return s;

	std::string pre = s.substr(0, s.find("${"));
	std::string post = s.substr(s.find("${") + 2);

	if(post.find('}') == std::string::npos)
		return s;

	std::string variable = post.substr(0, post.find('}'));
	std::string value;

	post = post.substr(post.find('}') + 1);

	const char *v = getenv(variable.c_str());
	if(v != nullptr)
		value = std::string(v);

	return exp_env(pre + value + post);
};