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

#include "SDL_ListBox.h"
#include "SDL_MainFrame.h"
#include <SDL_gfxPrimitives.h>

SDL_ListBox::SDL_ListBox()		
{
	m_curItem = 0;
	m_pLayout = new SDL_ScrollBoxLayout();
}

SDL_ListBox::~SDL_ListBox()	
{
	if ( m_curItem )
		m_curItem->Release();
}

SDL_Size SDL_ListBox::GetPreferedSize()	
{
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

bool SDL_ListBox::OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	
{
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

bool SDL_ListBox::OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw ) 
{
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

void SDL_ListBox::DrawWidget( SDL_Surface * screen )
{
	SDL_FillRect( screen, ( SDL_Rect * )&GetBounds(), SDL_MapRGB( screen->format, 0, 0, 0 ) );

	//
	SDL_Container::DrawWidget( screen );
}

void SDL_ListBox::SelectItem( SDL_Glyph * g )	
{
	if ( g == m_curItem )
		return;

	if ( m_curItem )
	{
		SDL_ListBoxItem * pCurItem = dynamic_cast<SDL_ListBoxItem *>(m_curItem);
		if ( pCurItem )
			pCurItem->SetSelected( false );
		m_curItem->Release();
	}
	
	SDL_ListBoxItem * pItem = dynamic_cast<SDL_ListBoxItem *>(g);
	if ( pItem )
		pItem->SetSelected( true );

	m_curItem = dynamic_cast<SDL_Glyph *>( g->GetObj() );
	if ( pItem )
		select( pItem );

	SDL_Rect	rc = pItem->GetBounds();
	if ( rc.y < m_pt.y )
		GetCurrentLayout()->Scroll( m_pt.y - rc.y, this );
	if ( rc.y + rc.h > m_pt.y + m_sz.h )
		GetCurrentLayout()->Scroll( m_pt.y + m_sz.h - rc.h - rc.y, this );
}