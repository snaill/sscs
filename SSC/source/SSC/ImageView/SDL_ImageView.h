#pragma once

#include "../SDL_Widget.h"

///<summary>
/// CImageView类的简要说明
///
/// 实现所有的图片操作，其中移动和缩放是通过中心点操作进行的
///
/// 作者: Snaill
/// 版本: 1.0
/// 日期: 2007/6/4
///</summary>
class SDL_ImageView :  public SDL_Widget
{
protected:
	///<summary>文件名</summary>
	char *				m_pszFilename;

	///<summary>原始图片对象</summary>
	SDL_Surface *			m_pObject;

	///<summary>图片显示区域</summary>
	SDL_Rect		m_rcImage;

	///<summary>缩放比例</summary>
	long		m_lRatio;

	///<summary>是否开始播放动画</summary>
	bool		m_bPlay;

	///<summary>适合状态,0:实际大小;1:适合宽度;2:适合高度;3:适合屏幕</summary>
	int			m_nFitState;
public:

	///<summary>
	/// CImageView的构造函数
	///</summary>
	SDL_ImageView(void);

	///<summary>
	/// CImageView的析构函数
	///</summary>
	virtual ~SDL_ImageView(void);

	virtual const char * GetType() { return "imageview"; }

	///<summary>
	/// 函数get_FileName的摘要说明
	///</summary>
	///<returns>返回值的说明///</returns>
	const char * get_FileName();

	///<summary>
	/// 函数put_FileName的摘要说明
	///</summary>
	///<param name='"lpsz">参数lpsz的说明</param>
	///<returns>
	/// 返回值的说明
	/// 返回TRUE ...
	/// 返回FALSE ...
	///</returns>
	bool Load( const char * lpsz );

	///<summary>
	/// 函数get_Object的摘要说明
	///</summary>
	///<returns>
	/// 返回值的说明
	/// 返回NULL ...
	///</returns>
	SDL_Surface * get_Object();

	///<summary>
	/// 函数put_Object的摘要说明
	///</summary>
	///<param name="obj">参数obj的说明</param>
	///<returns>
	/// 返回值的说明
	/// 返回TRUE ...
	/// 返回FALSE ...
	///</returns>
	bool put_Object( SDL_Surface * obj );
	
	//double get_Ratio();
	//void put_Ratio( double ratio );
	//int get_Angle();
	//void put_Angle( int ratio );

protected:
	///<summary>
	/// 根据当前的缩放比例重新计算图片的矩形范围
	///</summary>
	void RecalcImageRect();
	void DrawWidget( SDL_Surface * screen );

	bool OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw );
	bool OnMouseMove( const SDL_MouseMotionEvent * motion, bool * bDraw );
};
