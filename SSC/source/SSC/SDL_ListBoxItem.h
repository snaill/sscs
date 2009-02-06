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

#include "SDL_Widget.h"
#include "SDL_ImageList.h"
#include <SDL_ttf.h>

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_ListBoxItem : public SDL_Widget
{
public:
	sigslot::signal1<SDL_ListBoxItem *>		select;

public:
    SDL_ListBoxItem( const wchar_t * text, const wchar_t * remark, int iImage ) {
		int len = wcslen( text );
		m_text = new wchar_t[ len + 1 ];
		wcscpy( m_text, text );
		m_text[ len ] = '\0';

		len = wcslen( remark );
		m_remark = new wchar_t[ len + 1 ];
		wcscpy( m_remark, remark );
		m_remark[ len ] = '\0';

		m_check = false;
		m_imgList = 0;
		m_image = iImage;
    }

    virtual ~SDL_ListBoxItem()					{
	    if ( m_text )
			delete[] m_text;

		if ( m_remark )
			delete[] m_remark;
	}

	virtual const char * GetType()	{ return "listboxitem"; }

	virtual SDL_Size GetPreferedSize();

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen );

	virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	{
		if ( !IsIn( button->x, button->y ) )
			return false;

		select( this );
		return true;
	}

public:
	bool GetCheck()				{ return m_check;	}
	void SetCheck( bool check ) { m_check = check;	}
	void SetImageList( SDL_ImageList * imgList )	{
		m_imgList = imgList;
	}

protected:
	wchar_t *				m_text;
	wchar_t *				m_remark;
	int					m_image;
	bool				m_check;
	SDL_ImageList *		m_imgList;
};

#endif //!SDL_LISTBOXITEM_H_INCLUDED
