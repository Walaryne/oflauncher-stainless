//
// Created by fenteale on 2/11/21.
//

#ifndef OFLAUNCHER_STAINLESS_OFSIMPORTSVN_H
#define OFLAUNCHER_STAINLESS_OFSIMPORTSVN_H

#include "OFFilesystem.h"
#include "../db/OFSDatabase.h"

class OFSImportSVN {
public:
	OFSImportSVN(fs::path svnInstall, OFSDatabase* db);
	bool isSVN() const;
	int convertSVN();

private:
	fs::path svnInstall;
	OFSDatabase *db;
};

#endif // OFLAUNCHER_STAINLESS_OFSIMPORTSVN_H
