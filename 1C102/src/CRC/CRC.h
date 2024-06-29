/*
 * CRC.h
 *
 * created: 2024/6/18
 *  author: 
 */

#ifndef _CRC_H
#define _CRC_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned int calccrc(unsigned char crcbuf, unsigned int crc);
unsigned int chkcrc(unsigned char* buf, unsigned char len);

#ifdef __cplusplus
}
#endif

#endif // _CRC_H

