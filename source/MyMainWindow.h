/***************************************************************************
                          MyMainWindow.h  -  description
                             -------------------
    begin                : Nov. 04, 2015
    copyright            : (C) 2015 by NIAES
	author               : Yamate, N
 ***************************************************************************/


#pragma once

#include "generated/ui_mainwindow.h"
#include "MapToolSelect.h"
#include "MyAssistant.h"

#include <QSplashScreen>

class QgsSvgAnnotationItem;
class QgsLayerTreeMapCanvasBridge;
class QgsSvgAnnotation;
class QgsAnnotation;

/**
 * �C�x���g�t�B���^
 * Wait�J�[�\���\�����Ŏg�p����
 */
class AppFilter : public QObject
{
protected:
    bool eventFilter( QObject *obj, QEvent *event );
};


/**
 * ���C���E�B���h�E�N���X
 */
class MyMainWindow :
	public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:

	/** �R���X�g���N�^ */
	MyMainWindow( QSplashScreen *pSplash );

	/** �f�X�g���N�^ */
	~MyMainWindow(void);


private:

	/** �\������n�}��ǂݍ��� */
	void LoadMaps();

	/** �}����\�z���� */
	void SetupLegend();

	/** �y�n���p�e�[�u���𐶐����� */
	void SetupLuTable();

	/** �I���C�x���g */
	void closeEvent( QCloseEvent *event );

	/** �\���C�x���g */
	void showEvent( QShowEvent *event );

	/** �I���x��������Z�b�g */
	void resetSelectedArea();

	/** ���ʃp�l�������Z�b�g */
	void resetResultTree();

	/** �}�b�v�L�����o�X���C���[���X�g */
	QList<QgsMapLayer *> m_lstLayers;

	/** �r���[�R���g���[���̃A�N�V�����O���[�v */
	QActionGroup *m_pgrpViewControl;

	/** �L�����o�X���ړ��c�[�� */
	QgsMapTool *m_pMapToolPan;

	/** �L�����o�X���g��c�[�� */
	QgsMapTool *m_pMapToolZoomIn;

	/** �L�����o�X���k���c�[�� */
	QgsMapTool *m_pMapToolZoomOut;

	/** �v�f��I���c�[�� */
	MapToolSelect *m_pMapToolSelect;

	/** �C�x���g�t�B���^ */
	AppFilter *m_pFilter;

	/** �O��w�肳�ꂽ�_�̍��W */
	QgsPointXY m_pntLastPos;

	/** �X�v���b�V���E�B���h�E�I�u�W�F�N�g */
	QSplashScreen *m_pSplash;

	/** �J�X�^���A�V�X�^���g�I�u�W�F�N�g */
	MyAssistant *m_pAssistant;

	/** �w��n�_�ɔz�u����A�C�e�� */
	QgsSvgAnnotation *m_pPointAnnotation;

	/** ���W�ϊ��I�u�W�F�N�g */
	QgsCoordinateTransform *m_pCoordinateTrans;

	/** �}�b�v�L�����o�X�u���b�W�I�u�W�F�N�g */
	QgsLayerTreeMapCanvasBridge *mLayerTreeCanvasBridge;

	/** basin���C���C���f�b�N�X */
	int m_nBasinLayerIdx;

	/** lumesh���C���C���f�b�N�X */
	int m_nLumeshLayerIdx;

	/** network���C���C���f�b�N�X */
	int m_nNetworkLayerIdx;

	/** �y�n���p�摜���C���C���f�b�N�X */
	int m_nRasterLayerIdx;

	
private slots:

	/** �L�����o�X���ړ��{�^���������ꂽ�Ƃ� */
	void toolPan( bool bChecked );

	/** �L�����o�X���g��{�^���������ꂽ�Ƃ� */
	void toolZoomIn( bool bChecked );

	/** �L�����o�X���k���{�^���������ꂽ�Ƃ� */
	void toolZoomOut( bool bChecked );

	/** �S�̕\���{�^���������ꂽ�Ƃ� */
	void toolZoomReset();

	/** �v�f��I���{�^���������ꂽ�Ƃ� */
	void toolSelect( bool bChecked );

	/** �N���b�N�n�_����㗬�̃��b�V�����W�v���� */
	void aggregateMesh( QgsPointXY& pntPos );

	/** �N�G�����I�������Ƃ� */
	void onQueryFinished();

	/** �N�G���G���[��\������ */
	void showError(QString strError);

	/** �c�[���o�[�́u�t�@�C�����J���v�{�^���������ꂽ�Ƃ� */
	void onExportResult();

	/** ���W���X�g�t�@�C�����J���Ƃ� */
	void onFileOpen();

	/** ���̃v���O�����ɂ��Ẵ_�C�A���O���J�� */
	void onAppAbout();

	/** �w���v�{�^���������ꂽ�Ƃ� */
	void showDocumentation();

	/** �}��A�C�e�����N���b�N���ꂽ�Ƃ� */
	void enableRasterOpacitySlider( QgsMapLayer *pLayer );

	/** ���ߗ��X���C�_�̒l���ύX���ꂽ�Ƃ� */
	void changeRasterOpacity( int nOpacity );

	/** �����J�n�n�_��annotation���쐬���ꂽ�Ƃ� */
	void annotationCreated( QgsAnnotation *annotation );
};

