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

#ifndef SDL_LISTBOXITEM_H_INCLUDED
#define SDL_LISTBOXITEM_H_INCLUDED

#include "SDL_Container.h"
#include "SDL_Label.h"
#include "SDL_Image.h"
#include "SDL_BorderLayout.h"

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_ListBoxItem : public SDL_Container
{
public:
	SDL_ListBoxItem( SDL_Label * text, SDL_Label * remark, SDL_Image * image );
    virtual ~SDL_ListBoxItem()		{}

	virtual const char * GetType()	{ return "SDL_ListBoxItem"; }

	long GetParam()					{ return m_lParam;		}
	void SetParam( long lParam )	{ m_lParam = lParam;	}
	bool GetSelected()				{ return m_bSelected;		}
	void SetSelected( bool bSelected )	{ m_bSelected = bSelected;	}

protected:
	virtual SDL_Layout * DefaultLayout() { return new SDL_BorderLayout(); }

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen );

protected:
	long			m_lParam;
	bool			m_bSelected;
};

#endif //!SDL_LISTBOXITEM_H_INCLUDED
