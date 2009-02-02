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

#include "SDL_ListBoxItem.h"
#include "SDL_Screen.h"
#include <SDL_gfxPrimitives.h>

void SDL_ListBoxItem::DrawWidget( SDL_Surface * screen  )   
{
	bool bSelected = m_check;

    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_Screen::Get()->GetTheme();
	TTF_Font *pFont = theme->GetFont( SDL_Theme::Text );
	TTF_Font *pFontBig = theme->GetFont( SDL_Theme::BigText );

	SDL_Color	color = theme->GetColor( SDL_Theme::Text );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	int			x = m_pt.x;

	if ( bSelected )
		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, crSelect.r, crSelect.g, crSelect.b ) );
	else
		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, 0, 0, 0 ) );

	//
	if ( m_imgList ) {
		SDL_Size sz = m_imgList->GetImageSize();
		m_imgList->Draw( m_image, screen, x + 4, m_pt.y + ( m_sz.h - sz.h ) / 2 );
		x += 4 + sz.w + 4;
	}

	//
	SDL_Rect	rect;
	rect.x = x;
	rect.y = m_pt.y;
	rect.w = m_sz.w - 8;
	rect.h = m_sz.h * 2 / 3;
	if ( m_text )
		DrawText( screen, m_text, rect, pFontBig, color, false );

	rect.y = m_pt.y + rect.h;
	rect.h = m_sz.h - rect.h;
	if ( m_remark )
		DrawText( screen, m_remark, rect, pFont, color, true );

	//
	hlineRGBA( screen, m_pt.x + 4, m_pt.x + m_sz.w - 4, m_pt.y + m_sz.h - 1, color.r, color.g, color.b, 100 ); 

    //关闭字体
	theme->ReleaseFont( pFont );
	theme->ReleaseFont( pFontBig );
}

void SDL_ListBoxItem::DrawText( SDL_Surface * screen, char * text, SDL_Rect rect, TTF_Font * pFont, SDL_Color color, bool bTop )
{
    SDL_Surface  *pTextSurface = TTF_RenderText_Blended( pFont, text, color );

    // 绘制到屏幕缓存
    SDL_Rect  rc;
    rc.w = pTextSurface->w;
    rc.h = pTextSurface->h;

    rc.x = rect.x;
	rc.y = bTop ? rect.y : rect.y + ( rect.h - rc.h ) / 2;

    //将内存(显示环境中的)数据拷贝到当前显示设备环境
    SDL_BlitSurface( pTextSurface, 0, screen, &rc );

    //释放内存显示环境
    SDL_FreeSurface( pTextSurface );
}