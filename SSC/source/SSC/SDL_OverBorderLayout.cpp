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

#include "SDL_OverBorderLayout.h"

SDL_Size SDL_OverBorderLayout::GetPreferedSize( )	
{
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
			sz.w = max( sz.w, szItem.w );
			sz.h = max( sz.h, szItem.h );
		}
	}

	return sz;
}

void SDL_OverBorderLayout::SetBounds( const SDL_Rect * lprc )
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
			rcItem.x = lprc->x;
			rcItem.y = lprc->y;
			rcItem.w = lprc->w;
			rcItem.h = lprc->h;
		}
		pItem->SetBounds( &rcItem );
	}
}

void SDL_OverBorderLayout::DrawWidget( SDL_Surface * screen )	
{
	SDL_Iterator<SDL_Glyph> pos;
	GetIterator<SDL_Glyph>( &pos, true );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = pos.GetCurrentItem();
		pItem->Draw( screen );
	}
}

bool SDL_OverBorderLayout::HandleMouseEvent( const SDL_Event *event, bool * bDraw )
{
	SDL_Iterator<SDL_Glyph> pos; 
	GetIterator<SDL_Glyph>( &pos );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = dynamic_cast<SDL_Glyph *>( pos.GetCurrentItem() );
		if ( pItem && pItem->GetVisible() )
			if ( pItem->HandleMouseEvent( event, bDraw ) )
				return true;
	}

	return false;
}
