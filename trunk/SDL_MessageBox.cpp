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

#include "SDL_MessageBox.h"
#include "SDL_BoxLayout.h"
#include "SDL_Button.h"
#include "SDL_Text.h"
#include <SDL_draw.h>

SDL_MessageBox::SDL_MessageBox( const char * szTitle, const char * szMsg )
{
    SDL_HBoxLayout * hbox = new SDL_HBoxLayout();
    hbox->Add( new SDL_Button( new SDL_Text( "OK" ) ) );
    hbox->Add( new SDL_Button( new SDL_Text( "Cancel" ) ) );

    SDL_VBoxLayout * vbox = new SDL_VBoxLayout();
    vbox->Add( new SDL_Text( szTitle ) );
    vbox->Add( new SDL_Text( szMsg ) );
    vbox->Add( hbox );

    SetClientObject( vbox );
}

void SDL_MessageBox::GetClientRect( SDL_Rect *rc )
{
    rc->x = m_rc.x + 4;
    rc->y = m_rc.y + 4;
    rc->w = m_rc.w - 4 * 2;
    rc->h = m_rc.h - 4 * 2;
}

void SDL_MessageBox::DrawWidget( SDL_Surface * screen )
{
    Draw_Rect( screen, m_rc.x, m_rc.y, m_rc.w, m_rc.h, SDL_MapRGB(screen->format, 192, 192, 192) );

    SDL_Rect    rect;
    rect.x = m_rc.x + 1;
    rect.y = m_rc.y + 1;
    rect.w = m_rc.w - 2;
    rect.h = m_rc.h - 2;
    Draw_Rect( screen, rect.x, rect.y, rect.w, rect.h, SDL_MapRGB(screen->format, 0, 0, 0) );

    rect.x = rect.x + 1;
    rect.y = rect.y + 1;
    rect.w = rect.w - 2;
    rect.h = rect.h - 2;
    Draw_Rect( screen, rect.x, rect.y, rect.w, rect.h, SDL_MapRGB(screen->format, 192, 192, 192) );
}
