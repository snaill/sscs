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

#ifndef SDL_FLOWLAYOUT_H_INCLUDED
#define SDL_FLOWLAYOUT_H_INCLUDED

#include "SDL_Layout.h"

/// @brief ���н��沼�ֵĻ��࣬ʵ�̶ֹ�����
class SDL_FlowLayout : public SDL_Layout
{
public:
	SDL_FlowLayout()            {}

    virtual ~SDL_FlowLayout()	  { }

	virtual const char * GetType()				{ return "flowlayout"; }

	virtual SDL_Size GetPreferedSize( SDL_Container * pContainer )	{
		//!!!!!
		return SDL_Size( 0, 0 );
	}

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void Update( SDL_Container * pContainer, const SDL_Rect * lprc ) {
		int x = lprc->x, y = lprc->y, w = lprc->w, h = lprc->h;
		SDL_Rect	rcItem;

		Iterator * pos = pContainer->GetIterator();
		for ( pos->First(); !pos->IsDone(); pos->Next() )
		{
			SDL_Glyph * pItem = pos->GetCurrentItem();

			SDL_Size size = pItem->GetPreferedSize();
			rcItem.x = x;
			rcItem.y = y;
			rcItem.w = size.w;
			rcItem.h = size.h;
			pItem->SetBounds( &rcItem );
			x += size.w;
		}
		pos->Release();
    }
};

#endif // SDL_FLOWLAYOUT_H_INCLUDED