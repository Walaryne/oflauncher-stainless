//
// Created by fenteale on 2/11/21.
//

#include "OFSImportSVN.h"

OFSImportSVN::OFSImportSVN(fs::path svnInstall) : svnInstall(svnInstall) {}

bool OFSImportSVN::isSVN() const {
	return fs::exists(svnInstall / ".svn");
}