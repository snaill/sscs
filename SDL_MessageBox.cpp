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
