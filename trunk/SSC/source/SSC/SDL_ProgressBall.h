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

#include "SDL_ProgressBar.h"

/// @brief 进度条处理类，包括文档进度及当前的翻页进度
class SDL_ProgressBall : public SDL_ProgressBar
{
public:
	SDL_ProgressBall( );
	virtual ~SDL_ProgressBall(void);

	//
	virtual const char * GetType()			{ return "progressball";	}

	/// @brief 获取装饰器除去客户图元以后的矩形位置
	/// @param lprc 返回的矩形位置
	SDL_Size GetPreferedSize();

	/// @brief 设置修饰器图元矩形，包括客户图元的矩形范围，所以同时更新客户图元的矩形
	/// @param lpsz 图元矩形指针
	virtual void SetBounds( const SDL_Rect  * lpsz );

protected:
	virtual void DrawWidget( SDL_Surface * screen );
};
