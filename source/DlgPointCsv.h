/***************************************************************************
                          DlgPointCsv.h  -  description
                             -------------------
    begin                : Nov. 24, 2015
    copyright            : (C) 2015 by NIAES
	author               : Yamate, N
 ***************************************************************************/


#pragma once

#include "generated/ui_dlgPointCsv.h"

/** �_���w�肵�ďW�v����Ƃ��̃t�@�C���w��_�C�A���O�N���X */
class DlgPointCsv :
	public QDialog, public Ui::ui_PointCsv
{
	Q_OBJECT

public:
	DlgPointCsv( QWidget *parent = NULL );
	~DlgPointCsv();


private slots:

	/** ���̓t�@�C���́u�Q�Ɓv�{�^���������ꂽ�Ƃ� */
	void onBrowseInput();

	/** �o�̓t�@�C���́u�Q�Ɓv�{�^���������ꂽ�Ƃ� */
	void onBrowseOutput();
};

