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

#include "SDL_9CellLayout.h"
#include "SDL_Widget.h"

/* SDL_9CellLayout member function */
SDL_Size SDL_9CellLayout::GetPreferedSize( SDL_Container * pContainer )
{
	SDL_Size	sz(0, 0);
	SDL_Iterator<SDL_Glyph> pos;
	
	pContainer->GetIterator<SDL_Glyph>( &pos );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = pos.GetCurrentItem();
		SDL_Size	szItem = pItem->GetPreferedSize();
		sz.w = max( sz.w, szItem.w );
		sz.h = max( sz.h, szItem.h );
	}

	sz.w *= 3;
	sz.h *= 3;
	return sz;
}

void SDL_9CellLayout::Update( SDL_Container * pContainer, const SDL_Rect * lprc )
{
	SDL_Rect	rc;
	rc.x = lprc->x;
	rc.y = lprc->y - lprc->h / 3;
	rc.w = lprc->w / 3;
	rc.h = lprc->h / 3;
	
	SDL_Iterator<SDL_Glyph> pos; 
	pContainer->GetIterator<SDL_Glyph>( &pos );
	pos.First();
	for ( int i = 0; i < 9; i++ )
	{
		if ( pos.IsDone() )
			break;
			
		if ( 0 == i % 3 )
		{
			rc.x = lprc->x;
			rc.y += rc.h; 
		}
		SDL_Glyph * pItem = pos.GetCurrentItem();
		pItem->SetBounds( &rc );
		rc.x += rc.w;
	}
}
