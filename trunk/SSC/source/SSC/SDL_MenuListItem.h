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

#ifndef SDL_MENULISTITEM_H_INCLUDED
#define SDL_MENULISTITEM_H_INCLUDED

#include "SSC/SDL_Label.h"
#include "SSC/SDL_Image.h"
#include "SSC/SDL_BorderLayout.h"

/// @brief ����ͼԪ����Ļ��࣬��������ļ�������
class SDL_MenuListItem : public SDL_Layout
{
public:
	SDL_MenuListItem( SDL_Label * text, SDL_Label * remark, SDL_Image * image );
    virtual ~SDL_MenuListItem()		{}

	virtual const char * GetType()	{ return "SDL_MenuListItem"; }

	long GetParam()					{ return m_lParam;		}
	void SetParam( long lParam )	{ m_lParam = lParam;	}
	bool GetSelected()				{ return m_bSelected;		}
	void SetSelected( bool bSelected )	{ m_bSelected = bSelected;	}

protected:
	virtual SDL_Layout * DefaultLayout() { return new SDL_BorderLayout(); }

    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc );

protected:
	long			m_lParam;
	bool			m_bSelected;
};

#endif //!SDL_MENULISTITEM_H_INCLUDED