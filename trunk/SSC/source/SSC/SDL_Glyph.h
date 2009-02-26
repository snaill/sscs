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

#ifndef SDL_GLYPH_H_INCLUDED
#define SDL_GLYPH_H_INCLUDED

#include "SDL_Object.h"

/// @brief 控件类的基类
class SDL_Glyph : public SDL_Object, public SDL_BoundingBox
{
public:
	SDL_Glyph() {}

	virtual ~SDL_Glyph() {}

	virtual const char * GetType() = 0;

	/// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
	virtual SDL_Size GetPreferedSize() = 0;

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen )
	{
		SDL_Rect	rcOld;
		SDL_GetClipRect( screen, &rcOld );

		SDL_Rect	rcClip = And( rcOld );
		if ( !rcClip.w || !rcClip.h )
			return;

		SDL_SetClipRect( screen, &rcClip );

		DrawWidget( screen );

		SDL_SetClipRect( screen, &rcOld );
	}

	virtual int GetLayoutProperty(){ return m_nLayoutProperty;	}
    virtual void SetLayoutProperty( int layoutProperty ){ m_nLayoutProperty = layoutProperty; }

protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen ) = 0;

protected:
	int				m_nLayoutProperty;
};

#endif // SDL_GLYPH_H_INCLUDED
