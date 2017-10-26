#ifndef MJSTCARDS_GAME_CONFIG_HJ
#define MJSTCARDS_GAME_CONFIG_HJ

#include "common.h"
#include "cJSON.h"
#include "utility.h"
#include <qjsondocument.h>

#define CONF_NAME "MJSetCardsSettings.json"

class GameConfig
{
public:
    static GameConfig * GetInstance()
    {
        static GameConfig stGameCfg;
        stGameCfg.m_iInit(CONF_NAME);
        return &stGameCfg;
    }

private:
    GameConfig();
    ~GameConfig();

	int m_iInit(const char * pcConfFileName);
	void m_vSaveJsonToFile();

    char m_acConfFileName[BUFSIZ];
	cJSON * m_pstRoot;
	QJsonDocument m_oJsonDocument;


public:
	bool m_bGetCloseToTray();
	void m_vSetCloseToTray(bool bCloseToTray);
private:
	bool m_bCloseToTray;

public:
	bool m_bGetAutoStart();
	void m_vSetAutoStart(bool bAutoStart);
private:
	bool m_bAutoStart;


public:
	int m_iGetOutputFormat();
	void m_vSetOutputFormat(int iOutputFormat);
private:
	int m_iOutputFormat;


public:
	void m_vInitOutputPath();
	const char * m_pcGetOutputPath();
	const char * m_pcGetOutputFileName();
	const char * m_pcGetOutputPathFileName();
	void m_vSetOutputPath(const char * pcOutputPath);
	void m_vSetOutputFileName(const char * pcOutputFileName);
	void m_vSetOutputPathFileName(const char * pcOutputPathFileName);
private:
	char m_acOutputPath[BUFSIZ];
	char m_acOutputFileName[BUFSIZ];
	char m_acOutputPathFileName[BUFSIZ];
};

#endif
