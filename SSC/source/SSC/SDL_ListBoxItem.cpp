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
#include "SDL_MainFrame.h"
#include <SDL_gfxPrimitives.h>

//SDL_Size SDL_ListBoxItem::GetPreferedSize()	
//{	
//	SDL_Size	sz( 0, 0 ), szImage( 0, 0 ), szFont( 0, 0 );
//	sz.w = 0;
//	sz.h = 0;
//	if ( m_imgList )
//		szImage = m_imgList->GetImageSize();
//
//	if ( m_text.size() > 0 )
//	{
//		SDL_Theme * theme = SDL_MainFrame::Get()->GetTheme();
//		SDL_Font *pFontBig = theme->GetFont( SDL_Theme::BigText );
//		szFont = pFontBig->GetTextSize( m_text.c_str() );
//		pFontBig->Release();
//
//		if ( m_remark.size() > 0 )
//		{
//			SDL_Font *pFont = theme->GetFont( SDL_Theme::Text );
//			SDL_Size szTemp = pFont->GetTextSize( m_remark.c_str() );
//			if ( szFont.w < szTemp.w )
//				szFont.w = szTemp.w;
//			szFont.h += 4 + szTemp.h;
//			pFont->Release();
//		}
//	}
//
//	sz.w += 4 + szImage.w + szFont.w + 4;
//	sz.h = 4 + max( szImage.h, szFont.h ) + 4;
//	return sz;
//}

void SDL_ListBoxItem::DrawWidget( SDL_Surface * screen  )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_MainFrame::Get()->GetTheme();

	SDL_Color	color = theme->GetColor( SDL_Theme::Text );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	int			x = m_pt.x;

//	if ( GetSelected() )
//		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, crSelect.r, crSelect.g, crSelect.b ) );
//	else
//		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, 0, 0, 0 ) );

	//
	SDL_Container::DrawWidget( screen );

	hlineRGBA( screen, m_pt.x + 4, m_pt.x + m_sz.w - 4, m_pt.y + m_sz.h - 1, color.r, color.g, color.b, 100 ); 
}
