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

#include "SDL_ActionMenu.h"
#include "SDL_Spacer.h"
#include "SDL_WindowManager.h"
#include <SDL_gfxPrimitives.h>

SDL_ActionMenu::SDL_ActionMenu( SDL_Button * btn1, SDL_Button * btn2 ) 
{
	SDL_HBoxLayout * layout = new SDL_HBoxLayout();
	layout->Add( btn1 ? ( SDL_Glyph * )btn1 : ( SDL_Glyph * )new SDL_Spacer() );
	layout->Add( btn2 ? ( SDL_Glyph * )btn2 : ( SDL_Glyph * )new SDL_Spacer() );
	SetContent( layout );
}

void SDL_ActionMenu::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc  )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_WindowManager::Get()->GetTheme();

	SDL_Color	color = theme->GetColor( SDL_Theme::BtnText );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	int			x = m_pt.x;

	SDL_FillRect( screen, ( SDL_Rect * )lprc, SDL_MapRGB( screen->format, 255, 255, 255 ) );

	rectangleRGBA( screen, m_pt.x, m_pt.y, m_pt.x + m_sz.w - 1, m_pt.y + m_sz.h - 1, 0, 0, 0, 100 ); 

	SDL_Glyph::DrawWidget( screen, lprc );
}
