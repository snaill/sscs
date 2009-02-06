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

#ifndef SDL_TOOLBAR_H_INCLUDED
#define SDL_TOOLBAR_H_INCLUDED

#include "SDL_Widget.h"
#include "SDL_ToolButton.h"
#include "SDL_FlowLayout.h"

/// @brief 控件类的基类
class SDL_Toolbar : public SDL_Widget
{
public:
	sigslot::signal1<SDL_ToolButton *>		click;

// 基本属性
public:
	SDL_Toolbar()		{
		m_pLayout = new SDL_FlowLayout();
	}

	virtual ~SDL_Toolbar()	{
		if ( m_imgList )
			m_imgList->Release();
	}

	virtual const char * GetType()				{ return "toolbar"; }

	virtual SDL_Size GetPreferedSize()	{
		SDL_Size	sz( 0, 0 );
		
		Iterator * pos = GetIterator(true);
		for ( pos->First(); !pos->IsDone(); pos->Next() )
		{
			SDL_Size size = pos->GetCurrentItem()->GetPreferedSize();
			sz.w += size.w;
			if ( sz.h < size.h )
				sz.h = size.h;
		}
		pos->Release();

		return sz;
	}
public:
	SDL_ToolButton * AddItem( const wchar_t * text, int iImage )
	{
		SDL_ToolButton * pItem = new SDL_ToolButton( text, iImage );
		pItem->SetImageList( m_imgList );
		pItem->click.connect( this, &SDL_Toolbar::OnButtonClicked );

		Add( pItem );
		return pItem;
	}

	void SetImageList( SDL_ImageList * imgList )	{
		m_imgList = imgList;
	}

protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
    virtual void DrawWidget( SDL_Surface * screen ) { 
		SDL_Rect	rc = GetBounds();
		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, 255, 255, 255 ) );
	}

	void OnButtonClicked( SDL_ToolButton * button ) {
		click( button );
	}

protected:
	SDL_ImageList *		m_imgList;	
};

#endif // SDL_TOOLBAR_H_INCLUDED
