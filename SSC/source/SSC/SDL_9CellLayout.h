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

#ifndef SDL_9CELLLAYOUT_H_INCLUDED
#define SDL_9CELLLAYOUT_H_INCLUDED

#include "SDL_Layout.h"

class SDL_9CellLayout : public SDL_Layout
{
public:
	virtual const char * GetType()	{ return "SDL_9CellLayout"; }

	virtual SDL_Size GetPreferedSize( SDL_Container * pContainer );

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void Update( SDL_Container * pContainer, const SDL_Rect * lprc );
};

#endif // SDL_9CELLLAYOUT_H_INCLUDED
