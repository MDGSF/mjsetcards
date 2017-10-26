#include "MJSetCards.h"
#include <QtWidgets/QApplication>
#include <QTranslator>
#include <qnetwork.h>
#include <QTcpServer>
#include "global.h"

//QTcpServer * pTcpServer;
//
//bool bIsAlreadyRunning()
//{
//	pTcpServer = new QTcpServer();
//	bool bListenSuccess = pTcpServer->listen(QHostAddress::Any, 66666);
//	return bListenSuccess ? false : true;
//}

void vChangeWorkingDirectory()
{
	char buf[1024] = { 0 };
	GetCurrentDirectoryA(1024, buf);  //得到当前工作路径
	LOG(INFO) << "GetCurrentDirectoryA = " << buf;

	char strModule[1024] = { 0 };
	GetModuleFileNameA(NULL, strModule, 1024); //得到当前模块路径
	LOG(INFO) << "GetModuleFileNameA = " << strModule;

	QString strApplicationDirPath = QCoreApplication::applicationDirPath();
	QByteArray baApplicationDirPath = strApplicationDirPath.toLocal8Bit();
	char * pcApplicationDirPath = baApplicationDirPath.data();
	LOG(INFO) << "pcApplicationDirPath = " << pcApplicationDirPath;

	QString strApplicationFilePath = QCoreApplication::applicationFilePath();
	QByteArray baApplicationFilePath = strApplicationFilePath.toLocal8Bit();
	char * pcApplicationFilePath = baApplicationFilePath.data();
	LOG(INFO) << "pcApplicationFilePath = " << pcApplicationFilePath;

	QString strCurrentPath = QDir::currentPath();
	QByteArray baCurrentPath = strCurrentPath.toLocal8Bit();
	char * pcCurrentPath = baCurrentPath.data();
	LOG(INFO) << "pcCurrentPath = " << pcCurrentPath;

	google::FlushLogFilesUnsafe(google::GLOG_ERROR);
	google::FlushLogFilesUnsafe(google::GLOG_INFO);

	if (strcmp(pcApplicationDirPath, pcCurrentPath) != 0)
	{
		QString strApplicationDirPath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
		QByteArray baApplicationDirPath = strApplicationDirPath.toLocal8Bit();
		char * pcApplicationDirPath = baApplicationDirPath.data();
		SetCurrentDirectoryA(pcApplicationDirPath);
	}

	{
		LOG(INFO) << endl << endl;
		char buf[1024] = { 0 };
		GetCurrentDirectoryA(1024, buf);  //得到当前工作路径
		LOG(INFO) << "GetCurrentDirectoryA = " << buf;

		char strModule[1024] = { 0 };
		GetModuleFileNameA(NULL, strModule, 1024); //得到当前模块路径
		LOG(INFO) << "GetModuleFileNameA = " << strModule;

		QString strApplicationDirPath = QCoreApplication::applicationDirPath();
		QByteArray baApplicationDirPath = strApplicationDirPath.toLocal8Bit();
		char * pcApplicationDirPath = baApplicationDirPath.data();
		LOG(INFO) << "pcApplicationDirPath = " << pcApplicationDirPath;

		QString strApplicationFilePath = QCoreApplication::applicationFilePath();
		QByteArray baApplicationFilePath = strApplicationFilePath.toLocal8Bit();
		char * pcApplicationFilePath = baApplicationFilePath.data();
		LOG(INFO) << "pcApplicationFilePath = " << pcApplicationFilePath;

		QString strCurrentPath = QDir::currentPath();
		QByteArray baCurrentPath = strCurrentPath.toLocal8Bit();
		char * pcCurrentPath = baCurrentPath.data();
		LOG(INFO) << "pcCurrentPath = " << pcCurrentPath;

		google::FlushLogFilesUnsafe(google::GLOG_ERROR);
		google::FlushLogFilesUnsafe(google::GLOG_INFO);
	}
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//bIsAlreadyRunning();

	vChangeWorkingDirectory();

	QTranslator translator;
	translator.load("mjsetcards_zh.qm");
	a.installTranslator(&translator);

	a.setWindowIcon(QIcon(":/MJSetCards/Resources/fire_111_128.ico"));

	qApp->setQuitOnLastWindowClosed(false);

	MJSetCards w;
	w.show();
	
	return a.exec();
}
