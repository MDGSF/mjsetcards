#pragma once

#define GOOGLE_GLOG_DLL_DECL
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog/logging.h"
#pragma comment(lib, "libglog_static.lib")


#include "game_config.h"

extern GameConfig * g_pstGameConfig;

enum EUserStatus
{
	ENone = 0,
	ESetCards = 1,
	ESetCardsSuccess = 2,
	ELoadCards = 3
};

enum EOutputFormat
{
	EBinary = 0,
	EJsonDec = 1,
	EJsonHex = 2,
	EDec = 3,
	EHex = 4
};


#ifndef NDEBUG

const char * pcGLOGE(const char * pcFormat, ...);

#define GLOGE(format, ...) \
	do { \
		LOG(ERROR) << pcGLOGE(format, ##__VA_ARGS__); \
		google::FlushLogFiles(google::GLOG_INFO); \
	} while (0)


extern void vInitGlog();

#endif

class CGlobal
{
public:
	CGlobal()
	{
#ifndef NDEBUG
		vInitGlog();
#endif
	}
};

extern CGlobal g_oGlobal;


