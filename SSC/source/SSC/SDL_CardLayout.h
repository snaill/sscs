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

#ifndef SDL_CARDLAYOUT_H_INCLUDED
#define SDL_CARDLAYOUT_H_INCLUDED

#include "SDL_Layout.h"

/// @brief 所有界面布局的基类，实现固定布局
class SDL_CardLayout : public SDL_Layout
{
// 基本属性
public:
	SDL_CardLayout() : m_pActiveItem(0)  	{ }
    virtual ~SDL_CardLayout()				{ }

	virtual const char * GetType()				{ return "SDL_CardLayout"; }
	
// 方法
public:
	virtual SDL_Size GetPreferedSize()	{
		return m_pActiveItem ? m_pActiveItem->GetPreferedSize() : SDL_Size( 0, 0 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc )
    {
		if ( m_pActiveItem )
			m_pActiveItem->SetBounds( lprc );
    }

public:
	SDL_Glyph *	GetActiveItem()						{ return m_pActiveItem;	}
	void SetActiveItem( SDL_Glyph * pActiveItem )	{ m_pActiveItem = pActiveItem;	}

protected:
	SDL_Glyph *			m_pActiveItem;
};

#endif // SDL_CARDLAYOUT_H_INCLUDED
