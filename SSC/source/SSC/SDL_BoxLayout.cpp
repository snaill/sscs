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

#include "SDL_BoxLayout.h"
#include "SDL_Widget.h"

/* SDL_HBoxLayout member function */
SDL_Size SDL_HBoxLayout::GetPreferedSize( SDL_Container * pContainer )
{
	SDL_Size	sz(0, 0);
	int			nCount = 0;

	SDL_Iterator<SDL_Glyph> pos;
	pContainer->GetIterator<SDL_Glyph>( &pos );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = pos.GetCurrentItem();
		SDL_Size	szItem = pItem->GetPreferedSize();
		sz.w = max( sz.w, szItem.w );
		sz.h = max( sz.h, szItem.h );
		nCount ++;
	}

	sz.w *= nCount;
	return sz;
}

void SDL_HBoxLayout::Update( SDL_Container * pContainer, const SDL_Rect * lprc )
{
	int nCount = pContainer->GetCount();
	SDL_Rect	rc = *lprc;
	rc.w = rc.w / nCount;

	SDL_Iterator<SDL_Glyph> pos; 
	pContainer->GetIterator<SDL_Glyph>( &pos );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = pos.GetCurrentItem();
		pItem->SetBounds( &rc );
		rc.x += rc.w;
	}
}

/* SDL_VBoxLayout member function */
SDL_Size SDL_VBoxLayout::GetPreferedSize( SDL_Container * pContainer )
{
	SDL_Size	sz(0, 0);
	int			nCount = 0;

	SDL_Iterator<SDL_Glyph> pos; 
	pContainer->GetIterator<SDL_Glyph>( &pos, true );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = pos.GetCurrentItem();
		SDL_Size	szItem = pItem->GetPreferedSize();
		sz.w = max( sz.w, szItem.w );
		sz.h = max( sz.h, szItem.h );
		nCount ++;
	}

	sz.h *= nCount;
	return sz;
}

void SDL_VBoxLayout::Update( SDL_Container * pContainer, const SDL_Rect * lprc )
{
	int nCount = pContainer->GetCount();
	SDL_Rect	rc = *lprc;
	rc.h = rc.h / nCount;

	SDL_Iterator<SDL_Glyph> pos; 
	pContainer->GetIterator<SDL_Glyph>( &pos, true );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = pos.GetCurrentItem();
		pItem->SetBounds( &rc );
		rc.y += rc.h;
	}
}
