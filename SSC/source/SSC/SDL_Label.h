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

#ifndef SDL_LABEL_H_INCLUDED
#define SDL_LABEL_H_INCLUDED

#include "SDL_Widget.h"
#include "SDL_Glyph.h"
#include "SDL_Theme.h"
#include <SDL_ttf.h>

/// @brief 
class SDL_Label : public SDL_Glyph
{
public:
    SDL_Label( const wchar_t * text, int nFont = SDL_Theme::Text, 
			  int nColor = SDL_Theme::Text, int align = 0, int valign = 0 );

    virtual ~SDL_Label()				 {}

	virtual const char * GetType()	{ return "SDL_Label"; }

	virtual SDL_Size GetPreferedSize();

	void SetFont( int nFont )		{ m_nFont = nFont;		}
	void SetColor( int nColor )		{ m_nColor = nColor;	}
	void SetAlign( int nAlign )		{ m_align = nAlign;		}
	void SetVAlign( int nvAlign )	{ m_valign = nvAlign;	}

protected:
    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen );

protected:
	std::wstring		m_text;
	int 				m_nFont;
	int 				m_nColor;
	int					m_align;
	int 				m_valign;
};

#endif //!SDL_LABEL_H_INCLUDED
