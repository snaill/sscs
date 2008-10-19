/*
 * SDL_Text.cpp
 * Copyright (C) Snaill 2008 <snaill@jeebook.com>
 *
    SDL_Text.cpp is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    main.c is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

    // ��ʼ��ͼԪ״̬
    memset( &m_aStatus, 0x00, sizeof( SDL_TextStatus ) );
    m_aStatus.type = SDL_TEXTSTATUS;
    m_aStatus.transparent = true;
    m_aStatus.quality_high = true;
    m_aStatus.size = 10;
    m_aStatus.crBack.r = 255;
    m_aStatus.crBack.g = 255;
    m_aStatus.crBack.b = 255;
}

SDL_Text::~SDL_Text(void)
{
    if ( m_pszText )
        delete[] m_pszText;
}

void SDL_Text::GetBounds( SDL_Rect * lprc )
{
	if ( !m_pszText )
	{
		lprc->x = lprc->y = lprc->w = lprc->h = 0;
	}
	else
	{
 //       lprc->x = lprc->y = 0;
//		lprc->w = m_pBitmap->w;
	//	lprc->h = m_pBitmap->h;
	}
}

void SDL_Text::Draw( SDL_Surface * screen )
{
	if ( !m_pszText )
        return;

    const char *pszFontName="C:\\Windows\\Fonts\\arial.ttf";

    //�������ļ������������С
    TTF_Font *pFont = 0;
    if((pFont = TTF_OpenFont( pszFontName, m_aStatus.size )) == NULL)
    {
        printf("call TTF_Open failed: %s\n", SDL_GetError());
        return;
    }

    //������������
    int nStyle = TTF_STYLE_NORMAL;
    if ( m_aStatus.style_blod )
        nStyle |= TTF_STYLE_BOLD;
    if ( m_aStatus.style_italic )
        nStyle |= TTF_STYLE_ITALIC;
    if ( m_aStatus.style_underline )
        nStyle |= TTF_STYLE_UNDERLINE;
    TTF_SetFontStyle( pFont, nStyle );

    //ʹ�ô򿪵�����,���ַ���"��"���ڴ�(��ʾ����)��
    SDL_Surface  *pTextSurface = 0;
    if ( m_aStatus.transparent )
    {
        if ( m_aStatus.quality_high )
            pTextSurface = TTF_RenderText_Blended( pFont, m_pszText, m_aStatus.crText );
        else
            pTextSurface = TTF_RenderText_Solid( pFont, m_pszText, m_aStatus.crText );
    }
    else
    {
        pTextSurface = TTF_RenderText_Shaded( pFont, m_pszText, m_aStatus.crText, m_aStatus.crBack );
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

        if ( m_aStatus.align_left )
            rect.x = m_rc.x;
        else if ( m_aStatus.align_right )
            rect.x = m_rc.x + m_rc.w - rect.w;
        else
            rect.x = m_rc.x + ( m_rc.w - rect.w ) / 2;

        if ( m_aStatus.align_top )
            rect.y = m_rc.y;
        else if ( m_aStatus.align_bottom )
            rect.y = m_rc.y + m_rc.h;
        else
            rect.y = m_rc.y + ( m_rc.h - rect.h ) / 2;

        //���ڴ�(��ʾ�����е�)���ݿ�������ǰ��ʾ�豸����
        SDL_BlitSurface( pTextSurface, NULL, screen, &rect );
    }

    //�ͷ��ڴ���ʾ����
    SDL_FreeSurface(pTextSurface);

    //�ر�����
    TTF_CloseFont(pFont);
}

void SDL_Text::GetTextStatus( SDL_Status * status )
{
    memcpy( &status->text, &m_aStatus, sizeof( SDL_TextStatus ) );
}

void SDL_Text::SetTextStatus( const SDL_Status * status )
{
    memcpy( &m_aStatus, &status->text, sizeof( SDL_TextStatus ) );
}
