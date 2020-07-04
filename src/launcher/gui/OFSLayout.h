#ifndef OFLAUNCHER_STAINLESS_OFSLAYOUT_H
#define OFLAUNCHER_STAINLESS_OFSLAYOUT_H

#include "OFSGui.h"

#define DEFINE_LAYOUT(fname)                                                   \
	void OFSGui::fname(OFSGui *o) {                                            \
		o->fname();                                                            \
	}                                                                          \
	void OFSGui::fname()

#ifdef INCLUDE_RESOURCES
#define DATA(res_name) res_name##_bmp_data
#else
#define DATA(res_name) "../res/" #res_name ".bmp"
#endif

#endif // OFLAUNCHER_STAINLESS_OFSLAYOUT_H