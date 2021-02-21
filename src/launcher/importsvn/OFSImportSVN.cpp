//
// Created by fenteale on 2/11/21.
//

#include "OFSImportSVN.h"

OFSImportSVN::OFSImportSVN(fs::path svnInstall, OFSDatabase *db) : svnInstall(svnInstall), db(db) {}

bool OFSImportSVN::isSVN() const {
	return fs::exists(svnInstall / ".svn");
}

int OFSImportSVN::convertSVN() {
	if(!isSVN())
		return -1;

	fs::remove_all(svnInstall / ".svn");


	return db->compareIntegrity();;

}