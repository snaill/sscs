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

#ifndef SDL_TOOLBAR_H_INCLUDED
#define SDL_TOOLBAR_H_INCLUDED

#include "SDL_Widget.h"

/// @brief 控件类的基类
class SDL_Toolbar : public SDL_Widget
{
// 基本属性
public:
	SDL_Toolbar();
	virtual ~SDL_Toolbar()	{}
	virtual const char * GetType()				{ return "SDL_Toolbar"; }

	virtual SDL_Size GetPreferedSize();

protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
    virtual void DrawWidget( SDL_Surface * screen );
};

#endif // SDL_TOOLBAR_H_INCLUDED
