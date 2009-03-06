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

#ifndef SDL_WINDOW_H_INCLUDED
#define SDL_WINDOW_H_INCLUDED

#include "SDL_Widget.h"

class SDL_Window : public SDL_Widget
{
public:
	sigslot::signal1<SDL_Widget *>		destroy;

public:
	SDL_Window()			{}
    virtual ~SDL_Window()	{
		destroy( this );
	}

	virtual const char * GetType()	{ return "SDL_Window"; }
};

#endif //!SDL_WINDOW_H_INCLUDED
