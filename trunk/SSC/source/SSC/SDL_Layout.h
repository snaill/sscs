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

#ifndef SDL_LAYOUT_H_INCLUDED
#define SDL_LAYOUT_H_INCLUDED

#include "SDL_Glyph.h"
#include "SDL_Container.h"

/// @brief 所有界面布局的基类，实现固定布局，即对内部控件不做处理
class SDL_Layout : public SDL_Object
{
// 基本属性
public:
	virtual SDL_Rect GetBounds()	{
		SDL_Rect	rc;
		rc.x = m_x;
		rc.y = m_y;
		rc.w = m_w;
		rc.h = m_h;
		return rc;
	}

    virtual void SetBounds( const SDL_Rect * lprc )
    {
		m_x = lprc->x;
		m_y = lprc->y;
		m_w = lprc->w;
		m_h = lprc->h;
    }

	virtual SDL_Size GetPreferedSize(){		
		return SDL_Size( 32, 32 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void Update( SDL_Container * pContainer, const SDL_Rect * lprc ) = 0;

protected:
	SDL_Layout() : m_x(0), m_y(0), m_w(0), m_h(0) {}
    virtual ~SDL_Layout()	{ }

protected:
	Sint16		m_x, m_y;
	Uint16		m_w, m_h;
};

#endif // SDL_LAYOUT_H_INCLUDED
