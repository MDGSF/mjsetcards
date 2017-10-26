#pragma once

#include "common.h"
#include <QString>

#ifdef __cplusplus
extern "C" {
#endif

	void vSwap(uint8_t & a, uint8_t & b);

	void vReverseArray(uint8_t aucArray[], int iStartIndex, int iEndIndex);

	void vRandomArray(uint8_t aucArray[], uint8_t ucArraySize);

	bool bIsValidCard(Card ucCard);

	//0x07-->7,  0x13-->19
	//  07-->7,    13-->19
	void strHexToInt(QString str, int & i);

	//7-->0x07, 19-->0x13
	void IntToStrHex(int i, QString & str);

	int iSaveToFile(QString strFileName, char acContent[]);

	int iReadFromFile(const char * pcFileName, char acContent[], int iContentBufSize, int & riReadBytes);

	int iWriteToFile(const char * pcFileName, char acContent[], int iContentBufSize);

#ifdef __cplusplus
}
#endif


