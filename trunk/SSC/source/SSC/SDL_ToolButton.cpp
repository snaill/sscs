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
    //�������ļ������������С
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

	//�ر�����
	pFont->Release();

	//
	if ( m_bHover )
	{
		SDL_Rect	rc2;
		rc2.x = m_pt.x + 2;
		rc2.y = m_pt.y + 2;
		rc2.w = m_sz.w - 4;
		rc2.h = m_sz.h - 4;

		SDL_Color	cr1, cr2;
		cr1.r = cr1.g = cr1.b = 0;
		cr2.r = cr2.g = cr2.b = 192;

		if ( m_bMouseButtonDown )
            Draw3DRect( screen, rc2, cr1, cr2);
		else 
            Draw3DRect( screen, rc2, cr2, cr1);
	}
}
