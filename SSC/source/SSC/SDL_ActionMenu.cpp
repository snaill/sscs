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
#include "SDL_MainFrame.h"
#include <SDL_gfxPrimitives.h>

SDL_ActionMenu::SDL_ActionMenu( SDL_Button * btn1, SDL_Button * btn2 ) 
{
	if ( !btn1 )
		btn1 = new SDL_Button( 0, 0 );
	if ( !btn2 )
		btn2 = new SDL_Button( 0, 0 );

	Add( btn1 );
	Add( btn2 );
}

void SDL_ActionMenu::DrawWidget( SDL_Surface * screen  )   
{
    //�������ļ������������С
	SDL_Theme * theme = SDL_MainFrame::Get()->GetTheme();

	SDL_Color	color = theme->GetColor( SDL_Theme::WindowText );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	int			x = m_pt.x;

	SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, 255, 255, 255 ) );

	rectangleRGBA( screen, m_pt.x, m_pt.y, m_pt.x + m_sz.w - 1, m_pt.y + m_sz.h - 1, 0, 0, 0, 100 ); 

	SDL_Widget::DrawWidget( screen );
}