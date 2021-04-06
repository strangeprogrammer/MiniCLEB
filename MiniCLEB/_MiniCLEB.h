// Copyright (C) 2020 Stephen Fedele <32551324+strangeprogrammer@users.noreply.github.com>
// See the file 'LICENSE.txt' for licensing information of this file.

#ifndef _MINICLEB_H
#define _MINICLEB_H
	
	// Import the python system
	#define PY_SSIZE_T_CLEAN
	#include <Python.h>
	
	typedef struct {
		char* buf;
		unsigned long len;
	} bytes;
	
	typedef unsigned char BOOL;
	
	extern bytes fromInt(unsigned long n);
	extern unsigned long toInt(bytes leb);
	extern BOOL usable(bytes leb);
	extern BOOL valid(bytes leb);
	extern PyObject* extract(bytes blob);
	
#endif /* _MINICLEB_H */
