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

#ifndef SDL_CHECKBOX_H_INCLUDED
#define SDL_CHECKBOX_H_INCLUDED

#include "SDL_Widget.h"
#include <SDL_ttf.h>

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_CheckBox : public SDL_Widget
{
public:
    SDL_CheckBox( const wchar_t * text ) {
		if ( text )
			m_text = text;
    }

    virtual ~SDL_CheckBox()				 {}

	virtual const char * GetType()	{ return "listboxitem"; }

	virtual SDL_Size GetPreferedSize();

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen );

	virtual bool OnMouseEnter( const SDL_MouseMotionEvent * motion, bool * bDraw )	{ 
		SDL_Widget::OnMouseEnter( motion, bDraw );
		*bDraw = true;
		return true;	
	}

	virtual bool OnMouseLeave( const SDL_MouseMotionEvent * motion, bool * bDraw )	{ 
		SDL_Widget::OnMouseLeave( motion, bDraw );
		*bDraw = true;
		return true;	
	}
	virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	{
		if ( !IsIn( button->x, button->y ) )
			return false;

		SetCheck( !GetCheck() );
		*bDraw = true;
		return true;
	}

protected:
	std::wstring		m_text;
};

#endif //!SDL_CHECKBOX_H_INCLUDED
