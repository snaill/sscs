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

#include "SDL_ToolButton.h"
#include "SDL_Screen.h"
#include <SDL_gfxPrimitives.h>

SDL_Size SDL_ToolButton::GetPreferedSize()	
{
	SDL_Size	sz;
	sz.w = 0;
	sz.h = 0;
	if ( m_imgList )
	{
		SDL_Size	szImage = m_imgList->GetImageSize();
		sz.w = szImage.w;
		sz.h += szImage.h + 4;
	}

	if ( m_text )
	{
		int	 w, h;
		SDL_Theme * theme = SDL_Screen::Get()->GetTheme();
		TTF_Font *pFont = theme->GetFont( SDL_Theme::Text );
		TTF_SizeText( pFont, m_text, &w, &h );
		if ( sz.w < w )
			sz.w = w;
		sz.h += h;	
		theme->ReleaseFont( pFont );
	}

	sz.w += 4 + 4;
	sz.h += 4 + 4;
	return sz;
}

void SDL_ToolButton::DrawWidget( SDL_Surface * screen  )   
{
    //�������ļ������������С
	SDL_Theme * theme = SDL_Screen::Get()->GetTheme();
	TTF_Font *pFont = theme->GetFont( SDL_Theme::Text );

	SDL_Color	color = theme->GetColor( SDL_Theme::Text );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, 255, 255, 255 ) );

	//
	if ( m_imgList )
	{
		SDL_Size	szImage = m_imgList->GetImageSize();
		m_imgList->Draw( m_image, screen, m_pt.x + ( m_sz.w - 48 ) / 2, m_pt.y + 4 );
	}

	//
	SDL_Rect	rect;
	rect.x = m_pt.x;
	rect.y = m_pt.y + 4 + 52 ;
	rect.w = m_sz.w;
	rect.h = m_sz.h - 4 - 52;
	if ( m_text )
		DrawText( screen, m_text, rect, pFont, crSelect, false );

	//
	vlineRGBA( screen, m_pt.x + m_sz.w - 1, m_pt.y, m_pt.y + m_sz.h - 1, 128, 128, 128, 100 ); 

    //�ر�����
	theme->ReleaseFont( pFont );
}

void SDL_ToolButton::DrawText( SDL_Surface * screen, char * text, SDL_Rect rect, TTF_Font * pFont, SDL_Color color, bool bTop )
{
    SDL_Surface  *pTextSurface = TTF_RenderText_Blended( pFont, text, color );

    // ���Ƶ���Ļ����
    SDL_Rect  rc;
    rc.w = pTextSurface->w;
    rc.h = pTextSurface->h;

    rc.x = bTop ? rect.x : rect.x + ( rect.w - rc.w ) / 2;
	rc.y = rect.y;

    //���ڴ�(��ʾ�����е�)���ݿ�������ǰ��ʾ�豸����
    SDL_BlitSurface( pTextSurface, 0, screen, &rc );

    //�ͷ��ڴ���ʾ����
    SDL_FreeSurface( pTextSurface );
}