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

#ifndef SDL_SPACER_H_INCLUDED
#define SDL_SPACER_H_INCLUDED

#include "SDL_Glyph.h"

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_Spacer : public SDL_Glyph
{
public:
	SDL_Spacer( )	{}

    virtual ~SDL_Spacer()				 {}

	virtual const char * GetType()	{ return "SDL_Spacer"; }

	virtual SDL_Size GetPreferedSize()	{
		return SDL_Size( 2, 2 );
	}
	
    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc )	{}
};

#endif //!SDL_SPACER_H_INCLUDED
