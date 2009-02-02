#pragma once

#include "SDL_Widget.h"

/// @brief 进度条处理类，包括文档进度及当前的翻页进度
class SDL_ProgressBar : public SDL_Widget
{
protected:
	int			m_nPos;

public:
	SDL_ProgressBar( );
	virtual ~SDL_ProgressBar(void);

	//
	virtual const char * GetType()			{ return "progressbar";	}

	/// @brief 获取装饰器除去客户图元以后的矩形位置
	/// @param lprc 返回的矩形位置
	SDL_Size GetPreferedSize();

	/// @brief 设置修饰器图元矩形，包括客户图元的矩形范围，所以同时更新客户图元的矩形
	/// @param lpsz 图元矩形指针
	virtual void SetBounds( const SDL_Rect  * lpsz );

	inline int GetPos()				{ return m_nPos;				}
	inline void SetPos( int nPos )	{ m_nPos = nPos;				}

	void HitTest( POINT pt, int &nCommand, int &nPos );
protected:
	virtual void DrawWidget( SDL_Surface * screen );
};
