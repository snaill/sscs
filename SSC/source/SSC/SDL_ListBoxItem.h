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

/// @brief ����ͼԪ����Ļ��࣬��������ļ�������
class SDL_ListBoxItem : public SDL_Widget
{
public:
    SDL_ListBoxItem( const wchar_t * text, const wchar_t * remark, SDL_ImageList * imgList, int iImage ) {
		if ( text )
			m_text = text;
		if ( remark )
			m_remark = remark;
		m_imgList = imgList;
		m_image = iImage;
    }

    virtual ~SDL_ListBoxItem()					{
	    if ( m_imgList )
			m_imgList->Release();
	}

	virtual const char * GetType()	{ return "listboxitem"; }

	virtual SDL_Size GetPreferedSize();

    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
	virtual void DrawWidget( SDL_Surface * screen );

	virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	{
		if ( !IsIn( button->x, button->y ) )
			return false;

		click( this );
		return true;
	}

public:

protected:
	std::wstring		m_text;
	std::wstring		m_remark;
	int					m_image;
	SDL_ImageList *		m_imgList;
};

#endif //!SDL_LISTBOXITEM_H_INCLUDED
