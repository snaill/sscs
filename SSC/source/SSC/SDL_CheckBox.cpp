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

#include "SDL_CheckBox.h"
#include "SDL_WindowManager.h"
#include <SDL_gfxPrimitives.h>

SDL_CheckBox::SDL_CheckBox( const wchar_t * text ) 
{
	if ( text )
		m_text = text;
}

SDL_Size SDL_CheckBox::GetPreferedSize()	
{	
	SDL_Size	sz( 0, 0 ), szImage( 13, 13 ), szFont( 0, 0 );

	if ( m_text.size() > 0 )
	{
		SDL_Theme * theme = SDL_WindowManager::Get()->GetTheme();
		SDL_Font *pFontBig = theme->GetFont( SDL_FONTSIZE_BIG );
		szFont = pFontBig->GetTextSize( m_text.c_str() );
		pFontBig->Release();
	}

	sz.w += 4 + szImage.w + 4 + szFont.w + 4;
	sz.h = 4 + max( szImage.h, szFont.h ) + 4;
	return sz;
}

void SDL_CheckBox::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_WindowManager::Get()->GetTheme();

	SDL_FillRect( screen, ( SDL_Rect * )lprc, SDL_MapRGB( screen->format, 0, 0, 0 ) );

	//
	int			x = m_pt.x;
	int			a = GetHover() || GetCheck() ? 255 : 100;

	rectangleRGBA( screen, x + 4, lprc->y + ( lprc->h - 13) / 2, x + 4 + 13, lprc->y + ( lprc->h - 13) / 2 + 13, 255, 255, 255, a ); 
	if ( GetCheck() ) {
		lineRGBA( screen, x + 4 + 4, lprc->y + ( lprc->h - 13) / 2 + 4, x + 4 + 13 - 4, lprc->y + ( lprc->h - 13) / 2 + 13 - 4, 255, 255, 255, a ); 
		lineRGBA( screen, x + 4 + 13 - 4, lprc->y + ( lprc->h - 13) / 2 + 4, x + 4 + 4, lprc->y + ( lprc->h - 13) / 2 + 13 - 4, 255, 255, 255, a ); 
	}
	x += 4 + 13 + 4;

	//
	if ( m_text.size() > 0 )
	{
		SDL_Font *pFontBig = theme->GetFont( SDL_FONTSIZE_BIG );
		SDL_Color	color = theme->GetColor( SDL_Theme::BtnText );

		SDL_Rect	rect;
		rect.x = x;
		rect.y = m_pt.y;
		rect.w = m_pt.x + m_sz.w - x;
		rect.h = m_sz.h;
		pFontBig->DrawText2( screen, m_text.c_str(), rect, color, -1, 0 );
   
		//关闭字体
		pFontBig->Release();
	}

}

bool SDL_CheckBox::OnMouseEnter( const SDL_MouseMotionEvent * motion, bool * bDraw )	
{ 
	SDL_Glyph::OnMouseEnter( motion, bDraw );
	*bDraw = true;
	return true;	
}

bool SDL_CheckBox::OnMouseLeave( const SDL_MouseMotionEvent * motion, bool * bDraw )	
{ 
	SDL_Glyph::OnMouseLeave( motion, bDraw );
	*bDraw = true;
	return true;	
}

bool SDL_CheckBox::OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	
{
	if ( !IsIn( button->x, button->y ) )
		return false;

	SetCheck( !GetCheck() );
	*bDraw = true;
	return true;
}