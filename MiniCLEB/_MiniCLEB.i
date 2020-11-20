// Copyright (C) 2020 Stephen Fedele <32551324+strangeprogrammer@users.noreply.github.com>
// See the file 'LICENSE.txt' for licensing information of this file.

%module (moduleimport="import _MiniCLEB") MiniCLEB

%typemap(in) bytes {
	bytes leb;
	PyBytes_AsStringAndSize($input, &(leb.buf), (Py_ssize_t*)(&(leb.len)));
	$1 = leb;
};

%typemap(out) bytes {
	$result = PyBytes_FromStringAndSize($1.buf, $1.len);
};

%typemap(out) BOOL {
	if($1){
		Py_RETURN_TRUE;
	}else{
		Py_RETURN_FALSE;
	}
}

%{
#include "_MiniCLEB.h"
%}

%include "_MiniCLEB.h"
