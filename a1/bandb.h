// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 22 September 2020

#ifndef _BANDB_H
#define _BANDB_H

// FUNCTIONS
void getbytes(unsigned char dest[], int bytes, void * src, int reverse);
void getbits(char dest[], int bytes, void * src, int start, int end);
unsigned long long bits2ull(char * bits);
long long bits2ll(char * bits);
void spff(char * sign, char * exponent, char * significand, float * src);
void dpff(char * sign, char * exponent, char * significand, double * src);

#endif
