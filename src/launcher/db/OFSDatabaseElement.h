//
// Created by fenteale on 6/3/21.
//

#ifndef OFLAUNCHER_STAINLESS_OFSDATABASEELEMENT_H
#define OFLAUNCHER_STAINLESS_OFSDATABASEELEMENT_H
#include <string>

struct OFDbElement {
	std::string path;
	std::string checksum;
	bool sig;
	std::string sigData;

	OFDbElement(std::string &path, std::string &checksum, bool sig = false, std::string sigData="")
		: path(path), checksum(checksum), sig(sig), sigData(std::move(sigData)) {}
};

#endif // OFLAUNCHER_STAINLESS_OFSDATABASEELEMENT_H
