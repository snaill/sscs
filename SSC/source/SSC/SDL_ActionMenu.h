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
#include "SDL_Button.h"
#include "SDL_BoxLayout.h"
#include <SDL_ttf.h>

/// @brief ����ͼԪ����Ļ��࣬��������ļ�������
class SDL_ActionMenu : public SDL_Widget
{
public:
    SDL_ActionMenu( SDL_Button * btn1, SDL_Button * btn2 );
    virtual ~SDL_ActionMenu()		{}

	virtual const char * GetType()	{ return "SDL_ActionMenu"; }

protected:
	virtual SDL_Layout * DefaultLayout() { return new SDL_HBoxLayout(); }

    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc );
};

#endif //!SDL_ACTIONMENU_H_INCLUDED
