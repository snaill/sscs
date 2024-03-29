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

#include "SDL_Image.h"

SDL_Image::SDL_Image( const char * bmp )
{
    m_pBitmap = SDL_LoadBMP( bmp );
}

SDL_Image::~SDL_Image(void)
{
    if ( m_pBitmap )
        SDL_FreeSurface( m_pBitmap );
}

void SDL_Image::GetMinSize( int * w, int * h, SDL_DC * pDC )
{
	if ( !m_pBitmap )
	{
		*w = *h = 0;
	}
	else
	{
		*w = m_pBitmap->w;
		*h = m_pBitmap->h;
	}
}

void SDL_Image::Draw( SDL_Surface * screen, SDL_DC * pDC )
{
	if ( m_pBitmap )
	{
        SDL_Rect    rcOldClip;
        SDL_GetClipRect( screen, &rcOldClip );
        SDL_SetClipRect( screen, &m_rc );
        SDL_BlitSurface(m_pBitmap, 0, screen, &m_rc);
	    SDL_SetClipRect( screen, &rcOldClip );
	}
}
