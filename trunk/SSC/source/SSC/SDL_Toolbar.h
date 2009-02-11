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
// 基本属性
public:
	SDL_Toolbar()		{
		m_pLayout = new SDL_FlowLayout();
	}

	virtual ~SDL_Toolbar()	{}

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

	virtual bool Add( SDL_Widget * g )
    {
        assert( g );
		g->click.connect( this, &SDL_Toolbar::OnButtonClicked );
		return SDL_Widget::Add( g );
    }

protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
    virtual void DrawWidget( SDL_Surface * screen ) { 
		SDL_Rect	rc = GetBounds();
		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, 255, 255, 255 ) );
	}

	void OnButtonClicked( SDL_Widget * button ) {
		click( button );
	}
};

#endif // SDL_TOOLBAR_H_INCLUDED
