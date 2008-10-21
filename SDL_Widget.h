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

#ifndef SDL_WIDGET_H_INCLUDED
#define SDL_WIDGET_H_INCLUDED

#include "SDL_Glyph.h"

/// @brief 控件类的基类
class SDL_Widget : public SDL_Glyph
{
public:
    /// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
    virtual void GetMinSize( int * w, int * h );

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc );

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen );

    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event);

public:
    virtual void SetClientObject( SDL_Glyph * pg );

protected:
    SDL_Widget();
    virtual ~SDL_Widget();

    virtual void GetClientRect( SDL_Rect *rc );

    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
    virtual void DrawWidget( SDL_Surface * screen ) {}

    virtual void OnMouseEnter() {}
    virtual void OnMouseLeave() {}

protected:
    /// Widget状态
    SDL_WidgetStatus    m_aStatus;

    /// 客户对象，允许是图元或布局
    SDL_Glyph *         m_pg;
};

#endif // SDL_WIDGET_H_INCLUDED
