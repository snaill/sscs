#pragma once

#include "../SDL_Widget.h"

///<summary>
/// CImageView��ļ�Ҫ˵��
///
/// ʵ�����е�ͼƬ�����������ƶ���������ͨ�����ĵ�������е�
///
/// ����: Snaill
/// �汾: 1.0
/// ����: 2007/6/4
///</summary>
class SDL_ImageView :  public SDL_Widget
{
protected:
	///<summary>�ļ���</summary>
	char *				m_pszFilename;

	///<summary>ԭʼͼƬ����</summary>
	SDL_Surface *			m_pObject;

	///<summary>ͼƬ��ʾ����</summary>
	SDL_Rect		m_rcImage;

	///<summary>���ű���</summary>
	long		m_lRatio;

	///<summary>�Ƿ�ʼ���Ŷ���</summary>
	bool		m_bPlay;

	///<summary>�ʺ�״̬,0:ʵ�ʴ�С;1:�ʺϿ��;2:�ʺϸ߶�;3:�ʺ���Ļ</summary>
	int			m_nFitState;
public:

	///<summary>
	/// CImageView�Ĺ��캯��
	///</summary>
	SDL_ImageView(void);

	///<summary>
	/// CImageView����������
	///</summary>
	virtual ~SDL_ImageView(void);

	virtual const char * GetType() { return "imageview"; }

	///<summary>
	/// ����get_FileName��ժҪ˵��
	///</summary>
	///<returns>����ֵ��˵��///</returns>
	const char * get_FileName();

	///<summary>
	/// ����put_FileName��ժҪ˵��
	///</summary>
	///<param name='"lpsz">����lpsz��˵��</param>
	///<returns>
	/// ����ֵ��˵��
	/// ����TRUE ...
	/// ����FALSE ...
	///</returns>
	bool Load( const char * lpsz );

	///<summary>
	/// ����get_Object��ժҪ˵��
	///</summary>
	///<returns>
	/// ����ֵ��˵��
	/// ����NULL ...
	///</returns>
	SDL_Surface * get_Object();

	///<summary>
	/// ����put_Object��ժҪ˵��
	///</summary>
	///<param name="obj">����obj��˵��</param>
	///<returns>
	/// ����ֵ��˵��
	/// ����TRUE ...
	/// ����FALSE ...
	///</returns>
	bool put_Object( SDL_Surface * obj );
	
	//double get_Ratio();
	//void put_Ratio( double ratio );
	//int get_Angle();
	//void put_Angle( int ratio );

protected:
	///<summary>
	/// ���ݵ�ǰ�����ű������¼���ͼƬ�ľ��η�Χ
	///</summary>
	void RecalcImageRect();
	void DrawWidget( SDL_Surface * screen );

	bool OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw );
	bool OnMouseMove( const SDL_MouseMotionEvent * motion, bool * bDraw );
};
