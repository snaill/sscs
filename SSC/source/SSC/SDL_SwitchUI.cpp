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

#include "SDL_SwitchUI.h"
#include "SDL_Widget.h"

void SDL_SwitchUI::ToLeft( SDL_Surface * screen, const SDL_Rect * lprc, SDL_Surface * oldSurface, SDL_Surface * newSurface )
{
	SDL_Rect	rcOld;
	SDL_GetClipRect( screen, &rcOld );
	SDL_SetClipRect( screen, lprc );

	int xOff = lprc->w / 10;
	SDL_Rect	rectOld, rectNew;
	rectOld = rectNew = *lprc;
	rectNew.x = lprc->x + lprc->w;
	for ( int i = 0; i < 9; i ++ )
	{
		rectOld.x -= xOff;
		rectOld.w -= xOff;
		rectNew.x += xOff;
		rectNew.w += xOff;
		SDL_BlitSurface( oldSurface, 0, screen, &rectOld );
		SDL_BlitSurface( newSurface, 0, screen, &rectNew );

		SDL_UpdateRect(screen, lprc->x, lprc->y, lprc->w, lprc->h);

		SDL_Delay( 100 );
	}
		
	SDL_BlitSurface( newSurface, 0, screen, ( SDL_Rect * )lprc );

	SDL_SetClipRect( screen, &rcOld );
}
