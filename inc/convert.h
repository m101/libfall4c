#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <stdint.h>

uint8_t *bin_to_ascii (uint8_t *hash, int len);
// hex string to binary digits
unsigned int hexstr_to_num (unsigned char *str, size_t len);

#endif /* _CONVERT_H_ */
