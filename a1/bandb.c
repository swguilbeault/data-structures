// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 22 September 2020

#include "bandb.h"

// reads bytes from src and rewrites to dest, possible in reverse order
void getbytes(unsigned char dest[], int bytes, void * src, int reverse) {
  unsigned char * input = src;
  int i;
  for (i = 0; i < bytes; i++) dest[(reverse ? bytes - i - 1 : i)] = input[i]; // turnary operator determines correct index to put char (controlled by reverse)
}

// reads bits from src in specified range, writes specified bits to dest as chars
void getbits(char dest[], int bytes, void * src, int start, int end) {
  unsigned char * input = src;
  int i;
  for (i = start; i > end; i--)
    dest[start - i] = (input[bytes - i/8 - 1] & (1 << (i % 8))) ? '1' : '0'; // check if specified byte is 1 or 0 using bit mask
  dest[start - i] = '\0';
}

// retuns unsigned value from string of 1 and 0 characters by interpreting chars as binary
unsigned long long bits2ull(char * bits) {
  unsigned long long out = 0;
  int i;
  for (i = 0; bits[i] != '\0'; i++) // convert chars to appropriate values
    out = out * 2 + bits[i] - '0';
  return out;
}

// retuns unsigned value from string of 1 and 0 characters by interpreting chars as 2's compmliment binary
long long bits2ll(char * bits) {
  long long out = '0' - bits[0]; // make number negative if sign bit is 1
  int i;
  for (i = 1; bits[i] != '\0'; i++) // convert remaining chars to appropriate values
    out = out * 2 + bits[i] - '0';
  return out;
}

// reads bits from src float, writes exponent, sign, and significand bits to respective destinations
void spff(char * sign, char * exponent, char * significand, float * src) {
  unsigned char bytes[sizeof(float) + 1];
  getbytes(bytes, sizeof(float), (void *) src, 1); // reverse order due to system's endianness

  //place bit characters at string locations
  getbits(sign, sizeof(float), bytes, 31, 30);
  getbits(exponent, sizeof(float), bytes, 30, 22);
  getbits(significand, sizeof(float), bytes, 22, -1);
}

// reads bits from src double, writes exponent, sign, and significand bits to respective destinations
void dpff(char * sign, char * exponent, char * significand, double * src) {
  unsigned char bytes[sizeof(double) + 1];
  getbytes(bytes, sizeof(double), (void *) src, 1); // reverse order due to system's endianness

  //place bit characters at string locations
  getbits(sign, sizeof(double), bytes, 63, 62);
  getbits(exponent, sizeof(double), bytes, 62, 51);
  getbits(significand, sizeof(double), bytes, 51, -1);
}
