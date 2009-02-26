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

#ifndef SDL_LISTBOX_H_INCLUDED
#define SDL_LISTBOX_H_INCLUDED

#include "SDL_Widget.h"
#include "SDL_ListBoxItem.h"
#include "SDL_ScrollBoxLayout.h"

/// @brief 控件类的基类
class SDL_ListBox : public SDL_Widget
{
public:
	sigslot::signal1<SDL_ListBoxItem *>		select;

// 基本属性
public:
	SDL_ListBox()		{
		m_curItem = 0;
		m_pLayout = new SDL_ScrollBoxLayout();
	}

	virtual ~SDL_ListBox()	{}

	virtual const char * GetType()				{ return "SDL_ListBox"; }

	virtual SDL_Size GetPreferedSize()	{
		SDL_Size	sz( 0, 0 );
		
		SDL_Iterator<SDL_Glyph> pos; 
		GetIterator<SDL_Glyph>( &pos );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Size size = pos.GetCurrentItem()->GetPreferedSize();
			sz.h += size.h;
			if ( sz.w < size.w )
				sz.w = size.w;
		}

		return sz;
	}

protected:
	inline SDL_ScrollBoxLayout * GetCurrentLayout()	{ return (SDL_ScrollBoxLayout *)GetLayout(); }

	virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	{
		if ( button->button != SDL_BUTTON_LEFT )
			return false;

		SDL_Iterator<SDL_Glyph> pos; 
		GetIterator<SDL_Glyph>( &pos );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Glyph * g = pos.GetCurrentItem();
			if ( !g->IsIn( button->x, button->y ) )
				continue;

			SetFocus();

			SDL_ListBoxItem * pItem = dynamic_cast<SDL_ListBoxItem *>( g );
			if ( pItem )
			{
				SelectItem( pItem );
				*bDraw = true;	
			}
			return true;
		}
		return false;
	}

	virtual bool OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw ) {
		switch ( key->keysym.sym )
		{
		case SDLK_UP:
			if ( !m_curItem )
				SelectItem( GetCurrentLayout()->GetBottom( this ) );
			else
			{
				SDL_Glyph * g =  GetItem( GetItemID( m_curItem ) - 1 );
				SDL_Widget * pItem = dynamic_cast<SDL_Widget *>(g);
				if ( pItem )
					SelectItem( pItem );
			}
			*bDraw = true;
			break;
		case SDLK_DOWN:
			if ( !m_curItem )
				SelectItem( dynamic_cast<SDL_Widget *>( GetItem( 0 ) ) );
			else
			{
				SDL_Glyph * g =  GetItem( GetItemID( m_curItem ) + 1 );
				SDL_Widget * pItem = dynamic_cast<SDL_Widget *>(g);
				if ( pItem )
					SelectItem( pItem );
			}
			*bDraw = true;
			break;		
		default:
			return false;
		}

		return true;
	}

    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
 //   virtual void DrawWidget( SDL_Surface * screen ){}

	void SelectItem( SDL_Glyph * g )	{
		if ( g == m_curItem )
			return;

		SDL_ListBoxItem * pCurItem = dynamic_cast<SDL_ListBoxItem *>(m_curItem);
		if ( pCurItem )
			pCurItem->SetSelected( false );
		
		SDL_ListBoxItem * pItem = dynamic_cast<SDL_ListBoxItem *>(g);
		if ( pItem )
			pItem->SetSelected( true );

		m_curItem = g;
		if ( pItem )
			select( pItem );

		SDL_Rect	rc = pItem->GetBounds();
		if ( rc.y < m_pt.y )
			GetCurrentLayout()->Scroll( m_pt.y - rc.y, this );
		if ( rc.y + rc.h > m_pt.y + m_sz.h )
			GetCurrentLayout()->Scroll( m_pt.y + m_sz.h - rc.h - rc.y, this );
	}

protected:
	SDL_Glyph *	m_curItem;
};

#endif // SDL_LISTBOX_H_INCLUDED
