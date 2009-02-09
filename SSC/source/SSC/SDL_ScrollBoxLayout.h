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

#ifndef SDL_SCROLLBOXLAYOUT_H_INCLUDED
#define SDL_SCROLLBOXLAYOUT_H_INCLUDED

#include "SDL_Widget.h"

/// @brief 所有界面布局的基类，实现固定布局
class SDL_ScrollBoxLayout : public SDL_Layout
{
public:
	SDL_ScrollBoxLayout()            { 
		m_top = m_bottom = 0;
	}

    virtual ~SDL_ScrollBoxLayout()	  { }

	virtual const char * GetType()				{ return "scrollboxlayout"; }

	virtual SDL_Size GetPreferedSize( SDL_Widget * pContainer )	{
		//!!!!!
		return SDL_Size( 0, 0 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void Update( SDL_Widget * pContainer, const SDL_Rect * lprc ) {
		//
		SDL_Rect	rcItem;
		rcItem.x = lprc->x;
		rcItem.y = lprc->y;
		rcItem.w = lprc->w;

		Iterator * pos = pContainer->GetIterator();
		for ( pos->First(); !pos->IsDone(); pos->Next() )
		{
			SDL_Widget * pItem = pos->GetCurrentItem();
			SDL_Size	size = pItem->GetPreferedSize();
			rcItem.h = size.h;
			pItem->SetBounds( &rcItem );

			rcItem.y += rcItem.h;
		}
		pos->Release();

		//
		SDL_Layout::SetBounds( lprc );
    }

public:
	void Scroll( int nValue, SDL_Widget * pContainer )	{
		Iterator * pos = pContainer->GetIterator();
		for ( pos->First(); !pos->IsDone(); pos->Next() )
		{
			SDL_Widget * pItem = pos->GetCurrentItem();
			SDL_Rect	rc = pItem->GetBounds();
			rc.y += nValue;
			pItem->SetBounds(&rc);
		}
		pos->Release();
	}

	SDL_Widget * GetTop( SDL_Widget * pContainer )	{
		Iterator * pos = pContainer->GetIterator();
		for ( pos->First(); !pos->IsDone(); pos->Next() )
		{
			SDL_Widget * pItem = pos->GetCurrentItem();
			SDL_Rect	rc = pItem->GetBounds();
			if ( rc.y + rc.h > m_y )
				return pItem;
		}	
		pos->Release();

		return 0;
	}

	SDL_Widget * GetBottom( SDL_Widget * pContainer )	{
		Iterator * pos = pContainer->GetIterator(true);
		for ( pos->First(); !pos->IsDone(); pos->Next() )
		{
			SDL_Widget * pItem = pos->GetCurrentItem();
			SDL_Rect	rc = pItem->GetBounds();
			if ( rc.y < m_y + m_h )
				return pItem;
		}		
		pos->Release();
		return 0;
	}	

protected:
	Uint16	m_top, m_bottom;

};

#endif // SDL_SCROLLBOXLAYOUT_H_INCLUDED
