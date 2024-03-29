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

#ifndef SDL_STATIC_H_INCLUDED
#define SDL_STATIC_H_INCLUDED

#include "SDL_Widget.h"

class SDL_Static : public SDL_Widget
{
// ʵ�ָ��ӿ�
public:
	SDL_Static( SDL_Glyph * pg );
	virtual ~SDL_Static(void);

	virtual const char * GetType()				{ return "label"; }
};

#endif //!SDL_STATIC_H_INCLUDED
