/***************************************************************************
                          QueryManage.h  -  description
                             -------------------
    begin                : Nov. 11, 2015
    copyright            : (C) 2013 by NIAES
	author               : Yamate, N
 ***************************************************************************/


#pragma once

#include <QThread>
#include <QtCore>
//#include <QtSql>
#include <sqlite3.h>
#include <qgsrectangle.h>
#include <qgspoint.h>
#include <spatialite.h>



#define _tr(s) QString::fromLocal8Bit(s)



// ���o�[�W����
//#define OLD_VERSION


/** �N�G�����ʃe�[�u�����i�[���� */
typedef QList<QVariant> MyRowData;

/** �����Ώۉ͐�̒T���͈� */
#define RIV_SEARCH_DIST 100.0



/**
 * SQLite�f�[�^�x�[�X�Ǘ��N���X
 * �V���O���g���I�u�W�F�N�g�Ƃ��č\�z����
 */
class QueryManage :	public QThread
{
	Q_OBJECT

public:

	/** ���������͐�N���X */
	typedef struct InitialRivInfo
	{
		int nRivCode;
		int nBasinId;
		double dLrsLength;
	} 
	InitialRivInfo;

	/** �N�G�����s���̗�O�N���X */
	struct SLException
	{
		SLException( char *pMsg ) : errMsg( pMsg ){}
		SLException( const SLException &e ) : errMsg( e.errMsg ){}
		~SLException(){ if ( errMsg ) sqlite3_free( errMsg ); }

		QString errorMessage() const { return errMsg ? QString::fromUtf8( errMsg ) : ""; }
	private:
		char *errMsg;
	};

	/** �y�n���p��� */
	typedef struct _LUINFO
	{
		int nID;
		QString strLuCode;
		QString strLuName;
		int nParentItem;

		bool operator == (int n) const { return n == nID; }
		bool operator == (const QString &str) const { return str == strLuCode; }
	} LUINFO;


	/** ���������͐�n�_��� */
	class InitRivPos
	{
	public:
		int nRivCode;
		QgsPointXY pntPos;

		bool operator == (const int n) const { return n == nRivCode; }
	};


	/** �f�X�g���N�^ */
	~QueryManage(void);

	/** ���̃N���X�̃V���O���g����Ԃ� */
	static QueryManage* instance();

	/** �f�[�^�x�[�X�ɐڑ�����Ă��邩�ǂ��� */
	inline bool isOpened() const { return m_bOpen; }

	/** �f�[�^�x�[�X�t�@�C�������擾���� */
	inline QString& getDbName() { return m_strDbName; }

	/** �O��̃N�G�����ʂ��������� */
	void clearResult();

	/** 
	 * �|�C���g���w�肵�Ă��̒n�_����㗬�̓y�n���p���b�V�����W�v����������Z�b�g����
	 * @param pnt �w�肵���n�_
	 */
	inline void setCondition( QgsPointXY &pnt ){ m_pnt = pnt; }

	/** �N�G�����ʂ��擾���� */
	inline QMap<int, double>& getQueryResult(){ return m_mapResult; }

	/** �y�n���p���̃��X�g���擾���� */
	QVector<QueryManage::LUINFO>& getLuList();

	/** �y�n���p�R�[�h�̔ԍ����擾���� */
	int getLuId( QString strLuCode );

	/** �������ꂽ�x�����ID���擾���� */
	inline QVector<int>& getSearchedBasins(){ return m_vSearchedBasins; }

	/** �������ꂽ�͐얼���擾���� */
	inline QString getRivName(){ return m_strRivName; }

	/** �������ꂽ�y�n���p���b�V�����擾���� */
	inline QVector<int>& getSearchedMeshes(){ return m_vSearchedMeshes; }

	/** �N�G�������s���ꂽ���ǂ������擾���� */
	inline bool isQueryed(){ return m_bQueryed; }

	/** Spatialite�̃o�[�W������Ԃ� */
	inline const char * _spatialite_version() { return spatialite_version(); }

	/** �����J�n�ʒu�ɑ΂��ĉ͐�܂ł̋����͈͂����肷�邩�ǂ�����ݒ肷�� */
	inline void setCheckDist( bool bCheck ){ m_bCheckDist = bCheck; }

signals:

	/** �N�G���G���[���ɔ��s����V�O�i�� */
	void sqlError( QString );

protected:

	/** �R���X�g���N�^ */
	QueryManage();

	/** �y�n���p�e�[�u�����쐬���� */
	bool createLuTable();

	/** �O��̌��ʂ��N���A���� */
	void initializeResult();

	/** �N�G�������s���� */
	void run();

#ifdef OLD_VERSION
	/** �㗬�̓y�n���p���W�v���� */
	void getUpstreamLu( QPair<int, int>& nUpstream );
#endif

#ifdef OLD_VERSION
	/** �㗬���������� */
	void getUpstreamBasins( QPair<int, int>& nUpstream );
#else
	/**
	 �㗬����������
	 @param nCurrentRivGid �Ώۉ͐��gid
	 @param strStreamCode �Ώۉ͐��stream code
	 @param dDistStartPoint �w��n�_�́A�Ώۉ͐쉺���[�����LRS����
	 */
	void getUpstreamBasins( int nCurrentRivGid, QString &strStreamCode, double dDistStartPoint );

	/**
	 �����̕���_���܂ށA�ŏ��̉͐����������
	 @param pntStartPos �����J�n�n�_
	 @param nRivCode �Ώۉ͐��gid
	 */
	void initialBasinSearch( QgsPointXY &pntStartPos, int nRivCode );
#endif

	/** �S�Ă̓y�n���p���W�v���� */
	void aggregateAllLu();

	/** 
	 ���݂̎x����̓y�n���p���W�v����
	 @param nCurrentRivCode �Ώۉ͐��gid
	 @param dLrsLength �Ώۉ͐쉺���[�����LRS����
	 @param bGetName lumesh����͐얼�̂��擾���邩�ǂ���
	 */
	void aggregateCurrentLu( int nCurrentRivCode, double dLrsLength, bool bGetName = false );

	/** �㗬�̓y�n���p���W�v���� */
	void aggregateUpstreamLu();

	/** SQLite�n���h�� */
	sqlite3 *m_pSQLiteHandle;

	/** �f�[�^�׃t�@�C���� */
	QString m_strDbName;

	/** �f�[�^�x�[�X���ڑ�����Ă��邩�ǂ��� */
	bool m_bOpen;

	/** �W�v�N�_���W */
	QgsPointXY m_pnt;

	/** ���e���W�nSRID */
	int m_nSrid;

	/** ���̃N���X�̃V���O���g�� */
	static QueryManage *m_QueryManage;

	/** �y�n���p�e�[�u�� */
	QVector<LUINFO> m_vLuFields;

	/** �N�G������ */
	QMap<int, double> m_mapResult;

	/** �������ꂽ�x�����ID */
	QVector<int> m_vSearchedBasins;

	/** �������ꂽ�y�n���p���b�V����ID */
	QVector<int> m_vSearchedMeshes;

	/** �N���b�N�����n�_�̉͐얼 */
	QString m_strRivName;

	/** ���������s���ꂽ���ǂ��� */
	bool m_bQueryed;

	/** Spatialite�L���b�V���I�u�W�F�N�g */	
	void *m_pCache;

	/** �X�^�[�g�n�_���܂މ͐���̔z�� */
	QVector<InitialRivInfo> m_vInitRivInfo;

	/** �X�^�[�g�n�_�����܂ޖ������̉͐� */
	QQueue<InitRivPos> m_qInitRivPos;

	/** �����J�n�ʒu�ɑ΂��ĉ͐�܂ł̋����͈͂����肷�邩�ǂ��� */
	bool m_bCheckDist;

};

