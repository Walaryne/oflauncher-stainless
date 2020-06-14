#include <iostream>
#include "gui/OFSGui.h"
#include "net/OFSNet.h"

int main() {
    OFSGui g;
    g.init();
    OFSNet::test();
}
