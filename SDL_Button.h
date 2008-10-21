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

#ifndef SDL_BUTTON_H_INCLUDED
#define SDL_BUTTON_H_INCLUDED

#include "SDL_Widget.h"

class SDL_Button :	public SDL_Widget
{
public:
	SDL_Button( SDL_Glyph * pg );
	virtual ~SDL_Button(void);

	virtual const char * GetType()				{ return "button"; }

    /// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
    virtual void GetMinSize( int * w, int * h );

    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event);

protected:

    virtual void GetClientRect( SDL_Rect *rc );

    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
    virtual void DrawWidget( SDL_Surface * screen );

};

#endif //!SDL_BUTTON_H_INCLUDED
