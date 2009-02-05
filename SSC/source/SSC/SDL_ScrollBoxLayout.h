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

#include "SDL_Glyph.h"

/// @brief 所有界面布局的基类，实现固定布局
class SDL_ScrollBoxLayout : public SDL_Layout
{
public:
	SDL_ScrollBoxLayout()            { 
		m_top = m_bottom = 0;
	}

    virtual ~SDL_ScrollBoxLayout()	  { }

	virtual const char * GetType()				{ return "scrollboxlayout"; }

	virtual SDL_Size GetPreferedSize( SDL_Container * pContainer )	{
		//!!!!!
		return SDL_Size( 0, 0 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void Update( SDL_Container * pContainer, const SDL_Rect * lprc ) {
		//
		SDL_Rect	rcItem;
		rcItem.x = lprc->x;
		rcItem.y = lprc->y;
		rcItem.w = lprc->w;
		for ( size_t i = 0; i < pContainer->GetCount(); i ++ )
		{
			SDL_Glyph * pItem = pContainer->GetItem(i);
			if ( !pItem->IsShow() )
				continue;

			SDL_Size	size = pItem->GetPreferedSize();
			rcItem.h = size.h;
			pItem->SetBounds( &rcItem );

			rcItem.y += rcItem.h;
		}

		//
		SDL_Layout::SetBounds( lprc );
    }

public:
	void Scroll( int nValue, SDL_Container * pContainer )	{
		for ( size_t i = 0; i < pContainer->GetCount(); i ++ )
		{
			SDL_Rect	rc = pContainer->GetItem(i)->GetBounds();
			rc.y += nValue;
			pContainer->GetItem(i)->SetBounds(&rc);
		}
	}

	int GetTopIndex( SDL_Container * pContainer )	{
		for ( size_t i = 0; i < pContainer->GetCount(); i ++ )
		{
			SDL_Rect	rc = pContainer->GetItem(i)->GetBounds();
			if ( rc.y + rc.h > m_y )
				return i;
		}	

		return -1;
	}

	int GetBottomIndex( SDL_Container * pContainer )	{
		for ( int i = pContainer->GetCount() - 1; i >= 0 ; i -- )
		{
			SDL_Rect	rc = pContainer->GetItem(i)->GetBounds();
			if ( rc.y < m_y + m_h )
				return i;
		}		

		return -1;
	}	
//
//	void ShowItem( int index, SDL_Container * pContainer, const SDL_Rect * lprc  )	{
//		if ( index > m_top && index < m_bottom )
//			return;
//		
//		if ( index <= m_top )
//			SetTop( index, pContainer, lprc );
//
//		if ( index >= m_bottom )
//			SetBottom( index, pContainer, lprc );
//	}
//
//protected:
//	Uint16	GetTop()			{ return m_top; }
//	void	SetTop( Uint16 top, SDL_Container * pContainer, const SDL_Rect * lprc )	{ 
//		if ( m_top == top || top >= pContainer->GetCount() )
//			return;
//
//		SDL_Rect	rect;
//		int			h = 0;
//		for ( int i = top; i < pContainer->GetCount() && h < lprc->h; i++ )
//		{
//			SDL_Size	size = pContainer->GetItem(i)->GetPreferedSize();
//			rect.x = 0;
//			rect.w = lprc->w;
//			rect.y = lprc->y + h;
//			pContainer->GetItem(i)->SetBounds( &rect );
//			h += rect.h;
//			m_bottom = i;
//		}
//
//		m_top = top;
//	}
//
//	Uint16	GetBottom()					{ return m_bottom; }
//	void	SetBottom(Uint16 bottom, SDL_Container * pContainer, const SDL_Rect * lprc )	{ 
//		if ( m_bottom == bottom || bottom >= pContainer->GetCount() )
//			return;
//
//		SDL_Rect	rect;
//		int			h = lprc->h;
//		for ( int i = bottom; i >= 0 && h > 0; i-- )
//		{
//			SDL_Size	size = pContainer->GetItem(i)->GetPreferedSize();
//			rect.x = 0;
//			rect.w = lprc->w;
//			h -= rect.h;
//			rect.y = lprc->y + h;
//			pContainer->GetItem(i)->SetBounds( &rect );
//			m_top = i;
//		}
//
//		if ( h > 0 )
//			SetTop( 0, pContainer, lprc );
//
//		m_bottom = bottom;
//	}

protected:
	Uint16	m_top, m_bottom;

};

#endif // SDL_SCROLLBOXLAYOUT_H_INCLUDED
