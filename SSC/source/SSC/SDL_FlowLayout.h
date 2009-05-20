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

#ifndef SDL_FLOWLAYOUT_H_INCLUDED
#define SDL_FLOWLAYOUT_H_INCLUDED

#include "SDL_Layout.h"

/// @brief 所有界面布局的基类，实现固定布局
class SDL_FlowLayout : public SDL_Layout
{
public:
	SDL_FlowLayout()            {}

    virtual ~SDL_FlowLayout()	  { }

	virtual const char * GetType()				{ return "SDL_FlowLayout"; }

	virtual SDL_Size GetPreferedSize()	{
		//!!!!!
		return SDL_Size( 0, 0 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc ) {
		int x = lprc->x, y = lprc->y, w = lprc->w, h = lprc->h;
		SDL_Rect	rcItem;

		SDL_Iterator<SDL_Glyph> pos; 
		GetIterator<SDL_Glyph>( &pos );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Glyph * pItem = pos.GetCurrentItem();

			SDL_Size size = pItem->GetPreferedSize();
			rcItem.x = x;
			rcItem.y = y;
			rcItem.w = size.w;
			rcItem.h = size.h;
			pItem->SetBounds( &rcItem );
			x += size.w;
		}
    }
};

#endif // SDL_FLOWLAYOUT_H_INCLUDED
