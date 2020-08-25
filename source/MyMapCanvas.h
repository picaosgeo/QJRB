/***************************************************************************
						  QueryManage.h  -  description
							 -------------------
	begin                : Nov. 02, 2019
	copyright            : (C) 2013 by NIAES
	author               : Yamate, N
 ***************************************************************************/


#pragma once
#include <qgsmapcanvas.h>

 /**
  * �J�X�^���}�b�v�L�����o�X�N���X
  */
class MyMapCanvas : public QgsMapCanvas
{
	Q_OBJECT

public:

	/** �R���X�g���N�^ */
	MyMapCanvas( QWidget *parent = nullptr );

	/** �f�X�g���N�^ */
	~MyMapCanvas();

protected:
	/** �}�E�X�N���b�N�C�x���g */
	void mousePressEvent( QMouseEvent *event ) override;

signals:
	/** �E�N���b�N�C�x���g�������̃V�O�i�� */
	void rightButtonClicked();
};

