#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MJSetCards.h"
#include "typedef.h"
#include "common.h"
#include "utility.h"
#include "cJSON.h"
#include "global.h"

#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QMenu>

#include <iostream>
#include <iomanip>
using namespace std;

#define SYS_CARDS_NUM (CARD_MAX_COUNT - 4 * MAX_HANDCARD_NUM)


class MJSetCards : public QMainWindow
{
	Q_OBJECT

public:
	MJSetCards(QWidget *parent = Q_NULLPTR);
	

public slots:
	void slot_item_clicked(QListWidgetItem *item);

	void slot_user_clicked(QListWidgetItem *item);
	void slot_user_doubleclicked(QListWidgetItem *item);

	void slot_clearUser0Btn_clicked(bool checked);
	void slot_clearUser1Btn_clicked(bool checked);
	void slot_clearUser2Btn_clicked(bool checked);
	void slot_clearUser3Btn_clicked(bool checked);
	void slot_clearUser4Btn_clicked(bool checked);

	void slot_sortUser0Btn_clicked(bool checked);
	void slot_sortUser1Btn_clicked(bool checked);
	void slot_sortUser2Btn_clicked(bool checked);
	void slot_sortUser3Btn_clicked(bool checked);
	void slot_sortUser4Btn_clicked(bool checked);

	void slot_genBtn_clicked(bool checked);

	void slot_resetBtn_clicked(bool checked);

	void slot_checkBox_stateChanged(int state);

	void slot_loadCardBtn_clicked(bool checked);

	void slot_openDirectoryBtn_clicked(bool checked);

	void slot_outDirectoryBtn_clicked(bool checked);

	void slot_grabPicBtn_clicked(bool checked);


private slots:
	void m_vQuitAct(bool checked);
	void m_vAboutAct(bool checked);

	void m_vBinaryAct(bool checked);
	void m_vJsonDecAct(bool checked);
	void m_vJsonHexAct(bool checked);
	void m_vDecAct(bool checked);
	void m_vHexAct(bool checked);

	void m_vModifyOutPathAct(bool checked);
	void m_vModifyOutFileNameAct(bool checked);
	void m_vGenLnkAct(bool checked);
	void m_vAutoStartAct(bool checked);
	void m_vCloseToTrayAct(bool checked);

	void slot_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

private:
	void closeEvent(QCloseEvent *event);

	void m_vInit();
	void m_vInitFeng();
	void m_vInitJian();
	void m_vInitHua();
	void m_vReset();

	void m_vSave(QString strFileName, Card aucCards[], int iCardsNum);
	void m_vSaveBinary(QString strFileName, Card aucCards[], int iCardsNum);
	void m_vSaveJsonDec(QString strFileName, Card aucCards[], int iCardsNum);
	void m_vSaveDec(QString strFileName, Card aucCards[], int iCardsNum);
	void m_vSaveHex(QString strFileName, Card aucCards[], int iCardsNum);

	void m_vLoadCards(QString strFileName);
	void m_vLoadCardsBinary(QString strFileName);
	void m_vLoadCardsJsonDec(QString strFileName);
	void m_vLoadCardsDec(QString strFileName);
	void m_vLoadCardsHex(QString strFileName);

	bool m_bIsValidCard(Card ucCard);

	Card m_ucGetCardFromListItem(QListWidgetItem *item);

	QListWidgetItem * m_CreateListItem(Card ucCard);

	void m_vBackupFile(QString strFileName);

	bool m_bIsUserHandCardsValid();

	void m_vClearUserWidget(QListWidget * pUser);
	void m_vClearAllMJItems();
	void m_vClearAllUserItems();

	void m_vSortListWidget(QListWidget * pListWidget);

	void m_vUIEnableMJItems();
	void m_vUIDisableMJItems();

private:
	Ui::MJSetCardsClass ui;

	QSystemTrayIcon * poSystemTray;
	QMenu * pSystemTrayMenu;
	QAction * pRestoreAct;

	EOutputFormat m_eOutputFormat;
	QActionGroup * m_poOutputActGroup;

	QCheckBox * m_apoCheckBox[MJ_TYPE_NUM];

	QListWidget * m_apoListWidget[MJ_TYPE_NUM];
	QListWidgetItem * m_apoListWidgetItem[MJ_TYPE_NUM][MAX_XUSHU_NUM];
	int m_aiCardsNum[MJ_TYPE_NUM];

	QListWidget * m_apoUser[MJ_TYPE_NUM];
	QButtonGroup * RadioBtnGroupUser;
	QRadioButton * m_apoRadioBtn[MJ_TYPE_NUM];

	int m_aiNum[MAX_CARD_ARRAY_SIZE];

	Card m_aucResult[CARD_MAX_COUNT];
	int m_iMaxCardsNum;
};
