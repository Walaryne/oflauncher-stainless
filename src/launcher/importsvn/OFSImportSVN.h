//
// Created by fenteale on 2/11/21.
//

#ifndef OFLAUNCHER_STAINLESS_OFSIMPORTSVN_H
#define OFLAUNCHER_STAINLESS_OFSIMPORTSVN_H

#include "OFFilesystem.h"

class OFSImportSVN {
public:
	OFSImportSVN(fs::path svnInstall);
	bool isSVN() const;

private:
	fs::path svnInstall;
};

#endif // OFLAUNCHER_STAINLESS_OFSIMPORTSVN_H
