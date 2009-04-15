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

#ifndef SDL_SCROLLBOXLAYOUT_H_INCLUDED
#define SDL_SCROLLBOXLAYOUT_H_INCLUDED

#include "SDL_Layout.h"

/// @brief 所有界面布局的基类，实现固定布局
class SDL_ScrollBoxLayout : public SDL_Layout
{
public:
	SDL_ScrollBoxLayout()             { }

    virtual ~SDL_ScrollBoxLayout()	  { }

	virtual const char * GetType()				{ return "SDL_ScrollBoxLayout"; }

	virtual SDL_Size GetPreferedSize( SDL_Container * pContainer )	{
		//!!!!!
		return SDL_Size( 0, 0 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void Update( SDL_Container * pContainer, const SDL_Rect * lprc ) {
		//
		SDL_Rect	rcItem;
		rcItem.x = lprc->x;
		rcItem.y = lprc->y;
		rcItem.w = lprc->w;

		SDL_Iterator<SDL_Glyph> pos; 
		pContainer->GetIterator<SDL_Glyph>( &pos );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Glyph * pItem = pos.GetCurrentItem();
			SDL_Size	size = pItem->GetPreferedSize();
			rcItem.h = size.h;
			pItem->SetBounds( &rcItem );

			rcItem.y += rcItem.h;
		}

		//
		SDL_Layout::SetBounds( lprc );
    }

public:
	void Scroll( int nValue, SDL_Widget * pContainer )	{
		if ( !nValue )
			return;

		SDL_Iterator<SDL_Glyph> pos; 
		pContainer->GetIterator<SDL_Glyph>( &pos );
		pos.First();
		if ( pos.IsDone() )
			return;

		if ( nValue > 0 )
		{
			SDL_Glyph * pItem = pos.GetCurrentItem();
			SDL_Rect	rc = pItem->GetBounds();
			if ( rc.y + nValue > m_pt.y )
				nValue = m_pt.y - rc.y;
		}
		else
		{
			SDL_Iterator<SDL_Glyph> pos2; 
			pContainer->GetIterator<SDL_Glyph>( &pos2, true );
			pos2.First();
			SDL_Glyph * pItem = pos2.GetCurrentItem();
			SDL_Rect	rc = pItem->GetBounds();
			if ( rc.y + rc.h < m_pt.y + m_sz.h )
				return;

			if ( rc.y + rc.h + nValue < m_pt.y + m_sz.h )
				nValue = m_pt.y + m_sz.h - rc.y - rc.h;
		}

		//
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Glyph * pItem = pos.GetCurrentItem();
			SDL_Rect	rc = pItem->GetBounds();
			rc.y += nValue;
			pItem->SetBounds(&rc);
		}
	}
};

#endif // SDL_SCROLLBOXLAYOUT_H_INCLUDED
