#include "MJSetCards.h"
#include "conio.h"
#include "direct.h"

MJSetCards::MJSetCards(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//this->setFixedSize(680, 588);
	setWindowIcon(QIcon(":/MJSetCards/Resources/fire_111_128.ico"));

	ui.user_5->setVisible(false);
	ui.radioButton_5->setVisible(false);

	m_vInit();
}

void MJSetCards::m_vInit()
{
	ui.user_0->setViewMode(QListView::IconMode);
	ui.user_0->setFlow(QListView::LeftToRight);
	ui.user_0->setIconSize(QSize(40, 40));
	//ui.user_0->setSpacing(10);

	ui.user_1->setViewMode(QListView::IconMode);
	ui.user_1->setIconSize(QSize(40, 40));
	ui.user_1->setFlow(QListView::LeftToRight);

	ui.user_2->setViewMode(QListView::IconMode);
	ui.user_2->setIconSize(QSize(40, 40));
	ui.user_2->setFlow(QListView::LeftToRight);

	ui.user_3->setViewMode(QListView::IconMode);
	ui.user_3->setIconSize(QSize(40, 40));
	ui.user_3->setFlow(QListView::LeftToRight);

	ui.user_4->setViewMode(QListView::IconMode);
	ui.user_4->setIconSize(QSize(40, 40));
	ui.user_4->setFlow(QListView::LeftToRight);

	poSystemTray = new QSystemTrayIcon(this);
	poSystemTray->setIcon(QIcon(":/MJSetCards/Resources/fire_111_128.ico"));
	poSystemTray->setToolTip(tr("MJSetCards"));

	pRestoreAct = new QAction(tr("Restore window"), this);
	connect(pRestoreAct, SIGNAL(triggered()), this, SLOT(showNormal()));

	pSystemTrayMenu = new QMenu(this);
	pSystemTrayMenu->addAction(pRestoreAct);
	pSystemTrayMenu->addSeparator();
	pSystemTrayMenu->addAction(ui.actionQuit);

	poSystemTray->setContextMenu(pSystemTrayMenu);
	poSystemTray->show();
	connect(poSystemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

	
	connect(ui.actionmodifyOutPath, SIGNAL(triggered(bool)), this, SLOT(m_vModifyOutPathAct(bool)));
	connect(ui.actionmodifyOutFileName, SIGNAL(triggered(bool)), this, SLOT(m_vModifyOutFileNameAct(bool)));
	connect(ui.actiongenLnk, SIGNAL(triggered(bool)), this, SLOT(m_vGenLnkAct(bool)));
	connect(ui.actionautoStart, SIGNAL(triggered(bool)), this, SLOT(m_vAutoStartAct(bool)));
	connect(ui.actioncloseToTray, SIGNAL(triggered(bool)), this, SLOT(m_vCloseToTrayAct(bool)));

	ui.actionautoStart->setChecked(g_pstGameConfig->m_bGetAutoStart());
	ui.actioncloseToTray->setChecked(g_pstGameConfig->m_bGetCloseToTray());

	m_poOutputActGroup = new QActionGroup(this);
	m_poOutputActGroup->addAction(ui.actionbinary);
	m_poOutputActGroup->addAction(ui.actionjson_dec);
	m_poOutputActGroup->addAction(ui.actionjson_hex);
	m_poOutputActGroup->addAction(ui.actiondec);
	m_poOutputActGroup->addAction(ui.actionhex);
	m_poOutputActGroup->setExclusive(true);

	connect(ui.actionQuit, SIGNAL(triggered(bool)), this, SLOT(m_vQuitAct(bool)));
	connect(ui.actionAbout, SIGNAL(triggered(bool)), this, SLOT(m_vAboutAct(bool)));
	connect(ui.actionbinary, SIGNAL(triggered(bool)), this, SLOT(m_vBinaryAct(bool)));
	connect(ui.actionjson_dec, SIGNAL(triggered(bool)), this, SLOT(m_vJsonDecAct(bool)));
	connect(ui.actionjson_hex, SIGNAL(triggered(bool)), this, SLOT(m_vJsonHexAct(bool)));
	connect(ui.actiondec, SIGNAL(triggered(bool)), this, SLOT(m_vDecAct(bool)));
	connect(ui.actionhex, SIGNAL(triggered(bool)), this, SLOT(m_vHexAct(bool)));

	if (g_pstGameConfig->m_iGetOutputFormat() == 0) {
		ui.actionbinary->setChecked(true);
		m_eOutputFormat = EBinary;
	}
	else if (g_pstGameConfig->m_iGetOutputFormat() == 1) {
		ui.actionjson_dec->setChecked(true);
		m_eOutputFormat = EJsonDec;
	}
	else if (g_pstGameConfig->m_iGetOutputFormat() == 2) {
		ui.actionjson_hex->setChecked(true);
		m_eOutputFormat = EJsonHex;
	}
	else if (g_pstGameConfig->m_iGetOutputFormat() == 3) {
		ui.actiondec->setChecked(true);
		m_eOutputFormat = EDec;
	}
	else if (g_pstGameConfig->m_iGetOutputFormat() == 4) {
		ui.actionhex->setChecked(true);
		m_eOutputFormat = EHex;
	}


	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		for (int j = 0; j < MAX_XUSHU_NUM; j++)
		{
			m_apoListWidgetItem[i][j] = NULL;
		}
	}

	connect(ui.clearUser0Btn, SIGNAL(clicked(bool)), this, SLOT(slot_clearUser0Btn_clicked(bool)));
	connect(ui.clearUser1Btn, SIGNAL(clicked(bool)), this, SLOT(slot_clearUser1Btn_clicked(bool)));
	connect(ui.clearUser2Btn, SIGNAL(clicked(bool)), this, SLOT(slot_clearUser2Btn_clicked(bool)));
	connect(ui.clearUser3Btn, SIGNAL(clicked(bool)), this, SLOT(slot_clearUser3Btn_clicked(bool)));
	connect(ui.clearUser4Btn, SIGNAL(clicked(bool)), this, SLOT(slot_clearUser4Btn_clicked(bool)));

	connect(ui.sortUser0Btn, SIGNAL(clicked(bool)), this, SLOT(slot_sortUser0Btn_clicked(bool)));
	connect(ui.sortUser1Btn, SIGNAL(clicked(bool)), this, SLOT(slot_sortUser1Btn_clicked(bool)));
	connect(ui.sortUser2Btn, SIGNAL(clicked(bool)), this, SLOT(slot_sortUser2Btn_clicked(bool)));
	connect(ui.sortUser3Btn, SIGNAL(clicked(bool)), this, SLOT(slot_sortUser3Btn_clicked(bool)));
	connect(ui.sortUser4Btn, SIGNAL(clicked(bool)), this, SLOT(slot_sortUser4Btn_clicked(bool)));
	
	connect(ui.GenBtn, SIGNAL(clicked(bool)), this, SLOT(slot_genBtn_clicked(bool)));
	connect(ui.ResetBtn, SIGNAL(clicked(bool)), this, SLOT(slot_resetBtn_clicked(bool)));
	connect(ui.loadBtn, SIGNAL(clicked(bool)), this, SLOT(slot_loadCardBtn_clicked(bool)));
	connect(ui.DirectoryBtn, SIGNAL(clicked(bool)), this, SLOT(slot_openDirectoryBtn_clicked(bool)));
	connect(ui.OutDirectoryBtn, SIGNAL(clicked(bool)), this, SLOT(slot_outDirectoryBtn_clicked(bool)));
	connect(ui.GrabPicBtn, SIGNAL(clicked(bool)), this, SLOT(slot_grabPicBtn_clicked(bool)));

	


	m_apoCheckBox[0] = ui.checkBox_0;
	m_apoCheckBox[1] = ui.checkBox_1;
	m_apoCheckBox[2] = ui.checkBox_2;
	m_apoCheckBox[3] = ui.checkBox_3;
	m_apoCheckBox[4] = ui.checkBox_4;
	m_apoCheckBox[5] = ui.checkBox_5;
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		m_apoCheckBox[i]->setToolTip(QString::number(i));
		connect(m_apoCheckBox[i], SIGNAL(stateChanged(int)), this, SLOT(slot_checkBox_stateChanged(int)));
	}

	QString strWan = QString(tr("wan"));
	QString strTiao = QString(tr("tiao"));
	QString strBing = QString(tr("bing"));
	QString strFeng = QString(tr("feng"));
	QString strJian = QString(tr("jian"));
	QString strHua = QString(tr("hua"));
	QString g_strTypeName[MJ_TYPE_NUM];
	g_strTypeName[0] = strWan;
	g_strTypeName[1] = strTiao;
	g_strTypeName[2] = strBing;
	g_strTypeName[3] = strFeng;
	g_strTypeName[4] = strJian;
	g_strTypeName[5] = strHua;

	int aiTypeNum[MJ_TYPE_NUM] = { MAX_XUSHU_NUM, MAX_XUSHU_NUM, MAX_XUSHU_NUM, MAX_FENG_NUM, MAX_JIAN_NUM, MAX_HUA_NUM };

	m_aiCardsNum[MJ_TYPE_WAN] = MAX_XUSHU_NUM * 4;
	m_aiCardsNum[MJ_TYPE_TIAO] = MAX_XUSHU_NUM * 4;
	m_aiCardsNum[MJ_TYPE_BING] = MAX_XUSHU_NUM * 4;
	m_aiCardsNum[MJ_TYPE_FENG] = MAX_FENG_NUM * 4;
	m_aiCardsNum[MJ_TYPE_JIAN] = MAX_JIAN_NUM * 4;
	m_aiCardsNum[MJ_TYPE_FLOWER] = MAX_HUA_NUM * 4;
	

	m_apoListWidget[0] = ui.listWidget_0;
	m_apoListWidget[1] = ui.listWidget_1;
	m_apoListWidget[2] = ui.listWidget_2;
	m_apoListWidget[3] = ui.listWidget_3;
	m_apoListWidget[4] = ui.listWidget_4;
	m_apoListWidget[5] = ui.listWidget_5;

	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		m_apoListWidget[i]->clear();
		connect(m_apoListWidget[i], SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slot_item_clicked(QListWidgetItem *)));
	}


	RadioBtnGroupUser = new QButtonGroup(this);
	RadioBtnGroupUser->addButton(ui.radioButton_0, 0);
	RadioBtnGroupUser->addButton(ui.radioButton_1, 1);
	RadioBtnGroupUser->addButton(ui.radioButton_2, 2);
	RadioBtnGroupUser->addButton(ui.radioButton_3, 3);
	RadioBtnGroupUser->addButton(ui.radioButton_4, 4);
	RadioBtnGroupUser->addButton(ui.radioButton_5, 5);

	m_apoRadioBtn[0] = ui.radioButton_0;
	m_apoRadioBtn[1] = ui.radioButton_1;
	m_apoRadioBtn[2] = ui.radioButton_2;
	m_apoRadioBtn[3] = ui.radioButton_3;
	m_apoRadioBtn[4] = ui.radioButton_4;
	m_apoRadioBtn[5] = ui.radioButton_5;

	m_apoUser[0] = ui.user_0;
	m_apoUser[1] = ui.user_1;
	m_apoUser[2] = ui.user_2;
	m_apoUser[3] = ui.user_3;
	m_apoUser[4] = ui.user_4;
	m_apoUser[5] = ui.user_5;

	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		connect(m_apoUser[i], SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slot_user_clicked(QListWidgetItem *)));
		connect(m_apoUser[i], SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(slot_user_doubleclicked(QListWidgetItem *)));
	}
	
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		int iTypeNum = aiTypeNum[i];

		if (i >= MJ_TYPE_WAN && i <= MJ_TYPE_BING)
		{
			for (int j = 1; j <= iTypeNum; j++)
			{
				QString str = QString::number(j) + g_strTypeName[i];

				QString strHexValue = QString("0x") + QString::number(i) + QString::number(j);
				int iValue = 0;
				strHexToInt(strHexValue, iValue);
				QString strDecValue = QString::number(iValue);
				QString strValue = strHexValue + " " + strDecValue;
				QString strIconName = QString(":/MJSetCards/Resources/MJImage/MJ") + QString::number(i) + QString::number(j) + QString(".png");

				QListWidgetItem * pItem = new QListWidgetItem(str);
				pItem->setIcon(QIcon(strIconName));
				//pItem->setSizeHint(QSize(40, 40));
				pItem->setText(str);
				pItem->setTextAlignment(Qt::AlignHCenter);
				pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				pItem->setToolTip(strValue);
				pItem->setData(Qt::UserRole, strHexValue);
				m_apoListWidget[i]->addItem(pItem);
				m_apoListWidgetItem[i][j - 1] = pItem;
			}
		}
		else if (i == MJ_TYPE_FENG)
		{
			m_vInitFeng();
		}
		else if (i == MJ_TYPE_JIAN)
		{
			m_vInitJian();
		}
		else if (i == MJ_TYPE_FLOWER)
		{
			m_vInitHua();
		}
	}

	m_iMaxCardsNum = 0;
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		m_iMaxCardsNum += m_aiCardsNum[i];
	}

	ui.checkBox_0->setChecked(true);
	ui.checkBox_1->setChecked(true);
	ui.checkBox_2->setChecked(true);
	ui.checkBox_3->setChecked(true);
	ui.checkBox_4->setChecked(true);
	ui.checkBox_5->setChecked(false);
	m_iMaxCardsNum -= m_aiCardsNum[MJ_TYPE_FLOWER];
	
	m_vReset();

	ui.user_5->setEnabled(false);
	ui.radioButton_5->setEnabled(false);
}

void MJSetCards::m_vInitFeng()
{
	int i = MJ_TYPE_FENG;

	QString strDong = QString(tr("dong"));
	QString strNan = QString(tr("nan"));
	QString strXi = QString(tr("xi"));
	QString strBei = QString(tr("bei"));

	QString strFengTypeName[MAX_FENG_NUM];
	strFengTypeName[0] = strDong;
	strFengTypeName[1] = strNan;
	strFengTypeName[2] = strXi;
	strFengTypeName[3] = strBei;

	for (int j = 0; j < MAX_FENG_NUM; j++)
	{
		QString str = strFengTypeName[j];
		QString strHexValue = QString("0x") + QString::number(i) + QString::number(j + 1);
		int iValue = 0;
		strHexToInt(strHexValue, iValue);
		QString strDecValue = QString::number(iValue);
		QString strValue = strHexValue + " " + strDecValue;
		QString strIconName = QString(":/MJSetCards/Resources/MJImage/MJ") + QString::number(i) + QString::number(j + 1) + QString(".png");

		QListWidgetItem * pItem = new QListWidgetItem(str);
		pItem->setIcon(QIcon(strIconName));
		pItem->setText(str);
		pItem->setTextAlignment(Qt::AlignHCenter);
		pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		pItem->setToolTip(strValue);
		pItem->setData(Qt::UserRole, strHexValue);
		m_apoListWidget[i]->addItem(pItem);
		m_apoListWidgetItem[i][j] = pItem;
	}
}

void MJSetCards::m_vInitJian()
{
	int i = MJ_TYPE_JIAN;

	QString strZhong = QString(tr("zhong"));
	QString strFa = QString(tr("fa"));
	QString strBai = QString(tr("bai"));

	QString strJianTypeName[MAX_JIAN_NUM];
	strJianTypeName[0] = strZhong;
	strJianTypeName[1] = strFa;
	strJianTypeName[2] = strBai;

	for (int j = 0; j < MAX_JIAN_NUM; j++)
	{
		QString str = strJianTypeName[j];
		QString strHexValue = QString("0x") + QString::number(i) + QString::number(j + 1);
		int iValue = 0;
		strHexToInt(strHexValue, iValue);
		QString strDecValue = QString::number(iValue);
		QString strValue = strHexValue + " " + strDecValue;
		QString strIconName = QString(":/MJSetCards/Resources/MJImage/MJ") + QString::number(i) + QString::number(j + 1) + QString(".png");

		QListWidgetItem * pItem = new QListWidgetItem(str);
		pItem->setIcon(QIcon(strIconName));
		pItem->setText(str);
		pItem->setTextAlignment(Qt::AlignHCenter);
		pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		pItem->setToolTip(strValue);
		pItem->setData(Qt::UserRole, strHexValue);
		m_apoListWidget[i]->addItem(pItem);
		m_apoListWidgetItem[i][j] = pItem;
	}
}

void MJSetCards::m_vInitHua()
{
	int i = MJ_TYPE_FLOWER;

	QString strChun = QString(tr("chun"));
	QString strXia = QString(tr("xia"));
	QString strQiu = QString(tr("qiu"));
	QString strDong = QString(tr("winter"));
	QString strMei = QString(tr("mei"));
	QString strLan = QString(tr("lan"));
	QString strZhu = QString(tr("zhu"));
	QString strJu = QString(tr("ju"));

	QString strHuaTypeName[MAX_HUA_NUM];
	strHuaTypeName[0] = strChun;
	strHuaTypeName[1] = strXia;
	strHuaTypeName[2] = strQiu;
	strHuaTypeName[3] = strDong;
	strHuaTypeName[4] = strMei;
	strHuaTypeName[5] = strLan;
	strHuaTypeName[6] = strZhu;
	strHuaTypeName[7] = strJu;

	for (int j = 0; j < MAX_HUA_NUM; j++)
	{
		QString str = strHuaTypeName[j];
		QString strHexValue = QString("0x") + QString::number(i) + QString::number(j + 1);
		int iValue = 0;
		strHexToInt(strHexValue, iValue);
		QString strDecValue = QString::number(iValue);
		QString strValue = strHexValue + " " + strDecValue;
		QString strIconName = QString(":/MJSetCards/Resources/MJImage/MJ") + QString::number(i) + QString::number(j + 1) + QString(".png");

		QListWidgetItem * pItem = new QListWidgetItem(str);
		pItem->setIcon(QIcon(strIconName));
		pItem->setText(str);
		pItem->setTextAlignment(Qt::AlignHCenter);
		pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		pItem->setToolTip(strValue);
		pItem->setData(Qt::UserRole, strHexValue);
		m_apoListWidget[i]->addItem(pItem);
		m_apoListWidgetItem[i][j] = pItem;
	}
}


void MJSetCards::m_vQuitAct(bool checked)
{
	qApp->quit();
}

void MJSetCards::m_vAboutAct(bool checked)
{
	QMessageBox::information(this, tr("About"), tr("Author: Huang Jian.\nEmail: 1342042894@qq.com"), QMessageBox::Ok);
}

void MJSetCards::m_vBinaryAct(bool checked)
{
	m_eOutputFormat = EBinary;
	g_pstGameConfig->m_vSetOutputFormat((int)EBinary);
}
void MJSetCards::m_vJsonDecAct(bool checked)
{
	m_eOutputFormat = EJsonDec;
	g_pstGameConfig->m_vSetOutputFormat((int)EJsonDec);
}
void MJSetCards::m_vJsonHexAct(bool checked)
{
	m_eOutputFormat = EJsonHex;
	g_pstGameConfig->m_vSetOutputFormat((int)EJsonHex);
}
void MJSetCards::m_vDecAct(bool checked)
{
	m_eOutputFormat = EDec;
	g_pstGameConfig->m_vSetOutputFormat((int)EDec);
}
void MJSetCards::m_vHexAct(bool checked)
{
	m_eOutputFormat = EHex;
	g_pstGameConfig->m_vSetOutputFormat((int)EHex);
}

void MJSetCards::m_vModifyOutPathAct(bool checked)
{
	QString strCurPath = QString::fromLocal8Bit(g_pstGameConfig->m_pcGetOutputPath());
	/*if (strCurPath.isEmpty())
	{
	g_pstGameConfig->m_vInitOutputPath();
	strCurPath = QString::fromLocal8Bit(g_pstGameConfig->m_pcGetOutputPath());
	}*/

	bool ok;
	QString strText = QInputDialog::getText(this, tr("Input Dialog"), tr("Output Path:"), QLineEdit::Normal, strCurPath, &ok);
	strText = strText.trimmed();
	if (ok && !strText.isEmpty())
	{
		QByteArray baText = strText.toLocal8Bit();
		char * pcText = baText.data();
		g_pstGameConfig->m_vSetOutputPath(pcText);
	}
}

void MJSetCards::m_vModifyOutFileNameAct(bool checked)
{
	QString strCurFileName = QString::fromLocal8Bit(g_pstGameConfig->m_pcGetOutputFileName());
	bool ok;
	QString strText = QInputDialog::getText(this, tr("Input Dialog"), tr("Output FileName:"), QLineEdit::Normal, strCurFileName, &ok);
	if (ok && !strText.isEmpty())
	{
		QByteArray baText = strText.toLocal8Bit();
		char * pcText = baText.data();
		g_pstGameConfig->m_vSetOutputFileName(pcText);
	}
}

void MJSetCards::m_vGenLnkAct(bool checked)
{
	QString strDirPath = QCoreApplication::applicationDirPath();
	QString strExePathName = strDirPath + QString("\\MJSetCards.exe");
	QFile::link(strExePathName, QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).append("/").append("MJSetCards.lnk"));
}

void appAutoRun(bool bAutoRun)
{
	//HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

	if (bAutoRun)
	{
		QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
		//strAppPath.replace(QChar('/'),QChar('\\'),Qt::CaseInsensitive);
		reg.setValue("MJSetCards", strAppPath);
	}
	else
	{
		reg.setValue("MJSetCards", "");
	}
}

void MJSetCards::m_vAutoStartAct(bool checked)
{
	g_pstGameConfig->m_vSetAutoStart(checked);
	appAutoRun(checked);
}

void MJSetCards::m_vCloseToTrayAct(bool checked)
{
	g_pstGameConfig->m_vSetCloseToTray(checked);
}


void MJSetCards::closeEvent(QCloseEvent *event)
{
	if (g_pstGameConfig->m_bGetCloseToTray())
	{
		if (poSystemTray->isVisible())
		{
		hide();

		static int iShowTipNum = 0;
		if (iShowTipNum < 3)
		{
		poSystemTray->showMessage(tr("Tips"), tr("The MJSetCards is running behind!"));
		}
		iShowTipNum++;

		event->ignore();
		}
	}
	else
	{
		event->accept();
		qApp->quit();
	}
}

void MJSetCards::slot_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
		//单击托盘图标
		break;
	case QSystemTrayIcon::DoubleClick:
		//双击托盘图标
		//双击后显示主程序窗口
		this->show();
		break;
	default:
		break;
	}
}


void MJSetCards::m_vReset()
{
	ui.GenBtn->setEnabled(true);
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		m_apoCheckBox[i]->setEnabled(true);
		m_apoListWidget[i]->setEnabled(m_apoCheckBox[i]->isChecked());
	}

	memset(m_aucResult, 0, sizeof(m_aucResult));

	for (int i = 0; i < MAX_CARD_ARRAY_SIZE; i++)
	{
		m_aiNum[i] = 4;
	}

	ui.user_0->clear();
	ui.user_1->clear();
	ui.user_2->clear();
	ui.user_3->clear();
	ui.user_4->clear();
	ui.user_5->clear();

	ui.radioButton_0->setChecked(true);

	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		for (int j = 0; j < MAX_XUSHU_NUM; j++)
		{
			if (m_apoListWidgetItem[i][j] != NULL)
			{
				QListWidgetItem * pItem = m_apoListWidgetItem[i][j];
				pItem->setHidden(false);
			}
		}
	}
}

void MJSetCards::slot_checkBox_stateChanged(int state)
{
	QObject * pObject = this->sender();
	QCheckBox * pCheckBox = qobject_cast<QCheckBox *>(pObject);
	QString strToolTip = pCheckBox->toolTip();
	int iIndex = strToolTip.toInt();
	QListWidget * pListWidget = m_apoListWidget[iIndex];

	if (state == Qt::Unchecked)
	{
		m_iMaxCardsNum -= m_aiCardsNum[iIndex];
		pListWidget->setEnabled(false);
	}
	else if (state == Qt::Checked)
	{
		m_iMaxCardsNum += m_aiCardsNum[iIndex];
		pListWidget->setEnabled(true);
	}

	m_vReset();
}


void MJSetCards::slot_item_clicked(QListWidgetItem *item)
{
	QString strData = item->data(Qt::UserRole).toString();
	int iCard;
	strHexToInt(strData, iCard); //0x07-->7,  0x13-->19
	Card ucCard = iCard;
	if (m_aiNum[ucCard] <= 0)
	{
		return;
	}

	int iUserID = RadioBtnGroupUser->checkedId();
	QListWidget * pCurUserListWidget = m_apoUser[iUserID];
	if ( (iUserID >= 0 && iUserID < MAX_GAME_PLAY_USER && pCurUserListWidget->count() >= MAX_HANDCARD_NUM) )
	{
		return;
	}

	QListWidgetItem * poNewItem = new QListWidgetItem;
	*poNewItem = *item;

	pCurUserListWidget->addItem(poNewItem);

	m_aiNum[ucCard]--;
	if (m_aiNum[ucCard] == 0)
	{
		item->setHidden(true);
	}
}

void MJSetCards::slot_user_clicked(QListWidgetItem *item)
{
	QListWidget * pUser = item->listWidget();

	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		if (m_apoUser[i] == pUser)
		{
			QRadioButton * poRadioBtn = m_apoRadioBtn[i];
			poRadioBtn->setChecked(true);
		}
	}
}

void MJSetCards::slot_user_doubleclicked(QListWidgetItem *item)
{
	QListWidget * pUser = item->listWidget();
	int iRow = pUser->row(item);
	QListWidgetItem * pCurItem = pUser->takeItem(iRow);

	Card ucCard = m_ucGetCardFromListItem(pCurItem);
	m_aiNum[ucCard]++;
	int iType = CardType(ucCard);
	int iValue = CardNum(ucCard);
	m_apoListWidgetItem[iType][iValue - 1]->setHidden(false);

	delete pCurItem;


	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		if (m_apoUser[i] == pUser)
		{
			QRadioButton * poRadioBtn = m_apoRadioBtn[i];
			poRadioBtn->setChecked(true);
		}
	}
}

void MJSetCards::m_vClearUserWidget(QListWidget * pUser)
{
	while (pUser->count() > 0)
	{
		QListWidgetItem * pCurItem = pUser->takeItem(0);

		Card ucCard = m_ucGetCardFromListItem(pCurItem);
		m_aiNum[ucCard]++;
		int iType = CardType(ucCard);
		int iValue = CardNum(ucCard);
		m_apoListWidgetItem[iType][iValue - 1]->setHidden(false);

		delete pCurItem;
	}
}

void MJSetCards::slot_clearUser0Btn_clicked(bool checked)
{
	ui.radioButton_0->setChecked(true);
	m_vClearUserWidget(ui.user_0);
}
void MJSetCards::slot_clearUser1Btn_clicked(bool checked)
{
	ui.radioButton_1->setChecked(true);
	m_vClearUserWidget(ui.user_1);
}
void MJSetCards::slot_clearUser2Btn_clicked(bool checked)
{
	ui.radioButton_2->setChecked(true);
	m_vClearUserWidget(ui.user_2);
}
void MJSetCards::slot_clearUser3Btn_clicked(bool checked)
{
	ui.radioButton_3->setChecked(true);
	m_vClearUserWidget(ui.user_3);
}
void MJSetCards::slot_clearUser4Btn_clicked(bool checked)
{
	ui.radioButton_4->setChecked(true);
	m_vClearUserWidget(ui.user_4);
}

void MJSetCards::slot_sortUser0Btn_clicked(bool checked)
{
	ui.radioButton_0->setChecked(true);
	m_vSortListWidget(ui.user_0);
}
void MJSetCards::slot_sortUser1Btn_clicked(bool checked)
{
	ui.radioButton_1->setChecked(true);
	m_vSortListWidget(ui.user_1);
}
void MJSetCards::slot_sortUser2Btn_clicked(bool checked)
{
	ui.radioButton_2->setChecked(true);
	m_vSortListWidget(ui.user_2);
}
void MJSetCards::slot_sortUser3Btn_clicked(bool checked)
{
	ui.radioButton_3->setChecked(true);
	m_vSortListWidget(ui.user_3);
}
void MJSetCards::slot_sortUser4Btn_clicked(bool checked)
{
	ui.radioButton_4->setChecked(true);
	m_vSortListWidget(ui.user_4);
}


void MJSetCards::slot_genBtn_clicked(bool checked)
{
	if (!m_bIsUserHandCardsValid())
	{
		return;
	}

	Card aucLeft[CARD_MAX_COUNT] = { 0 };
	int iLeftNum = 0;

	for (int i = 0; i < MAX_CARD_ARRAY_SIZE; i++)
	{
		if (m_bIsValidCard(i))
		{
			for (int j = 0; j < m_aiNum[i]; j++)
			{
				aucLeft[iLeftNum++] = i;
			}
		}
	}

	vRandomArray(aucLeft, iLeftNum);

	memset(m_aucResult, 0, sizeof(m_aucResult));
	int iResultIndex = 0;

	for (int i = 0; i <= 4; i++)
	{
		QListWidget * poUser = m_apoUser[i];
		for (int j = 0; j < poUser->count(); j++)
		{
			QListWidgetItem * poItem = poUser->item(j);
			Card ucCard = m_ucGetCardFromListItem(poItem);
			m_aucResult[iResultIndex++] = ucCard;
		}
		iResultIndex = HANDCARD_NUM * (i+1);
	}

	for (int i = 0; i < CARD_MAX_COUNT; i++)
	{
		if (m_aucResult[i] != 0)
		{
			continue;
		}

		if (iLeftNum == 0)
		{
			break;
		}

		m_aucResult[i] = aucLeft[--iLeftNum];
	}

	for (int i = 0; i < HANDCARD_NUM * 4; i++)
	{
		if (!m_bIsValidCard(m_aucResult[i]))
		{
			QMessageBox message(QMessageBox::Warning, tr("Information"), tr("User hand cards is not valid."), QMessageBox::Ok, NULL);
			message.exec();
			return;
		}
	}

	QString strFileName = QString::fromLocal8Bit(g_pstGameConfig->m_pcGetOutputPathFileName());
	if (strFileName.size() == 0)
	{
		g_pstGameConfig->m_vSetOutputFileName(MJ_FILE_NAME);
		strFileName = QString::fromLocal8Bit(g_pstGameConfig->m_pcGetOutputPathFileName());
	}
	m_vSave(strFileName, m_aucResult, m_iMaxCardsNum);

	m_vClearAllMJItems();
	m_vClearAllUserItems();
	m_vLoadCards(strFileName);
}

void MJSetCards::m_vClearAllMJItems()
{
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		if (!m_apoCheckBox[i]->isChecked())
		{
			continue;
		}

		QListWidget * poList = m_apoListWidget[i];
		for (int j = 0; j < poList->count(); j++)
		{
			QListWidgetItem * pItem = poList->item(j);
			pItem->setHidden(true);
		}
	}

	for (int i = 0; i < MAX_CARD_ARRAY_SIZE; i++)
	{
		m_aiNum[i] = 0;
	}
}

void MJSetCards::m_vClearAllUserItems()
{
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		QListWidget * poUser = m_apoUser[i];
		poUser->clear();
	}
}

void MJSetCards::m_vSave(QString strFileName, Card aucCards[], int iCardsNum)
{
	switch (m_eOutputFormat)
	{
	case EBinary:
	{
		m_vSaveBinary(strFileName, aucCards, iCardsNum);
	}
	break;
	case EJsonDec:
	{
		m_vSaveJsonDec(strFileName, aucCards, iCardsNum);
	}
	break;
	case EJsonHex:
	{

	}
	break;
	case EDec:
	{
		m_vSaveDec(strFileName, aucCards, iCardsNum);
	}
	break;
	case EHex:
	{
		m_vSaveHex(strFileName, aucCards, iCardsNum);
	}
	break;
	default:
	{

	}
	break;
	}
}

void MJSetCards::m_vSaveBinary(QString strFileName, Card aucCards[], int iCardsNum)
{
	int iStartIndex = MAX_GAME_PLAY_USER * HANDCARD_NUM;
	int iEndIndex = iCardsNum - 1;
	vReverseArray(aucCards, iStartIndex, iEndIndex);

	QByteArray baFileName = strFileName.toLocal8Bit();
	char * pcFileName = baFileName.data();
	int iRet = iWriteToFile(pcFileName, (char *)aucCards, iCardsNum);
	if (iRet != EXIT_SUCCESS)
	{
		printf("m_vSaveBinary iWriteToFile failed.");
		return;
	}
}

void MJSetCards::m_vSaveJsonDec(QString strFileName, Card aucCards[], int iCardsNum)
{
	cJSON * pRoot = cJSON_CreateArray();
	for (int i = 0; i < 5; i++)
	{
		cJSON * pSub = cJSON_CreateArray();
		cJSON_AddItemToArray(pRoot, pSub);
	}

	for (int i = 0; i < iCardsNum; i++)
	{
		if (i < MAX_GAME_PLAY_USER * HANDCARD_NUM)
		{
			cJSON * pSub = cJSON_GetArrayItem(pRoot, i / HANDCARD_NUM);
			if (NULL == pSub)
			{
				return;
			}

			cJSON * item = cJSON_CreateNumber(aucCards[i]);
			cJSON_AddItemToArray(pSub, item);
		}
		else
		{
			cJSON * pSub = cJSON_GetArrayItem(pRoot, 4);
			if (NULL == pSub)
			{
				return;
			}

			cJSON * item = cJSON_CreateNumber(aucCards[i]);
			cJSON_AddItemToArray(pSub, item);
		}
	}

	char * pcRoot = cJSON_PrintUnformatted(pRoot);

	iSaveToFile(strFileName, pcRoot);

	cJSON_Delete(pRoot);
	printf("%s\n", pcRoot);
	free(pcRoot);
}

void MJSetCards::m_vSaveDec(QString strFileName, Card aucCards[], int iCardsNum)
{
	QFile f(strFileName);
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream txtOutput(&f);

	for (int i = 0; i < iCardsNum; i++)
	{
		if (i != 0 && i % HANDCARD_NUM == 0)
		{
			txtOutput << endl;
		}

		Card ucCard = aucCards[i];
		char acCard[10] = { 0 };
		sprintf(acCard, "%02d", ucCard);

		txtOutput << acCard << " ";
	}

	f.close();
}

void MJSetCards::m_vSaveHex(QString strFileName, Card aucCards[], int iCardsNum)
{
	QFile f(strFileName);
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream txtOutput(&f);

	for (int i = 0; i < iCardsNum; i++)
	{
		if (i != 0 && i % HANDCARD_NUM == 0)
		{
			txtOutput << endl;
		}

		Card ucCard = aucCards[i];
		char acCard[10] = { 0 };
		sprintf(acCard, "0x%02x", ucCard);

		txtOutput << acCard << " ";
	}

	f.close();
}


void MJSetCards::slot_resetBtn_clicked(bool checked)
{
	m_vReset();
}

void MJSetCards::slot_loadCardBtn_clicked(bool checked)
{
	char acOutputPath[BUFSIZ] = { 0 };
	strcpy(acOutputPath, g_pstGameConfig->m_pcGetOutputPath());
	QString strOutputPath = QString::fromLocal8Bit(acOutputPath);
	strOutputPath = QDir::toNativeSeparators(strOutputPath);

	QString strFileName = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		strOutputPath,
		"",
		0);
	if (strFileName.isNull())
	{
		return;
	}

	m_vClearAllMJItems();
	m_vClearAllUserItems();
	m_vLoadCards(strFileName);
}

void MJSetCards::m_vLoadCards(QString strFileName)
{
	switch (m_eOutputFormat)
	{
	case EBinary:
	{
		m_vLoadCardsBinary(strFileName);
	}
	break;
	case EJsonDec:
	{
		m_vLoadCardsJsonDec(strFileName);
	}
	break;
	case EJsonHex:
	{

	}
	break;
	case EDec:
	{
		m_vLoadCardsDec(strFileName);
	}
	break;
	case EHex:
	{
		m_vLoadCardsHex(strFileName);
	}
	break;
	default:
	{

	}
	break;
	}
}

void MJSetCards::m_vLoadCardsBinary(QString strFileName)
{
	QByteArray baFileName = strFileName.toLocal8Bit();
	char * pcFileName = baFileName.data();

	char acContent[BUFSIZ] = { 0 };
	int iReadBytes = 0;
	int iRet = iReadFromFile(pcFileName, acContent, sizeof(acContent), iReadBytes);
	if (iRet != EXIT_SUCCESS)
	{
		return;
	}

	int iStartIndex = MAX_GAME_PLAY_USER * HANDCARD_NUM;
	int iEndIndex = iReadBytes - 1;
	vReverseArray((uint8_t*)acContent, iStartIndex, iEndIndex);

	for (int i = 0; i < iReadBytes; i++)
	{
		QListWidget * poUser;
		if (i < MAX_GAME_PLAY_USER*HANDCARD_NUM)
		{
			poUser = m_apoUser[i / HANDCARD_NUM];
		}
		else
		{
			poUser = m_apoUser[4];
		}

		Card ucCard = acContent[i];

		if (!m_bIsValidCard(ucCard))
		{
			//ignore the invalid data.
			//QMessageBox::information(this, tr("Error"), tr("Invalid Cards."), QMessageBox::Ok);
			//m_vReset();
			continue;
		}

		QListWidgetItem * poItem = m_CreateListItem(ucCard);
		poUser->addItem(poItem);
	}
}

void MJSetCards::m_vLoadCardsJsonDec(QString strFileName)
{
	QByteArray baFileName = strFileName.toLocal8Bit();
	char * pcFileName = baFileName.data();

	char acContent[BUFSIZ] = { 0 };
	int iReadBytes = 0;
	int iRet = iReadFromFile(pcFileName, acContent, sizeof(acContent), iReadBytes);
	if (iRet != EXIT_SUCCESS)
	{
		return;
	}

	cJSON *pstJson = cJSON_Parse(acContent);
	int iSize = cJSON_GetArraySize(pstJson);
	if (iSize != 5)
	{
		return;
	}

	for (int i = 0; i < iSize; i++)
	{
		QListWidget * poUser = m_apoUser[i];
		cJSON * pSub = cJSON_GetArrayItem(pstJson, i);
		int iSubSize = cJSON_GetArraySize(pSub);
		for (int j = 0; j < iSubSize; j++)
		{
			cJSON *item = cJSON_GetArrayItem(pSub, j);
			Card ucCard = item->valueint;
			if (!bIsValidCard(ucCard))
			{
				continue;
			}
			QListWidgetItem * poItem = m_CreateListItem(ucCard);
			poUser->addItem(poItem);
		}
	}
	cJSON_Delete(pstJson);
}

void MJSetCards::m_vLoadCardsDec(QString strFileName)
{
	QFile f(strFileName);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream txtInput(&f);

	int iLineNum = 0;
	while (!txtInput.atEnd())
	{
		QString strLine = txtInput.readLine().trimmed();
		QStringList strList = strLine.split(' ');

		QListWidget * poUser = NULL;

		if (iLineNum < 4)
		{
			poUser = m_apoUser[iLineNum];
		}
		else
		{
			poUser = m_apoUser[4];
		}

		for (int i = 0; i < strList.size(); i++)
		{
			Card ucCard = (Card)strList[i].toInt();;
			if (!bIsValidCard(ucCard))
			{
				continue;
			}
			QListWidgetItem * poItem = m_CreateListItem(ucCard);
			poUser->addItem(poItem);
		}

		iLineNum++;
	}

	f.close();
}

void MJSetCards::m_vLoadCardsHex(QString strFileName)
{
	QFile f(strFileName);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream txtInput(&f);

	int iLineNum = 0;
	while (!txtInput.atEnd())
	{
		QString strLine = txtInput.readLine().trimmed();
		QStringList strList = strLine.split(' ');

		QListWidget * poUser = NULL;

		if (iLineNum < 4)
		{
			poUser = m_apoUser[iLineNum];
		}
		else
		{
			poUser = m_apoUser[4];
		}

		for (int i = 0; i < strList.size(); i++)
		{
			int iCard;
			strHexToInt(strList[i], iCard);
			Card ucCard = iCard;
			if (!bIsValidCard(ucCard))
			{
				continue;
			}
			QListWidgetItem * poItem = m_CreateListItem(ucCard);
			poUser->addItem(poItem);
		}

		iLineNum++;
	}

	f.close();
}


void MJSetCards::slot_openDirectoryBtn_clicked(bool checked)
{
	QString strDirPath = QCoreApplication::applicationDirPath();
	QDesktopServices::openUrl(QUrl::fromLocalFile(strDirPath));
}

void MJSetCards::slot_outDirectoryBtn_clicked(bool checked)
{
	char acOutputPath[BUFSIZ] = { 0 };
	strcpy(acOutputPath, g_pstGameConfig->m_pcGetOutputPath());
	int iSize = strlen(acOutputPath);
	for (int i = 0; i < iSize; i++)
	{
		if (acOutputPath[i] == '\\')
		{
			acOutputPath[i] = '\/';
		}
	}

	//QDir::toNativeSeparators

	QString strOutputPath = QString::fromLocal8Bit(acOutputPath);
	if (strOutputPath.size() == 0)
	{
		strOutputPath = QCoreApplication::applicationDirPath();
	}
	QDesktopServices::openUrl(QUrl::fromLocalFile(strOutputPath));
}

void MJSetCards::slot_grabPicBtn_clicked(bool checked)
{
	QPixmap bmp;
	QPixmap pix = bmp.grabWindow(QApplication::desktop()->winId(), frameGeometry().x(), frameGeometry().y(), frameGeometry().width(), frameGeometry().height());
	QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss") + ".bmp";//通过时间命名文件
	if (pix.isNull())
	{
		QMessageBox::information(this, tr("Error"), tr("Grab Window Failed."), QMessageBox::Ok);
		return;
	}

	QString strDirPath = QCoreApplication::applicationDirPath();
	QString strPicPath = strDirPath + QString("\\screen\\");
	strPicPath = QDir::toNativeSeparators(strPicPath);
	QByteArray baPicPath = strPicPath.toLocal8Bit();
	char * pcPicPath = baPicPath.data();
	_mkdir(pcPicPath);

	
	if (!pix.save(strPicPath + fileName, "BMP"))
	{
		QMessageBox::information(this, tr("Error"), tr("Save Pic Failed."), QMessageBox::Ok);
		return;
	}
	
	QMessageBox::information(this, tr("Information"), tr("Grab Window Success.") + strPicPath, QMessageBox::Ok);
}

QListWidgetItem * MJSetCards::m_CreateListItem(Card ucCard)
{
	int iType = CardType(ucCard);
	int iValue = CardNum(ucCard);

	QListWidgetItem * poItem = m_apoListWidgetItem[iType][iValue - 1];
	QListWidgetItem * poNewItem = new QListWidgetItem();
	*poNewItem = *poItem;
	return poNewItem;
}

Card MJSetCards::m_ucGetCardFromListItem(QListWidgetItem *item)
{
	QString strData = item->data(Qt::UserRole).toString();
	int iCard;
	strHexToInt(strData, iCard);
	return (Card)iCard;
}

bool MJSetCards::m_bIsValidCard(Card ucCard)
{
	int iType = CardType(ucCard);
	if (iType < MJ_TYPE_WAN || iType > MJ_TYPE_FLOWER)
	{
		return false;
	}

	if (!m_apoCheckBox[iType]->isChecked())
	{
		return false;
	}

	return bIsValidCard(ucCard);
}


void MJSetCards::m_vBackupFile(QString strFileName)
{

}

bool MJSetCards::m_bIsUserHandCardsValid()
{
	if (m_apoUser[0]->count() > HANDCARD_NUM)
	{
		QMessageBox message(QMessageBox::Warning, tr("Information"), tr("User 1 hand cards num is not 13."), QMessageBox::Ok, NULL);
		message.exec();
		return false;
	}

	if (m_apoUser[1]->count() > HANDCARD_NUM)
	{
		QMessageBox message(QMessageBox::Warning, tr("Information"), tr("User 2 hand cards num is not 13."), QMessageBox::Ok, NULL);
		message.exec();
		return false;
	}

	if (m_apoUser[2]->count() > HANDCARD_NUM)
	{
		QMessageBox message(QMessageBox::Warning, tr("Information"), tr("User 3 hand cards num is not 13."), QMessageBox::Ok, NULL);
		message.exec();
		return false;
	}

	if (m_apoUser[3]->count() > HANDCARD_NUM)
	{
		QMessageBox message(QMessageBox::Warning, tr("Information"), tr("User 4 hand cards num is not 13."), QMessageBox::Ok, NULL);
		message.exec();
		return false;
	}

	return true;
}

void MJSetCards::m_vSortListWidget(QListWidget * pListWidget)
{
	int iSize = pListWidget->count();
	QListWidgetItem ** pItemArray = new QListWidgetItem*[iSize];
	int iIndex = 0;
	while (pListWidget->count() > 0)
	{
		pItemArray[iIndex++] = pListWidget->takeItem(0);
	}

	for (int i = 0; i < iSize; i++)
	{
		for (int j = 1; j < iSize - i; j++)
		{
			QListWidgetItem * p1 = pItemArray[j - 1];
			QListWidgetItem * p2 = pItemArray[j];
			QString str1 = p1->data(Qt::UserRole).toString();
			QString str2 = p2->data(Qt::UserRole).toString();
			int iValue1;
			int iValue2;
			strHexToInt(str1, iValue1);
			strHexToInt(str2, iValue2);
			if (iValue1 > iValue2)
			{
				QListWidgetItem * temp = pItemArray[j - 1];
				pItemArray[j - 1] = pItemArray[j];
				pItemArray[j] = temp;
			}
		}
	}

	for (int i = 0; i < iSize; i++)
	{
		pListWidget->addItem(pItemArray[i]);
	}

	delete[] pItemArray;
}

void MJSetCards::m_vUIDisableMJItems()
{
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		m_apoCheckBox[i]->setEnabled(false);
		m_apoListWidget[i]->setEnabled(false);
	}
}

void MJSetCards::m_vUIEnableMJItems()
{
	for (int i = 0; i < MJ_TYPE_NUM; i++)
	{
		m_apoCheckBox[i]->setEnabled(true);
		m_apoListWidget[i]->setEnabled(true);
	}
}