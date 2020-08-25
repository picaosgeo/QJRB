/***************************************************************************
                          MapToolSelect.h  -  description
                             -------------------
    begin                : Oct 09, 2015
    copyright            : (C) 2015 by NIAES
	author               : Yamate, N
 ***************************************************************************/

#pragma once

#include <qgsmaptool.h>

class MyMapCanvas;

/**
 *  �f�[�^�I���c�[���N���X
 */
class MapToolSelect :	public QgsMapTool
{
	Q_OBJECT

public:

	/**
	 * �R���X�g���N�^
	 * @param canvas �}�b�v�L�����o�X�ւ̃|�C���^
	 */
	MapToolSelect( MyMapCanvas *canvas );

	/** �f�X�g���N�^ */
	~MapToolSelect(void);

	/** �L�����o�X����N���b�N�����Ƃ��̃C�x���g */
	virtual void canvasPressEvent( QgsMapMouseEvent *event );

signals:

	/** �����ꂽ�|�C���g�̌o�ܓx */
	void mousePressed( QgsPointXY& );
};

