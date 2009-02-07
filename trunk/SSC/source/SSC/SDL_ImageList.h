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

#ifndef SDL_IMAGELIST_H_INCLUDED
#define SDL_IMAGELIST_H_INCLUDED

#include "SDL_Object.h"
#include <stdio.h>

/// @brief ImageList
class SDL_ImageList : public SDL_Object
{
// »ù±¾ÊôÐÔ
public:
	SDL_ImageList(): m_size(0, 0), m_grow(1), m_images(0) {}

    virtual ~SDL_ImageList()	{
		SDL_FreeSurface( m_images );
	}

	virtual const char * GetType()	{ return "imagelist"; }

	void Create( int cx, int cy, int grow )	{
		m_size.w = cx;
		m_size.h = cy;
		m_grow = grow;
		
		Destory();
	}

	void Destory() {
		if ( m_images )
			SDL_FreeSurface( m_images );
		m_images = 0;
	}

	bool CreateFromBitmap( int cx, SDL_Surface * surface, SDL_Color crMask )	{
		Destory();

		m_images = SDL_ConvertSurface( surface, surface->format, surface->flags );
		if ( !m_images )
			return false;

		SDL_SetColorKey( m_images, SDL_SRCCOLORKEY, SDL_MapRGB( surface->format, crMask.r, crMask.g, crMask.b ) );
		m_size.w = cx;
		m_size.h = surface->h;
		m_grow = 1;		
		m_count = m_images->w / cx;
		return true;
	}

	void Add( SDL_Surface * surface )	{
		SDL_Rect		rc;
		if ( m_images )
		{
			if ( m_images->w - m_count * m_size.w < surface->w )
			{
				SDL_Surface * image = SDL_CreateRGBSurface( 0, m_images->w + ( surface->w > m_size.w * m_grow ? surface->w : m_size.w * m_grow ), m_size.h, m_images->format->BitsPerPixel, 
										  m_images->format->Rmask, m_images->format->Gmask, m_images->format->Bmask, m_images->format->Amask );
				SDL_BlitSurface( m_images, 0, image, 0 );	
				SDL_FreeSurface( m_images );
				m_images = image;
			}

			rc.x = ( m_count + 1 ) * m_size.w;
			rc.y = 0;
			rc.w = surface->w;
			rc.h = m_size.h < surface->h ? m_size.h : surface->h;
			SDL_BlitSurface(surface, 0, m_images, &rc );
		}
		else
		{
			m_images = SDL_CreateRGBSurface( 0, ( surface->w > m_size.w * m_grow ? surface->w : m_size.w * m_grow ), m_size.h, surface->format->BitsPerPixel, 
										  surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
			
			SDL_BlitSurface(surface, 0, m_images, 0 );				
		}
	}

	void Draw( int iImage, SDL_Surface * screen, int x, int y ) {

		SDL_Rect	rcSrc, rcTarget;
		rcSrc.x = iImage * m_size.w;
		rcSrc.y = 0;
		rcTarget.x = x;
		rcTarget.y = y;
		rcSrc.w = rcTarget.w = m_size.w;
		rcSrc.h = rcTarget.h = m_size.h;

		SDL_BlitSurface(m_images, &rcSrc, screen, &rcTarget );
	}

	SDL_Size GetImageSize()	{
		return m_size;
	}
protected:
	SDL_Surface *	m_images;
	SDL_Size		m_size;
	int				m_count;
	int				m_grow;
};

#endif //!SDL_IMAGELIST_H_INCLUDED
