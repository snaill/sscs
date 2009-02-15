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
#include "SDL_ImageList.h"

SDL_Image::SDL_Image( SDL_ImageList * imgList, int iImage )
{
    m_pBitmap = 0;
	m_imgList = imgList;
	m_iImage = iImage;
}

SDL_Image::~SDL_Image(void)
{
    if ( m_pBitmap )
        SDL_FreeSurface( m_pBitmap );
    if ( m_imgList )
		m_imgList->Release();
}

SDL_Size SDL_Image::GetPreferedSize()
{
	if ( m_pBitmap )
	{
		return SDL_Size( m_pBitmap->w, m_pBitmap->h );
	}
	else if ( m_imgList )
	{
		return m_imgList->GetImageSize();
	}

	return SDL_Size( 0, 0 );
}

void SDL_Image::Draw( SDL_Surface * screen )
{
	SDL_Rect	rect = GetBounds();
	if ( m_pBitmap ) 
	{
		if ( m_pBitmap->w < rect.w )
			rect.x += ( rect.w - m_pBitmap->w ) / 2;
		if ( m_pBitmap->h < rect.h )
			rect.y += ( rect.h - m_pBitmap->w ) / 2;
		rect.w = m_pBitmap->w;
		rect.h = m_pBitmap->h;
		SDL_BlitSurface( m_pBitmap, 0, screen, &rect );
	}
	else
	{
		SDL_Size sz = m_imgList->GetImageSize();
		if ( sz.w < rect.w )
			rect.x += ( rect.w - sz.w ) / 2;
		if ( sz.h < rect.h )
			rect.y += ( rect.h - sz.h ) / 2;

		m_imgList->Draw( m_iImage, screen, rect.x, rect.y );
	}
}
