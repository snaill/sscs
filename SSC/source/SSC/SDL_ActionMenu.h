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

#ifndef SDL_ACTIONMENU_H_INCLUDED
#define SDL_ACTIONMENU_H_INCLUDED

#include "SDL_Widget.h"
#include "SDL_Image.h"
#include "SDL_Label.h"
#include "SDL_ToolButton.h"
#include "SDL_BoxLayout.h"
#include <SDL_ttf.h>

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_ActionMenu : public SDL_Widget
{
public:
    SDL_ActionMenu( SDL_ToolButton * btn1, SDL_ToolButton * btn2 ) {
		if ( !btn1 )
			btn1 = new SDL_ToolButton( 0, 0, 0 );
		if ( !btn2 )
			btn2 = new SDL_ToolButton( 0, 0, 0 );

		Add( btn1 );
		Add( btn2 );

		SetLayout( new SDL_HBoxLayout() );
    }

    virtual ~SDL_ActionMenu()		{}

	virtual const char * GetType()	{ return "SDL_ActionMenu"; }

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen );
};

#endif //!SDL_ACTIONMENU_H_INCLUDED
