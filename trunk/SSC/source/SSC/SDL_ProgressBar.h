/*
 * SDL_SimpleControls
 * Copyright (C) 2008 Snaill
 *
    SDL_SimpleControls is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SDL_SimpleControls is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Snaill  <snaill@jeebook.com>
 */

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
	virtual const char * GetType()			{ return "SDL_ProgressBar";	}

	/// @brief 获取装饰器除去客户图元以后的矩形位置
	/// @param lprc 返回的矩形位置
	SDL_Size GetPreferedSize();

	inline int GetPos()				{ return m_nPos;				}
	inline void SetPos( int nPos )	{ m_nPos = nPos;				}

	void HitTest( POINT pt, int &nCommand, int &nPos );
protected:
	virtual void DrawWidget( SDL_Surface * screen );
};
