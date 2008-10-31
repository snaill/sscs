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

#include "SDL_DC.h"

SDL_DC::SDL_DC()
{
    TTF_Init();

    m_uTextStatus = TEXT_ALIGN_CENTER | TEXT_ALIGN_VCENTER
            | TEXT_STYLE_TRANSPARENT | TEXT_STYLE_HIGHQUALITY;
    m_uTextSize = 10;
    m_crBack.r = m_crBack.g = m_crBack.b = 255;
    m_crText.r = m_crText.g = m_crText.b = 0;
}

SDL_DC::~SDL_DC()
{
    TTF_Quit();
}

TTF_Font * SDL_DC::GetFont()
{
    TTF_Font *pFont = 0;
    if((pFont = TTF_OpenFont( GetFontName(), GetFontSize() )) == NULL)
    {
        printf("call TTF_Open failed: %s\n", SDL_GetError());
        return 0;
    }

    //…Ë÷√◊÷ÃÂ Ù–‘
    int nStyle = TTF_STYLE_NORMAL;
    if ( m_uTextStatus & TEXT_STYLE_BLOD )
        nStyle |= TTF_STYLE_BOLD;
    if ( m_uTextStatus & TEXT_STYLE_ITALIC )
        nStyle |= TTF_STYLE_ITALIC;
    if ( m_uTextStatus & TEXT_STYLE_UNDERLINE )
        nStyle |= TTF_STYLE_UNDERLINE;
    TTF_SetFontStyle( pFont, nStyle );

    return pFont;
}

void SDL_DC::ReleaseFont( TTF_Font * pFont )
{
    TTF_CloseFont(pFont);
}

Uint32 SDL_DC::GetTextAlign()
{
    return m_uTextStatus & 0x000000FF;
}

Uint32 SDL_DC::SetTextAlign( Uint32 uAlign )
{
    Uint32 old = m_uTextStatus & 0x000000FF;
    m_uTextStatus = ( m_uTextStatus & 0xFFFFFF00 ) | ( uAlign & 0x000000FF );
    return old;
}

Uint32 SDL_DC::GetTextStyle()
{
    return m_uTextStatus & 0x0000FF00;
}

Uint32 SDL_DC::SetTextStyle( Uint32 uStyle )
{
    Uint32 old = m_uTextStatus & 0x0000FF00;
    m_uTextStatus = ( m_uTextStatus & 0xFFFF00FF ) | ( uStyle & 0x0000FF00 );
    return old;
}

SDL_Color SDL_DC::GetBkColor()
{
    return m_crBack;
}

SDL_Color SDL_DC::SetBkColor( SDL_Color cr )
{
    SDL_Color old = m_crBack;
    m_crBack = cr;
    return old;
}

SDL_Color SDL_DC::GetTextColor()
{
    return m_crText;
}

SDL_Color SDL_DC::SetTextColor( SDL_Color cr )
{
    SDL_Color old = m_crText;
    m_crText = cr;
    return old;
}

const char * SDL_DC::GetFontName()
{
    return "C:\\Windows\\Fonts\\arial.ttf";
}

Uint32 SDL_DC::GetFontSize()
{
    return m_uTextSize;
}

Uint32 SDL_DC::SetFontSize( Uint32 uSize )
{
    Uint32 old = m_uTextSize;
    m_uTextSize = uSize;
    return old;
}
