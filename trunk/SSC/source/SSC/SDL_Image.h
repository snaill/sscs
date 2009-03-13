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

class SDL_ImageList;
class SDL_Image :	public SDL_Glyph
{
public:
	SDL_Image( SDL_Surface * surface );
	SDL_Image( SDL_ImageList * imgList, int iImage );
	virtual ~SDL_Image(void);

	virtual const char * GetType()				{ return "SDL_Image"; }

	virtual SDL_Size GetPreferedSize();
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc );

protected:
	SDL_Surface	*		m_pBitmap;
	SDL_ImageList *		m_imgList;
	int					m_iImage;
};

#endif //!SDL_IMAGE_H_INCLUDED
