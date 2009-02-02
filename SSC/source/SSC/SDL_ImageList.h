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

/// @brief ImageList
class SDL_ImageList : public SDL_Object
{
// »ù±¾ÊôÐÔ
public:
	SDL_ImageList(): m_size(0, 0), m_grow(0) {}

    virtual ~SDL_ImageList()	{
		for ( std::vector< SDL_Surface * >::iterator pos = m_images.begin(); pos != m_images.end(); pos ++ )
			SDL_FreeSurface( *pos );
		m_images.clear();
	}

	virtual const char * GetType()	{ return "imagelist"; }

	bool Create( int cx, SDL_Surface * surface, SDL_Color crMask )	{
		SDL_Surface * image = SDL_ConvertSurface( surface, surface->format, surface->flags );
		if ( !image )
			return false;

		SDL_SetColorKey( image, SDL_SRCCOLORKEY, SDL_MapRGB( surface->format, crMask.r, crMask.g, crMask.b ) );
		m_size.w = cx;
		m_size.h = image->h;
		m_grow = image->w / cx;
		m_count = m_grow;
		m_images.push_back( image );
		return true;
	}

	void Draw( int iImage, SDL_Surface * screen, int x, int y ) {
		int index = iImage / m_grow;

		SDL_Rect	rcSrc, rcTarget;
		rcSrc.x = iImage % m_grow * m_size.w;
		rcSrc.y = 0;
		rcTarget.x = x;
		rcTarget.y = y;
		rcSrc.w = rcTarget.w = m_size.w;
		rcSrc.h = rcTarget.h = m_size.h;

		SDL_BlitSurface(m_images[ index ], &rcSrc, screen, &rcTarget );
	}

	SDL_Size GetImageSize()	{
		return m_size;
	}
protected:
	std::vector<SDL_Surface*>	m_images;
	SDL_Size		m_size;
	int				m_count;
	int				m_grow;
};

#endif //!SDL_IMAGELIST_H_INCLUDED
