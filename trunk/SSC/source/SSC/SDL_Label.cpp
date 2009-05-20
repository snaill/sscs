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

#include "SDL_Label.h"
#include "SDL_Font.h"
#include "SDL_Theme.h"
#include "SDL_WindowManager.h"
#include <SDL_gfxPrimitives.h>

SDL_Label::SDL_Label( const wchar_t * text, int nFont, int nColor, int align, int valign ) 
{
	if ( text )
		m_text = text;
	m_nFont = nFont;
	m_nColor = nColor;
	m_align = align;
	m_valign = valign;
}

SDL_Size SDL_Label::GetPreferedSize()	
{	
	SDL_Size	szFont( 0, 0 );

	if ( m_text.size() > 0 )
	{
		SDL_Theme * theme = SDL_WindowManager::Get()->GetTheme();
		SDL_Font *pFontBig = theme->GetFont( m_nFont );
		szFont = pFontBig->GetTextSize( m_text.c_str() );
		pFontBig->Release();
	}

	return szFont;
}

void SDL_Label::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc )   
{
	if ( m_text.size() > 0 )
	{
		SDL_Theme * theme = SDL_WindowManager::Get()->GetTheme();
		SDL_Font *pFontBig = theme->GetFont( m_nFont );
		SDL_Color	color = theme->GetColor( m_nColor );

		pFontBig->DrawText2( screen, m_text.c_str(), *lprc, color, m_align, m_valign );
   
		//¹Ø±Õ×ÖÌå
		pFontBig->Release();
	}

}
