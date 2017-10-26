#include "global.h"
#include "conio.h"
#include "direct.h"


GameConfig * g_pstGameConfig = GameConfig::GetInstance();

CGlobal g_oGlobal;


#ifndef NDEBUG

void vInitGlog()
{
	_mkdir("D:\\MJSetCards_LOG");

	google::InitGoogleLogging("MJSetCards");
	google::SetLogDestination(google::GLOG_INFO, "D:\\MJSetCards_LOG/MJSetCards_INFO_");
	google::FlushLogFilesUnsafe(google::GLOG_ERROR);
	FLAGS_logbufsecs = 0; //缓冲日志输出，默认为30秒，此处改为立即输出
	FLAGS_max_log_size = 100; //最大日志大小为 100MB
	FLAGS_colorlogtostderr = true; //设置输出到屏幕的日志显示相应颜色

	LOG(INFO) << "info log test";
	LOG(WARNING) << "warning log test";
	LOG(ERROR) << "error log test" << endl << endl;

	LOG(INFO) << __FUNCTION__;
	LOG(INFO) << "-----> " << __FUNCTION__;
	LOG(INFO) << "<----- " << __FUNCTION__;
	LOG(INFO) << "<----- " << __FUNCTION__ << endl << endl;
	google::FlushLogFiles(google::GLOG_INFO);
}

const char * pcGLOGE(const char * pcFormat, ...)
{
	va_list pcList;
	va_start(pcList, pcFormat);
	static char acLog[LBUFSIZ] = { 0 };
	vsnprintf(acLog, sizeof(acLog), pcFormat, pcList);
	va_end(pcList);
	return acLog;
}

#endif
