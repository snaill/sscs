/*
 * SDL_Image.cpp
 * Copyright (C) Snaill 2008 <snaill@jeebook.com>
 *
    SDL_Image.cpp is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    main.c is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

void SDL_Image::GetBounds( SDL_Rect * lprc )
{
	if ( !m_pBitmap )
	{
		lprc->x = lprc->y = lprc->w = lprc->h = 0;
	}
	else
	{
        lprc->x = lprc->y = 0;
		lprc->w = m_pBitmap->w;
		lprc->h = m_pBitmap->h;
	}
}

void SDL_Image::Draw( SDL_Surface * screen )
{
	if ( m_pBitmap )
	{
        SDL_BlitSurface(m_pBitmap, 0, screen, &m_rc);
	}
}
