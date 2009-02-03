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
		SDL_Theme * theme = SDL_Screen::Get()->GetTheme();
		SDL_Font *pFont = theme->GetFont( SDL_Theme::Text );
		SDL_Size	szFont = pFont->GetTextSize( m_text );
		if ( sz.w < szFont.w )
			sz.w = szFont.w;
		sz.h += szFont.h;	
		pFont->Release();
	}

	sz.w += 4 + 4;
	sz.h += 4 + 4;
	return sz;
}

void SDL_ToolButton::DrawWidget( SDL_Surface * screen  )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_Screen::Get()->GetTheme();
	SDL_Font *pFont = theme->GetFont( SDL_Theme::Text );

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
		pFont->DrawText( screen, m_text, rect, crSelect );
	//	DrawText( screen, m_text, rect, pFont, crSelect, false );

	//
	vlineRGBA( screen, m_pt.x + m_sz.w - 1, m_pt.y + 4, m_pt.y + m_sz.h - 4, 128, 128, 128, 100 ); 

    //关闭字体
	pFont->Release();
}
