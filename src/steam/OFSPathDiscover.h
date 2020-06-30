/*
 * Created by Terradice on 6/29/20 14:20:00
 */

#ifndef OFLAUNCHER_STAINLESS_OFSPATH_H
#define OFLAUNCHER_STAINLESS_OFSPATH_H

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

static std::string exp_env(const std::string &s) {
	if(s.find("${") == std::string::npos)
		return s;

	std::string pre = s.substr(0, s.find("${"));
	std::string post = s.substr(s.find("${") + 2);

	if(post.find('}') == std::string::npos)
		return s;

	std::string variable = post.substr(0, post.find('}'));
	std::string value = "";

	post = post.substr(post.find('}') + 1);

	const char *v = getenv(variable.c_str());
	if(v != NULL)
		value = std::string(v);

	return exp_env(pre + value + post);
};

namespace fs = std::filesystem;

class OFSPathDiscover {
public:
	explicit OFSPathDiscover();
	std::string getSteamPath();
	std::string getSourcePath();
	std::string getSourcemodsPath();

private:
	fs::path steamPath;
	fs::path sourcePath;
	fs::path sourcemodsPath;
};

#endif // OFLAUNCHER_STAINLESS_OFSPATH_H
