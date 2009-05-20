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

#include "SDL_Layout.h"

void SDL_Layout::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc )
{
	SDL_Iterator<SDL_Glyph> pos;
	GetIterator<SDL_Glyph>( &pos );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Glyph * pItem = pos.GetCurrentItem();
		pItem->Draw( screen );
	}
}

bool SDL_Layout::HandleMouseEvent( const SDL_Event *event, bool * bDraw )
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
