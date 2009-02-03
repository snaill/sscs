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

SDL_Size SDL_ListBoxItem::GetPreferedSize()	
{	
	SDL_Size	sz( 0, 0 ), szImage( 0, 0 ), szFont( 0, 0 );
	sz.w = 0;
	sz.h = 0;
	if ( m_imgList )
		szImage = m_imgList->GetImageSize();

	if ( m_text )
	{
		SDL_Theme * theme = SDL_Screen::Get()->GetTheme();
		SDL_Font *pFontBig = theme->GetFont( SDL_Theme::BigText );
		szFont = pFontBig->GetTextSize( m_text );
		pFontBig->Release();

		if ( m_remark )
		{
			SDL_Font *pFont = theme->GetFont( SDL_Theme::Text );
			SDL_Size szTemp = pFont->GetTextSize( m_remark );
			if ( szFont.w < szTemp.w )
				szFont.w = szTemp.w;
			szFont.h += 4 + szTemp.h;
			pFont->Release();
		}
	}

	sz.w += 4 + szImage.w + szFont.w + 4;
	sz.h = 4 + max( szImage.h, szFont.h ) + 4;
	return sz;
}

void SDL_ListBoxItem::DrawWidget( SDL_Surface * screen  )   
{
    //�������ļ������������С
	SDL_Theme * theme = SDL_Screen::Get()->GetTheme();
	SDL_Font *pFont = theme->GetFont( SDL_Theme::Text );
	SDL_Font *pFontBig = theme->GetFont( SDL_Theme::BigText );

	SDL_Color	color = theme->GetColor( SDL_Theme::Text );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	int			x = m_pt.x;

	if ( m_check )
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
	if ( m_text )
	{
		SDL_Rect	rect;
		if ( m_remark )
		{
			rect.x = x;
			rect.y = m_pt.y + 4;
			rect.w = m_sz.w;
			rect.h = m_sz.h;
			pFontBig->DrawText( screen, m_text, rect, color, -1, -1 );

			rect.y += pFontBig->GetTextSize( m_text ).h + 4;
			pFont->DrawText( screen, m_remark, rect, color, -1, -1 );
		}
		else
		{
			rect.x = x;
			rect.y = m_pt.y;
			rect.w = m_pt.x + m_sz.w - x;
			rect.h = m_sz.h;
			pFontBig->DrawText( screen, m_text, rect, color, -1, 0 );
		}
	}

	//
	hlineRGBA( screen, m_pt.x + 4, m_pt.x + m_sz.w - 4, m_pt.y + m_sz.h - 1, color.r, color.g, color.b, 100 ); 

    //�ر�����
	pFont->Release();
	pFontBig->Release();
}