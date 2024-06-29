
#ifndef _BH1750_H
#define _BH1750_H

#ifdef __cplusplus
extern "C" {
#endif

void BH1750Send(unsigned char Byte);
unsigned int BH1750Read(void);

#ifdef __cplusplus
}
#endif

#endif // _BH1750_H



