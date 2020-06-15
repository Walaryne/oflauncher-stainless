//
// Created by walaryne on 6/14/20.
//

#include "OFSNet.h"

#include <utility>

OFSNet::OFSNet(std::string serverURL) {
    p_serverURL = std::move(serverURL);
}

OFSNet::OFSNet() {
    p_serverURL = nullptr;
}

std::string OFSNet::getServerURL() {
    return p_serverURL;
}

void OFSNet::setServerURL(std::string URL) {
    p_serverURL = std::move(URL);
}

void OFSNet::fetchDatabase() {

}
