#include "utility.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAction>

void vSwap(uint8_t & a, uint8_t & b)
{
	uint8_t temp = a;
	a = b;
	b = temp;
}

void vReverseArray(uint8_t aucArray[], int iStartIndex, int iEndIndex)
{
	while (iStartIndex < iEndIndex)
	{
		vSwap(aucArray[iStartIndex], aucArray[iEndIndex]);
		++iStartIndex;
		--iEndIndex;
	}
}

void vRandomArray(uint8_t aucArray[], uint8_t ucArraySize)
{
	srand((unsigned int)time(0));
	for (uint8_t i = 1; i < ucArraySize; i++)
	{
		uint8_t index = (uint8_t)(rand() % i);
		vSwap(aucArray[i], aucArray[index]);
	}
}

bool bIsValidCard(Card ucCard)
{
	int iType = CardType(ucCard);
	int iValue = CardNum(ucCard);

	if (iType < MJ_TYPE_WAN || iType > MJ_TYPE_FLOWER)
	{
		return false;
	}

	switch (iType)
	{
	case MJ_TYPE_WAN:
	{
		if (iValue < 1 || iValue > 9)
		{
			return false;
		}
	}
	break;
	case MJ_TYPE_TIAO:
	{
		if (iValue < 1 || iValue > 9)
		{
			return false;
		}
	}
	break;
	case MJ_TYPE_BING:
	{
		if (iValue < 1 || iValue > 9)
		{
			return false;
		}
	}
	break;
	case MJ_TYPE_FENG:
	{
		if (iValue < 1 || iValue > 4)
		{
			return false;
		}
	}
	break;
	case MJ_TYPE_JIAN:
	{
		if (iValue < 1 || iValue > 3)
		{
			return false;
		}
	}
	break;
	case MJ_TYPE_FLOWER:
	{
		if (iValue < 1 || iValue > 8)
		{
			return false;
		}
	}
	break;

	default:
	{

	}
	break;
	}

	return true;
}

void strHexToInt(QString str, int & i)
{
	bool ok;
	i = str.toInt(&ok, 16);
}

void IntToStrHex(int i, QString & str)
{
	char acStr[10] = { 0 };
	sprintf(acStr, "0x%02x", i);
	str = QString(acStr);
}

int iSaveToFile(QString strFileName, char acContent[])
{
	QFile f(strFileName);
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return EXIT_FAILURE;
	}

	QTextStream txtOutput(&f);
	txtOutput << acContent;
	f.close();
	return EXIT_SUCCESS;
}

int iReadFromFile(const char * pcFileName, char acContent[], int iContentBufSize, int & riReadBytes)
{
	if (NULL == pcFileName) {
		printf("pcFileName==NULL\n");
		return EXIT_FAILURE;
	}

	FILE *fp = NULL;
	if ((fp = fopen(pcFileName, "rb")) == NULL) {
		printf("Failed to open file %s \n", pcFileName);
		return EXIT_FAILURE;
	}

	//obtain file size
	fseek(fp, 0, SEEK_END);
	int iFileSize = ftell(fp);
	rewind(fp);

	int iReadBytes = fread(acContent, 1, iContentBufSize, fp);
	if (iFileSize != iReadBytes) {
		printf("read file error\n");
		return EXIT_FAILURE;
	}
	acContent[iReadBytes] = '\0';
	riReadBytes = iReadBytes;

	if (fclose(fp) != 0) {
		printf("close file error\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int iWriteToFile(const char * pcFileName, char acContent[], int iContentBufSize)
{
	if (NULL == pcFileName) {
		printf("pcFileName==NULL\n");
		return EXIT_FAILURE;
	}

	FILE *fp = NULL;
	if ((fp = fopen(pcFileName, "wb")) == NULL) {
		printf("Failed to open file %s \n", pcFileName);
		return EXIT_FAILURE;
	}

	int iWriteBytes = fwrite(acContent, 1, iContentBufSize, fp);
	if (iContentBufSize != iWriteBytes) {
		printf("write file error\n");
		return EXIT_FAILURE;
	}

	if (fclose(fp) != 0) {
		printf("close file error\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
