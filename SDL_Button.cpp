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
#include "SDL_Text.h"

SDL_Button::SDL_Button( SDL_Glyph * pg )
{
    SetClientObject( pg );
}

SDL_Button::~SDL_Button(void)
{
}

void SDL_Button::GetClientRect( SDL_Rect *rc )
{
    rc->x = m_rc.x + 2;
    rc->y = m_rc.y + 2;
    rc->w = m_rc.w - 2 * 2;
    rc->h = m_rc.h - 2 * 2;
}

void SDL_Button::DrawWidget( SDL_Surface * screen )
{
    if ( m_aStatus.mouse_on )
    {
        if ( m_aStatus.mouse_lbutton )
            Draw3DRect( screen, m_rc, SDL_MapRGB(screen->format, 0, 0, 0), SDL_MapRGB(screen->format, 192, 192, 192));
        else
            Draw3DRect( screen, m_rc, SDL_MapRGB(screen->format, 192, 192, 192), SDL_MapRGB(screen->format, 0, 0, 0));
    }
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
