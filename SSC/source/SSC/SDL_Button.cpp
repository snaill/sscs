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

#include "SDL_Button.h"
#include "SDL_MainFrame.h"
#include <SDL_gfxPrimitives.h>

SDL_Button::SDL_Button( SDL_Label * text, SDL_Image * image ) 
{
	if ( image )
		Add( image );

	assert( text );
	text->SetColor( SDL_Theme::BtnText );
	Add( text );
}

SDL_Size SDL_Button::GetPreferedSize()	
{
	SDL_Size	sz = SDL_Widget::GetPreferedSize();
	//sz.w = 0;
	//sz.h = 0;

	//if ( m_imgList )
	//{
	//	SDL_Size	szImage = m_imgList->GetImageSize();
	//	sz.w = szImage.w;
	//	sz.h += szImage.h + 4;
	//}

	//if ( m_text.size() > 0 )
	//{
	//	SDL_Theme * theme = SDL_MainFrame::Get()->GetTheme();
	//	SDL_Font *pFont = theme->GetFont( SDL_Theme::Text );
	//	SDL_Size	szFont = pFont->GetTextSize( m_text.c_str() );
	//	if ( sz.w < szFont.w )
	//		sz.w = szFont.w;
	//	sz.h += szFont.h;	
	//	pFont->Release();
	//}

	sz.w += 4 + 4;
	sz.h += 4 + 4;
	return sz;
}

void SDL_Button::DrawWidget( SDL_Surface * screen  )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_MainFrame::Get()->GetTheme();
	SDL_Font *pFont = theme->GetFont( 0 );

	SDL_Color	crText = theme->GetColor( SDL_Theme::BtnText );
	SDL_Color	crFace = theme->GetColor( SDL_Theme::BtnFace );

	SDL_Rect	rc = GetBounds();
	SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, crFace.r, crFace.g, crFace.b ) );

	//
	SDL_Widget::DrawWidget( screen );

	//
	if ( GetHover() )
	{
		SDL_Rect	rc2;
		rc2.x = m_pt.x + 2;
		rc2.y = m_pt.y + 2;
		rc2.w = m_sz.w - 4;
		rc2.h = m_sz.h - 4;

		SDL_Color	cr1, cr2;
		cr1.r = cr1.g = cr1.b = 0;
		cr2.r = cr2.g = cr2.b = 192;

		if ( SDL_BUTTON(1) == SDL_GetMouseState( 0, 0 ) )
	//	if ( m_bMouseButtonDown )
            Draw3DRect( screen, rc2, cr1, cr2);
		else 
            Draw3DRect( screen, rc2, cr2, cr1);
	}
}

bool SDL_Button::OnMouseEnter( const SDL_MouseMotionEvent * motion, bool * bDraw )	
{ 
	if ( !motion->state )
	{
		SDL_Widget::OnMouseEnter( motion, bDraw );
		*bDraw = true;
	}
	return true;	
}

bool SDL_Button::OnMouseLeave( const SDL_MouseMotionEvent * motion, bool * bDraw )	
{ 
	SDL_Widget::OnMouseLeave( motion, bDraw );
	*bDraw = true;
	return true;	
}

bool SDL_Button::OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	
{
	if ( !IsIn( button->x, button->y ) )
		return false;

		click( this );
	*bDraw = true;
	return true;
}

bool SDL_Button::OnMouseUp( const SDL_MouseButtonEvent * button, bool * bDraw )	
{
	if ( IsIn( button->x, button->y ) )
		click( this );

	*bDraw = true;
	return true;
}