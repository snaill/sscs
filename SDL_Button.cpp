/*
 * SDL_Button.cpp
 * Copyright (C) Snaill 2008 <snaill@jeebook.com>
 *
    SDL_Button.cpp is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    main.c is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SDL_Button.h"
#include "SDL_Text.h"

SDL_Button::SDL_Button( const char * text )
{
    SDL_Status status;

    SDL_Text * pText = new SDL_Text( text );
    pText->GetTextStatus( &status );
    status.type = SDL_TEXTSTATUS;
    status.text.size = 13;
    status.text.crText.r = 128;
    status.text.crText.g = 128;
    status.text.crText.b = 128;
    pText->SetTextStatus( &status );

    Add( pText );
}

SDL_Button::~SDL_Button(void)
{
}

void SDL_Button::Draw( SDL_Surface * screen )
{
    if ( m_aStatus.mouse_on )
    {
        if ( m_aStatus.mouse_lbutton )
            Draw3DRect( screen, m_rc, SDL_MapRGB(screen->format, 0, 0, 0), SDL_MapRGB(screen->format, 192, 192, 192));
        else
            Draw3DRect( screen, m_rc, SDL_MapRGB(screen->format, 192, 192, 192), SDL_MapRGB(screen->format, 0, 0, 0));
    }

    SDL_Widget::Draw( screen );
}

void SDL_Button::SetBounds(const SDL_Rect *rc)
{
    m_aChildren[0]->SetBounds( rc );
    SDL_Widget::SetBounds( rc );
}

bool SDL_Button::HandleEvent(const SDL_Event *event)
{
    switch ( event->type )
    {
//        case SDL_MOUSEMOTION:
//        {
//            SDL_MouseMotionEvent * mevent = ( SDL_MouseMotionEvent * )event;
//            if ( HitTest( mevent->x, mevent->y ) )
//            {
//                if ( !m_bHot )
//                    m_bHot = true;
//            }
//            else
//            {
//                if ( m_bHot )
//                    m_bHot = false;
//            }
//        }
    }
    return SDL_Widget::HandleEvent( event );
}

void SDL_Button::OnMouseEnter()
{
    SDL_Text * pText = ( SDL_Text * )m_aChildren[0];
    SDL_Status status;
    pText->GetTextStatus( &status );
    status.text.crText.r = 0;
    status.text.crText.g = 0;
    status.text.crText.b = 0;
    pText->SetTextStatus( &status );
}

void SDL_Button::OnMouseLeave()
{
    SDL_Text * pText = ( SDL_Text * )m_aChildren[0];
    SDL_Status status;
    pText->GetTextStatus( &status );
    status.text.crText.r = 128;
    status.text.crText.g = 128;
    status.text.crText.b = 128;
    pText->SetTextStatus( &status );
}
