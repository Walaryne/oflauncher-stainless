#ifndef OFLAUNCHER_STAINLESS_OFSLAYOUT_H
#define OFLAUNCHER_STAINLESS_OFSLAYOUT_H

#include "OFSGui.h"

#define DEFINE_LAYOUT(fname)                                                   \
	void OFSGui::fname(OFSGui *o) {                                            \
		o->fname();                                                            \
	}                                                                          \
	void OFSGui::fname()

#endif // OFLAUNCHER_STAINLESS_OFSLAYOUT_H