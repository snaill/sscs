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

#ifndef SDL_IMAGE_H_INCLUDED
#define SDL_IMAGE_H_INCLUDED

#include "SDL_Glyph.h"

class SDL_Image :	public SDL_Glyph
{
protected:
	SDL_Surface	*	m_pBitmap;

public:
	SDL_Image( const char * );
	virtual ~SDL_Image(void);

	virtual const char * GetType()				{ return "image"; }

	virtual void GetMinSize( int * w, int * h, SDL_DC * pDC );
	virtual void Draw( SDL_Surface * screen, SDL_DC * pDC );
};

#endif //!SDL_IMAGE_H_INCLUDED
