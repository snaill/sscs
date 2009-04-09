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

#ifndef SDL_SWITCHUI_H_INCLUDED
#define SDL_SWITCHUI_H_INCLUDED

#include "SDL_Glyph.h"
#include <SDL.h>

///
typedef void (* SwitchUIFunc)( long lParam );

/// 
class SDL_SwitchUI
{
public:
	enum {
		toLeft,
		toRight
	};

// 基本属性
public:
	SDL_SwitchUI()		  	{ }
    virtual ~SDL_SwitchUI()	{ }

public:
	void Switch( int nMode, SDL_Glyph * gOld, SDL_Glyph * gNew );
	void Switch( int nMode, SDL_Glyph * g, SwitchUIFunc f, long lParam );

// 方法
protected:
	void Move( SDL_Surface * screen, SDL_Surface * oldSurface, SDL_Surface * newSurface, int nMode, const SDL_Rect * lprc );
};

#endif // SDL_SWITCHUI_H_INCLUDED
