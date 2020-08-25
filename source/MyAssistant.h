/***************************************************************************
                          MyAssistant.h  -  description
                             -------------------
    begin                : Dec 04, 2015
    copyright            : (C) 2015 by niaes
	author               : Yamate, N
 ***************************************************************************/


#pragma once

#include <QtCore/QString>

QT_BEGIN_NAMESPACE
class QProcess;
QT_END_NAMESPACE

/**
 * �J�X�^���A�V�X�^���g�\���N���X
 */
class MyAssistant
{
public:

	/** �R���X�g���N�^ */
	MyAssistant(void);

	/** �f�X�g���N�^ */
	~MyAssistant(void);

	/** �\������y�[�W���w�肷�� */
	void showDocumentation(const QString &file);

private:

	/** �A�V�X�^���g���N������ */
    bool startAssistant();

	/** �A�V�X�^���g�v���Z�X */
    QProcess *m_pProc;
};

