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

#include "SDL_Toolbar.h"
#include "SDL_FlowLayout.h"

SDL_Toolbar::SDL_Toolbar()		
{
	m_pLayout = new SDL_FlowLayout();
}

SDL_Size SDL_Toolbar::GetPreferedSize()	
{
	SDL_Size	sz( 0, 0 );
	
	SDL_Iterator<SDL_Glyph> pos; 
	GetIterator<SDL_Glyph>( &pos, true );
	for ( pos.First(); !pos.IsDone(); pos.Next() )
	{
		SDL_Size size = pos.GetCurrentItem()->GetPreferedSize();
		sz.w += size.w;
		if ( sz.h < size.h )
			sz.h = size.h;
	}

	return sz;
}

void SDL_Toolbar::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc ) 
{ 
	SDL_FillRect( screen, ( SDL_Rect * )lprc, SDL_MapRGB( screen->format, 255, 255, 255 ) );

	SDL_Widget::DrawWidget( screen, lprc );
}