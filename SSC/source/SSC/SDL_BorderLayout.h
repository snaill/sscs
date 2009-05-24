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

#ifndef SDL_BORDERLAYOUT_H_INCLUDED
#define SDL_BORDERLAYOUT_H_INCLUDED

#include "SDL_Layout.h"

/// @brief 所有界面布局的基类，实现固定布局
class SDL_BorderLayout : public SDL_Layout
{
public:
	enum { north, south, west, east, fill };

// 基本属性
public:
	SDL_BorderLayout()		  	{ }
    virtual ~SDL_BorderLayout()	{ }

	virtual const char * GetType()				{ return "SDL_BorderLayout"; }
	
// 方法
public:
	virtual SDL_Size GetPreferedSize()	{
		SDL_Size	sz;

		SDL_Iterator<SDL_Glyph> pos; 
		GetIterator<SDL_Glyph>( &pos, true );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Glyph * pItem = pos.GetCurrentItem();
			SDL_Size	szItem = pItem->GetPreferedSize();
			switch ( pItem->GetLayoutProperty() )
			{
			case north: 
			case south:
				if ( szItem.w > sz.w )
					sz.w = szItem.w;
				sz.h += szItem.h;
				break;
			case west:
			case east:
				sz.w += szItem.w;
				if ( szItem.h > sz.h )
					sz.h = szItem.h;
				break;
			case fill:
				sz.w += szItem.w;
				sz.h += szItem.h;
			}
		}

		return sz;
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc )
    {
		SDL_Rect	rc = *lprc;
		SDL_Iterator<SDL_Glyph> pos; 
		GetIterator<SDL_Glyph>( &pos );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			if ( rc.w == 0 || rc.h == 0 )
				continue;

			SDL_Glyph * pItem = pos.GetCurrentItem();
			SDL_Size	sz = pItem->GetPreferedSize();
			SDL_Rect	rcItem;
			switch ( pItem->GetLayoutProperty() )
			{
			case north:
				rcItem.x = rc.x;
				rcItem.y = rc.y;
				rcItem.w = rc.w;
				rcItem.h = sz.h;
				rc.y += rcItem.h;
				rc.h -= rcItem.h;
				break;
			case south:
				rcItem.x = rc.x;
				rcItem.y = rc.y + rc.h - sz.h;
				rcItem.w = rc.w;
				rcItem.h = sz.h;
				rc.h -= rcItem.h;
				break;
			case west:
				rcItem.x = rc.x;
				rcItem.y = rc.y;
				rcItem.w = sz.w;
				rcItem.h = rc.h;
				rc.x += rcItem.w;
				rc.w -= rcItem.w;
				break;
			case east:
				rcItem.x = rc.x + rc.w - sz.w;
				rcItem.y = rc.y;
				rcItem.w = sz.w;
				rcItem.h = rc.h;
				rc.w -= rcItem.w;
				break;
			case fill:
				rcItem.x = rc.x;
				rcItem.y = rc.y;
				rcItem.w = rc.w;
				rcItem.h = rc.h;
				rc.w = rc.h = 0;
			}
			pItem->SetBounds( &rcItem );
		}

		SDL_Layout::SetBounds( lprc );
    }
};

#endif // SDL_BORDERLAYOUT_H_INCLUDED
