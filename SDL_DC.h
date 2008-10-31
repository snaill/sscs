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

#ifndef SDL_DC_H_INCLUDED
#define SDL_DC_H_INCLUDED

#include <SDL_ttf.h>

class SDL_DC
{
public:
    enum {
        TEXT_ALIGN_LEFT         = 0x00000001,
        TEXT_ALIGN_RIGHT        = 0x00000002,
        TEXT_ALIGN_CENTER       = 0x00000004,
        TEXT_ALIGN_TOP          = 0x00000008,
        TEXT_ALIGN_BOTTOM       = 0x00000010,
        TEXT_ALIGN_VCENTER      = 0x00000020,

        TEXT_STYLE_BLOD         = 0x00000100,
        TEXT_STYLE_ITALIC       = 0x00000200,
        TEXT_STYLE_UNDERLINE    = 0x00000400,
        TEXT_STYLE_HIGHQUALITY  = 0x00000800,
        TEXT_STYLE_TRANSPARENT  = 0x00001000
    };
public:
    SDL_DC();
    ~SDL_DC();

    TTF_Font * GetFont();

    void ReleaseFont( TTF_Font * pFont );

    Uint32 GetTextAlign();

    Uint32 SetTextAlign( Uint32 uAlign );

    Uint32 GetTextStyle();
    Uint32 SetTextStyle( Uint32 uStyle );

    SDL_Color GetBkColor();
    SDL_Color SetBkColor( SDL_Color cr );

    SDL_Color GetTextColor();
    SDL_Color SetTextColor( SDL_Color cr );

    const char * GetFontName();

    Uint32 GetFontSize();
    Uint32 SetFontSize( Uint32 uSize );
protected:
    Uint32      m_uTextStatus;
    Uint32      m_uTextSize;    /* 字体大小 */

    SDL_Color   m_crBack;       /* 背景色 */
    SDL_Color   m_crText;       /* 前景色 */
};

#endif // SDL_DC_H_INCLUDED
