#include "game_config.h"
#include <windows.h>

#define AUTOSTART "AutoStart"
#define OUTPUTFORMAT "OutputFormat"
#define OUTPUTPATH "OutputPath"
#define OUTPUTFILENAME "OutputFileName"
#define OUTPUTPATHFILENAME "OutputPathFileName"
#define CLOSETOTRAY "CloseToTray"

GameConfig::GameConfig()
{

}

GameConfig::~GameConfig()
{
	cJSON_Delete(m_pstRoot);
}

void vTest()
{
	QVariantList people;

	QVariantMap bob;
	bob.insert("Name", "Bob");
	bob.insert("Phonenumber", 123);

	QVariantMap alice;
	alice.insert("Name", "Alice");
	alice.insert("Phonenumber", 321);

	people << bob << alice;

	QJsonDocument jsonDocument = QJsonDocument::fromVariant(people);
	if (!jsonDocument.isNull()) {
		QByteArray baJsonDocument = jsonDocument.toJson();
		int iRet = iWriteToFile(CONF_NAME, baJsonDocument.data(), baJsonDocument.size());
		printf("iRet = %d", iRet);
	}
}

void vTest1()
{
	QVariantMap oRoot;
	oRoot.insert("AutoStart", false);
	oRoot.insert("OutputFormat", 1);
	oRoot.insert("OutputPath", "");
	oRoot.insert("OutputFileName", MJ_FILE_NAME);
	oRoot.insert("OutputPathFileName", "");

	QJsonDocument jsonDocument = QJsonDocument::fromVariant(oRoot);
	if (!jsonDocument.isNull()) {
		QByteArray baJsonDocument = jsonDocument.toJson();
		int iRet = iWriteToFile(CONF_NAME, baJsonDocument.data(), baJsonDocument.size());
		printf("iRet = %d", iRet);
	}
}


void GameConfig::m_vSaveJsonToFile()
{
	char * pcContent = cJSON_Print(m_pstRoot);

	iWriteToFile(m_acConfFileName, pcContent, strlen(pcContent));

	free(pcContent);
}

int GameConfig::m_iInit(const char * pcConfFileName)
{
    if (pcConfFileName)
    {
        memset(m_acConfFileName, 0x00, sizeof(m_acConfFileName));
        GetModuleFileNameA(NULL, m_acConfFileName, sizeof(m_acConfFileName) - 1);
        int len = strrchr(m_acConfFileName, '\\') - m_acConfFileName;
        memset(m_acConfFileName + len + 1, 0, strlen(m_acConfFileName) - len - 1);
        strcat(m_acConfFileName, pcConfFileName);
    }
    else
    {
        strcpy_s(m_acConfFileName, sizeof(m_acConfFileName), CONF_NAME);
    }

	m_pstRoot = NULL;
	char acContent[BBUFSIZ] = { 0 };
	int iReadBytes = 0;
	int iRet = iReadFromFile(m_acConfFileName, acContent, sizeof(acContent), iReadBytes);
	if (iRet == EXIT_SUCCESS)
	{
		m_pstRoot = cJSON_Parse(acContent);
	}
	
	if (NULL == m_pstRoot)
	{
		m_pstRoot = cJSON_CreateObject();
	}


	cJSON * pCloseToTray = cJSON_GetObjectItem(m_pstRoot, CLOSETOTRAY);
	if (NULL == pCloseToTray)
	{
		pCloseToTray = cJSON_CreateNumber(1);
		cJSON_AddItemToObject(m_pstRoot, CLOSETOTRAY, pCloseToTray);
	}
	m_bCloseToTray = pCloseToTray->valueint;

	
	cJSON * pAutoStart = cJSON_GetObjectItem(m_pstRoot, AUTOSTART);
	if (NULL == pAutoStart)
	{
		pAutoStart = cJSON_CreateNumber(0);
		cJSON_AddItemToObject(m_pstRoot, AUTOSTART, pAutoStart);
	}
	m_bAutoStart = pAutoStart->valueint;

	
	cJSON * pOutputFormat = cJSON_GetObjectItem(m_pstRoot, OUTPUTFORMAT);
	if (NULL == pOutputFormat)
	{
		pOutputFormat = cJSON_CreateNumber(1);
		cJSON_AddItemToObject(m_pstRoot, OUTPUTFORMAT, pOutputFormat);
	}
	m_iOutputFormat = pOutputFormat->valueint;


	memset(m_acOutputPath, 0, sizeof(m_acOutputPath));
	cJSON * pOutputPath = cJSON_GetObjectItem(m_pstRoot, OUTPUTPATH);
	if (NULL == pOutputPath)
	{
		pOutputPath = cJSON_CreateString("");
		cJSON_AddItemToObject(m_pstRoot, OUTPUTPATH, pOutputPath);
	}
	strcpy(m_acOutputPath, pOutputPath->valuestring);

	memset(m_acOutputFileName, 0, sizeof(m_acOutputFileName));
	cJSON * pOutputFileName = cJSON_GetObjectItem(m_pstRoot, OUTPUTFILENAME);
	if (NULL == pOutputFileName)
	{
		pOutputFileName = cJSON_CreateString(MJ_FILE_NAME);
		cJSON_AddItemToObject(m_pstRoot, OUTPUTFILENAME, pOutputFileName);
	}
	strcpy(m_acOutputFileName, pOutputFileName->valuestring);

	memset(m_acOutputPathFileName, 0, sizeof(m_acOutputPathFileName));
	cJSON * pOutputPathFileName = cJSON_GetObjectItem(m_pstRoot, OUTPUTPATHFILENAME);
	if (NULL == pOutputPathFileName)
	{
		strcpy(m_acOutputPathFileName, m_acOutputPath);
		strcat(m_acOutputPathFileName, m_acOutputFileName);
		pOutputPathFileName = cJSON_CreateString(m_acOutputPathFileName);
		cJSON_AddItemToObject(m_pstRoot, OUTPUTPATHFILENAME, pOutputPathFileName);
	}
	else
	{
		strcpy(m_acOutputPathFileName, pOutputPathFileName->valuestring);
		if (strlen(m_acOutputPathFileName) == 0)
		{
			strcpy(m_acOutputPathFileName, m_acOutputFileName);
		}
	}

	return EXIT_SUCCESS;
}


bool GameConfig::m_bGetCloseToTray()
{
	return m_bCloseToTray;
}
void GameConfig::m_vSetCloseToTray(bool bCloseToTray)
{
	m_bCloseToTray = bCloseToTray; 
	cJSON * pCloseToTray = cJSON_GetObjectItem(m_pstRoot, CLOSETOTRAY);
	if (pCloseToTray == NULL) {
		return;
	}
	cJSON_SetIntValue(pCloseToTray, bCloseToTray);
	m_vSaveJsonToFile();
}


bool GameConfig::m_bGetAutoStart()
{
	return m_bAutoStart;
}
void GameConfig::m_vSetAutoStart(bool bAutoStart)
{
	m_bAutoStart = bAutoStart;
	cJSON * pAutoStart = cJSON_GetObjectItem(m_pstRoot, AUTOSTART);
	if (pAutoStart == NULL) {
		return;
	}
	cJSON_SetIntValue(pAutoStart, m_bAutoStart);
	m_vSaveJsonToFile();
}

int GameConfig::m_iGetOutputFormat()
{
	return m_iOutputFormat;
}
void GameConfig::m_vSetOutputFormat(int iOutputFormat)
{
	m_iOutputFormat = iOutputFormat;
	cJSON * pOutputFormat = cJSON_GetObjectItem(m_pstRoot, OUTPUTFORMAT);
	if (pOutputFormat == NULL) {
		return;
	}
	cJSON_SetIntValue(pOutputFormat, m_iOutputFormat);
	m_vSaveJsonToFile();
}

void GameConfig::m_vInitOutputPath()
{
	QString strDirPath = QCoreApplication::applicationDirPath();
	QByteArray baDirPath = strDirPath.toLocal8Bit();
	char * pcDirPath = baDirPath.data();
	m_vSetOutputPath(pcDirPath);
}
const char * GameConfig::m_pcGetOutputPath()
{
	return m_acOutputPath;
}
const char * GameConfig::m_pcGetOutputFileName()
{
	return m_acOutputFileName;
}
const char * GameConfig::m_pcGetOutputPathFileName()
{
	return m_acOutputPathFileName;
}
void GameConfig::m_vSetOutputPath(const char * pcOutputPath)
{
	memset(m_acOutputPath, 0, sizeof(m_acOutputPath));
	strcpy(m_acOutputPath, pcOutputPath);

	cJSON * pOutputPath = cJSON_GetObjectItem(m_pstRoot, OUTPUTPATH);
	if (pOutputPath == NULL) {
		return;
	}
	//strcpy(pOutputPath->valuestring, m_acOutputPath);
	cJSON * pstNew = cJSON_CreateString(m_acOutputPath);
	cJSON_ReplaceItemInObject(m_pstRoot, OUTPUTPATH, pstNew);

	char acOutputPath[BUFSIZ] = { 0 };
	strcpy(acOutputPath, m_acOutputPath);
	char cAppendChar = '\0';

	if (strchr(acOutputPath, '/') != NULL)
	{
		cAppendChar = '/';
	}
	else if (strchr(acOutputPath, '\\') != NULL)
	{
		cAppendChar = '\\';
	}

	int iSize = strlen(acOutputPath);
	if (acOutputPath[iSize - 1] != cAppendChar)
	{
		acOutputPath[iSize] = cAppendChar;
		acOutputPath[iSize + 1] = '\0';
	}
	
	char acOutputPathFileName[BUFSIZ] = { 0 };
	strcpy(acOutputPathFileName, acOutputPath);
	strcat(acOutputPathFileName, m_acOutputFileName);
	m_vSetOutputPathFileName(acOutputPathFileName);
}
void GameConfig::m_vSetOutputFileName(const char * pcOutputFileName)
{
	strcpy(m_acOutputFileName, pcOutputFileName);
	cJSON * pOutputFileName = cJSON_GetObjectItem(m_pstRoot, OUTPUTFILENAME);
	if (pOutputFileName == NULL) {
		return;
	}
	//strcpy(pOutputFileName->valuestring, m_acOutputFileName);
	cJSON * pstNew = cJSON_CreateString(m_acOutputFileName);
	cJSON_ReplaceItemInObject(m_pstRoot, OUTPUTFILENAME, pstNew);


	char acOutputPath[BUFSIZ] = { 0 };
	strcpy(acOutputPath, m_acOutputPath);
	char cAppendChar = '\0';

	if (strchr(acOutputPath, '/') != NULL)
	{
		cAppendChar = '/';
	}
	else if (strchr(acOutputPath, '\\') != NULL)
	{
		cAppendChar = '\\';
	}

	int iSize = strlen(acOutputPath);
	if (acOutputPath[iSize - 1] != cAppendChar)
	{
		acOutputPath[iSize] = cAppendChar;
		acOutputPath[iSize + 1] = '\0';
	}
	
	char acOutputPathFileName[BUFSIZ] = { 0 };
	strcpy(acOutputPathFileName, acOutputPath);
	strcat(acOutputPathFileName, m_acOutputFileName);
	m_vSetOutputPathFileName(acOutputPathFileName);
}
void GameConfig::m_vSetOutputPathFileName(const char * pcOutputPathFileName)
{
	strcpy(m_acOutputPathFileName, pcOutputPathFileName);
	cJSON * pOutputPathFileName = cJSON_GetObjectItem(m_pstRoot, OUTPUTPATHFILENAME);
	if (pOutputPathFileName == NULL) {
		return;
	}
	//strcpy(pOutputPathFileName->valuestring, m_acOutputPathFileName);
	cJSON * pstNew = cJSON_CreateString(m_acOutputPathFileName);
	cJSON_ReplaceItemInObject(m_pstRoot, OUTPUTPATHFILENAME, pstNew);

	m_vSaveJsonToFile();
}

