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

#include "SDL_Text.h"
#include "SDL_Setting.h"

SDL_Text::SDL_Text( const char * text )
{
    // ��ʼ��ͼԪ�ı�
    int len = strlen( text );
    m_pszText = new char[ len + 1 ];
    strcpy( m_pszText, text );
    m_pszText[ len ] = '\0';
}

SDL_Text::~SDL_Text(void)
{
    if ( m_pszText )
        delete[] m_pszText;
}

void SDL_Text::GetMinSize( int * w, int * h )
{
	*w = *h = 0;

	if ( m_pszText )
	{
	    SDL_DC * pDC = SDL_Setting::Get()->GetDC();

        TTF_Font *pFont = pDC->GetFont();

        //
        TTF_SizeText( pFont, m_pszText, w, h );

        //�ر�����
        TTF_CloseFont(pFont);
	}
}

void SDL_Text::Draw( SDL_Surface * screen )
{
	if ( !m_pszText )
        return;

    //�������ļ������������С
    SDL_DC * pDC = SDL_Setting::Get()->GetDC();
    TTF_Font *pFont = pDC->GetFont();

    //ʹ�ô򿪵�����,���ַ���"��"���ڴ�(��ʾ����)��
    SDL_Surface  *pTextSurface = 0;
    Uint32 uStyle = pDC->GetTextStyle();
    if ( uStyle & SDL_DC::TEXT_STYLE_TRANSPARENT )
    {
        if ( uStyle & SDL_DC::TEXT_STYLE_HIGHQUALITY )
            pTextSurface = TTF_RenderText_Blended( pFont, m_pszText, pDC->GetTextColor() );
        else
            pTextSurface = TTF_RenderText_Solid( pFont, m_pszText, pDC->GetTextColor() );
    }
    else
    {
        pTextSurface = TTF_RenderText_Shaded( pFont, m_pszText, pDC->GetTextColor(), pDC->GetBkColor() );
    }

    // ���Ƶ���Ļ����
    if ( !pTextSurface )
    {
        printf("call TTF_RenderUTF8_Solid failed %s\n", SDL_GetError());
    }
    else
    {
        SDL_Rect  rect;
        rect.w = pTextSurface->w;
        rect.h = pTextSurface->h;

        Uint32 uAlign = pDC->GetTextAlign();
        if ( uAlign & SDL_DC::TEXT_ALIGN_LEFT )
            rect.x = m_rc.x;
        else if ( uAlign & SDL_DC::TEXT_ALIGN_RIGHT )
            rect.x = m_rc.x + m_rc.w - rect.w;
        else
            rect.x = m_rc.x + ( m_rc.w - rect.w ) / 2;

        if ( uAlign & SDL_DC::TEXT_ALIGN_TOP )
            rect.y = m_rc.y;
        else if ( uAlign & SDL_DC::TEXT_ALIGN_BOTTOM )
            rect.y = m_rc.y + m_rc.h;
        else
            rect.y = m_rc.y + ( m_rc.h - rect.h ) / 2;

        //���ڴ�(��ʾ�����е�)���ݿ�������ǰ��ʾ�豸����
        SDL_Rect    rcOldClip;
        SDL_GetClipRect( screen, &rcOldClip );
        SDL_SetClipRect( screen, &m_rc );
        SDL_BlitSurface( pTextSurface, NULL, screen, &rect );
	    SDL_SetClipRect( screen, &rcOldClip );
    }

    //�ͷ��ڴ���ʾ����
    SDL_FreeSurface(pTextSurface);

    //�ر�����
    TTF_CloseFont(pFont);
}
