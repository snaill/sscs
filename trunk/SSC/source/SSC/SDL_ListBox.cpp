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
#include "SDL_WindowManager.h"

SDL_ListBox::SDL_ListBox()		
{
	m_curItem = 0;
}

SDL_ListBox::~SDL_ListBox()	
{
	if ( m_curItem )
		m_curItem->Release();
}

SDL_Size SDL_ListBox::GetPreferedSize()	
{
	SDL_Size	sz( 0, 0 );
	//
	//SDL_Iterator<SDL_Glyph> pos; 
	//GetCurrentLayout()->GetIterator<SDL_Glyph>( &pos );
	//for ( pos.First(); !pos.IsDone(); pos.Next() )
	//{
	//	SDL_Size size = pos.GetCurrentItem()->GetPreferedSize();
	//	sz.h += size.h;
	//	if ( sz.w < size.w )
	//		sz.w = size.w;
	//}

	return sz;
}

bool SDL_ListBox::OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	
{
	//if ( button->button != SDL_BUTTON_LEFT )
	//	return false;

	//SDL_Iterator<SDL_Glyph> pos; 
	//GetIterator<SDL_Glyph>( &pos );
	//for ( pos.First(); !pos.IsDone(); pos.Next() )
	//{
	//	SDL_Glyph * g = pos.GetCurrentItem();
	//	if ( !g->IsIn( button->x, button->y ) )
	//		continue;

	//	SDL_ListBoxItem * pItem = dynamic_cast<SDL_ListBoxItem *>( g );
	//	if ( pItem )
	//	{
	//		pItem->SetSelected( true );
	//		*bDraw = true;	
	//	}
	//	return true;
	//}
	return false;
}

bool SDL_ListBox::OnMouseUp( const SDL_MouseButtonEvent * button, bool * bDraw )
{
	//if ( button->button != SDL_BUTTON_LEFT )
	//	return false;

	//SDL_Iterator<SDL_Glyph> pos; 
	//GetIterator<SDL_Glyph>( &pos );
	//for ( pos.First(); !pos.IsDone(); pos.Next() )
	//{
	//	SDL_Glyph * g = pos.GetCurrentItem();
	//	if ( !g->IsIn( button->x, button->y ) )
	//		continue;

	//	SDL_ListBoxItem * pItem = dynamic_cast<SDL_ListBoxItem *>( g );
	//	if ( pItem && pItem->GetSelected() )
	//	{
	//		pItem->SetSelected( false );
	//		select( pItem );
	//		*bDraw = true;	
	//	}
	//	return true;
	//}
	return false;
}

bool SDL_ListBox::OnMouseMove( const SDL_MouseMotionEvent * motion, bool * bDraw )
{
	//if ( !( motion->state & SDL_BUTTON(1) ) )
	//	return false;

	//GetCurrentLayout()->Scroll( motion->yrel, this );

	////
	//SDL_Iterator<SDL_Glyph> pos; 
	//GetIterator<SDL_Glyph>( &pos );
	//for ( pos.First(); !pos.IsDone(); pos.Next() )
	//{
	//	SDL_Glyph * g = pos.GetCurrentItem();
	//	if ( !g->IsIn( motion->x, motion->y ) )
	//		continue;

	//	SDL_ListBoxItem * pItem = dynamic_cast<SDL_ListBoxItem *>( g );
	//	if ( pItem && pItem->GetSelected() )
	//	{
	//		pItem->SetSelected( false );
	//	}
	//	break;
	//}
	//*bDraw = true;
	return true;
}

void SDL_ListBox::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc )
{
	SDL_Theme * theme = SDL_WindowManager::Get()->GetTheme();

	SDL_Color	color = theme->GetColor( SDL_Theme::Background );
	SDL_FillRect( screen, ( SDL_Rect * )lprc, SDL_MapRGB( screen->format, color.r, color.g, color.b ) );

	//
	SDL_Glyph::DrawWidget( screen, lprc );
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

	m_curItem = g->GetObj<SDL_Glyph>();

	SDL_Rect	rc = g->GetBounds();
	if ( rc.y < m_pt.y )
		GetCurrentLayout()->Scroll( m_pt.y - rc.y, this );
	if ( rc.y + rc.h > m_pt.y + m_sz.h )
		GetCurrentLayout()->Scroll( m_pt.y + m_sz.h - rc.h - rc.y, this );
}