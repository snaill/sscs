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

// 方法
public:
	void SetOld( SDL_Glyph * g );
	void SetNew( SDL_Glyph * g );
	void Switch( int nMode );

protected:
	void ToLeft( SDL_Surface * screen, const SDL_Rect * lprc, SDL_Surface * oldSurface, SDL_Surface * newSurface );
	void ToRight( SDL_Surface * screen, const SDL_Rect * lprc, SDL_Surface * oldSurface, SDL_Surface * newSurface );

protected:
	SDL_Rect		m_rcClip;
	SDL_Surface *	m_old;
	SDL_Surface *	m_new;
};

#endif // SDL_SWITCHUI_H_INCLUDED
