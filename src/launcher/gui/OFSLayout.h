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
#define FONTDATA(res_name) res_name##_ttf_data
#else
#define DATA(res_name) "../res/" #res_name ".bmp"
#define FONTDATA(res_name) "../res/" #res_name ".ttf"
#endif

#endif // OFLAUNCHER_STAINLESS_OFSLAYOUT_H