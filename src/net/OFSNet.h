//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSNET_H
#define OFLAUNCHER_STAINLESS_OFSNET_H
#include <curl/curl.h>
#include <string>

class OFSNet {
public:
    OFSNet(std::string serverURL);
    OFSNet();
	std::string getServerURL();
	void setServerURL(std::string URL);
	void fetchDatabase();
	void downloadFile(std::string path);


private:
    std::string p_serverURL;
    std::string p_dbFileName;
};

#endif // OFLAUNCHER_STAINLESS_OFSNET_H
