// Copyright (C) 2020 Stephen Fedele <32551324+strangeprogrammer@users.noreply.github.com>
// See the file 'LICENSE.txt' for licensing information of this file.

// Import the python system
#define PY_SSIZE_T_CLEAN
#include <Python.h>

// For 'malloc' and 'free' declaration
#include <stdlib.h>

#include "_MiniCLEB.h"

const static unsigned long initbufsize = 1 * sizeof(char);

bytes fromInt(unsigned long n){
	char* buf = malloc(initbufsize);
	unsigned long len = initbufsize;
	unsigned long idx = 0;
	
	// Mask and shift all of the 7-bit segments of 'n'
	do{
		// If we need to write more than the buffer can hold, double its size
		if(!(idx < len)){
			len *= 2;
			buf = realloc(buf, len);
		}
		
		// Mask and shift off 7 bits for the buffer
		char temp = (n & 0b01111111) | 0b10000000;
		n >>= 7;
		buf[idx++] = temp;
	}while(n);
	
	// Make the resultant buffer fit the output exactly
	len = idx * sizeof(char); // 'len == idx' assuming 'sizeof(char) == 1' (but what if it's not?)
	buf = realloc(buf, len);
	
	// A final touch: clear the continue flag of the most significant byte
	buf[idx - 1] &= 0b01111111;
	
	bytes retval;
	retval.buf = buf;
	retval.len = len;
	return retval;
}

// Accumulate the LEB by walking backwards through the bytes string
unsigned long toInt(bytes leb){
	unsigned long n = 0;
	
	// Accumulate the LEB into the return value
	for(unsigned long idx = leb.len - 1;
	idx < leb.len; // Due to wrap-around of the unsigned long 'idx' after it proceeds past 0, this breaking condition is the same as '0 <= idx' if 'idx' had been negative instead
	idx--){
		// Accumulate a single byte from the buffer
		char c = leb.buf[idx];
		n = (n << 7) + (c & 0b01111111);
	}
	
	return n;
}

// Return the length of the LEB by finding the terminal byte
static unsigned long length(bytes leb){
	unsigned long idx = 0;
	for(;(idx < leb.len);idx++){
		if(!(leb.buf[idx] & 0b10000000)){
			return idx + 1;
		}
	}
	
	return idx;
}

// 64 bits can be correctly encoded within 9 7-bit chunks, with 1 bit in the 10th chunk. We return whether or not the LEB fits this description.
BOOL valid(bytes leb){
	if(10 * sizeof(char) < leb.len){ // Easy case first
		 return 0;
	}else if (0 == leb.len){
		return 0;
	}else if(leb.len == 10 * sizeof(char)){
		if(leb.buf[9] & 0b11111110){ // If any more than 64 bits have been used, reject the LEB since it's not perfectly reconstructable
			return 0;
		}
	}/*else if(leb.len < 10 * sizeof(char)){*/
		return 1;
	/*}*/
}

PyObject* extract(bytes bobj){
	int len = length(bobj);
	
	return PyTuple_Pack(2,
		PyBytes_FromStringAndSize(bobj.buf, len),
		PyBytes_FromStringAndSize(&(bobj.buf[len]), bobj.len - len)
	);
}
