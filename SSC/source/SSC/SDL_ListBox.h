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

#ifndef SDL_LISTBOX_H_INCLUDED
#define SDL_LISTBOX_H_INCLUDED

#include "SDL_Widget.h"
#include "SDL_ListBoxItem.h"
#include "SDL_ScrollBoxLayout.h"

/// @brief 控件类的基类
class SDL_ListBox : public SDL_Widget
{
public:
	sigslot::signal1<SDL_ListBoxItem *>		select;

// 基本属性
public:
	SDL_ListBox();
	virtual ~SDL_ListBox();

	virtual const char * GetType()				{ return "SDL_ListBox"; }

	virtual SDL_Size GetPreferedSize();

protected:
	inline SDL_ScrollBoxLayout * GetCurrentLayout()	{ return (SDL_ScrollBoxLayout *)GetLayout(); }

	virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw );
;	virtual bool OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw );

    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
    virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc );
	void SelectItem( SDL_Glyph * g );

protected:
	SDL_Glyph *	m_curItem;
};

#endif // SDL_LISTBOX_H_INCLUDED
