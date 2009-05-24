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

#include "SSC/SDL_ListItem.h"

/// @brief ����ͼԪ����Ļ��࣬��������ļ�������
class SDL_MenuListItem : public SDL_ListItem
{
public:
	SDL_MenuListItem( SDL_Label * text );
    virtual ~SDL_MenuListItem()		{}

	virtual const char * GetType()	{ return "SDL_MenuListItem"; }

	virtual SDL_Size GetPreferedSize();

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void SetBounds( const SDL_Rect * lprc );

protected:
   /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc );

};

#endif //!SDL_MENULISTITEM_H_INCLUDED
