#ifndef OFLAUNCHER_STAINLESS_OFSLAYOUT_H
#define OFLAUNCHER_STAINLESS_OFSLAYOUT_H

#include "OFSGui.h"

#define DEFINE_LAYOUT(fname)                                                   \
	void OFSGui::fname(OFSGui *o) {                                            \
		o->fname();                                                            \
	}                                                                          \
	void OFSGui::fname()


#define DATA(res_name) res_name##_bmp_data
#define FONTDATA(res_name) res_name##_ttf_data


#endif // OFLAUNCHER_STAINLESS_OFSLAYOUT_H