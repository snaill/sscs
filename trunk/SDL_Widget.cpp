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

#include "SDL_Widget.h"

SDL_Widget::SDL_Widget() : m_pg( 0 )
{
    memset( &m_aStatus, 0x00, sizeof( SDL_WidgetStatus ) );
    m_aStatus.type = SDL_WIDGETSTATUS;
}

SDL_Widget::~SDL_Widget()
{
    if ( m_pg )
        m_pg->Release();
}

void SDL_Widget::SetClientObject( SDL_Glyph * pg )
{
    if ( m_pg )
        m_pg->Release();

    m_pg = pg;
}

void SDL_Widget::GetClientRect( SDL_Rect *rc )
{
    GetBounds( rc );
}

void SDL_Widget::GetMinSize( int * w, int * h )
{
    if ( m_pg )
        m_pg->GetMinSize( w, h );
    else
        SDL_Glyph::GetMinSize( w, h );
}

void SDL_Widget::SetBounds( const SDL_Rect *rc )
{
    SDL_Glyph::SetBounds( rc );
    if ( m_pg )
    {
        SDL_Rect rect;
        GetClientRect( &rect );
        m_pg->SetBounds( &rect );
    }
}

void SDL_Widget::Draw( SDL_Surface * screen )
{
    DrawWidget( screen );
    if ( m_pg )
        m_pg->Draw( screen );
}

bool SDL_Widget::HandleEvent(const SDL_Event *event)
{
    if ( m_pg && m_pg->HandleEvent( event ) )
        return true;

    switch ( event->type )
    {
        case SDL_MOUSEMOTION:
        {
            if ( HitTest( event->motion.x, event->motion.y ) )
            {
                if ( !m_aStatus.mouse_on )
                {
                    m_aStatus.mouse_on = true;
                    OnMouseEnter();
                }
            }
            else
            {
                if ( m_aStatus.mouse_on )
                {
                    OnMouseLeave();
                    m_aStatus.mouse_on = false;
                }
            }
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
        {
            if ( HitTest( event->button.x, event->button.y ) )
            {
                switch ( event->button.button )
                {
                    case SDL_BUTTON_LEFT:
                        m_aStatus.mouse_lbutton = SDL_PRESSED == event->button.state ? true : false;
                        break;
                    case SDL_BUTTON_MIDDLE:
                       m_aStatus.mouse_mbutton = SDL_PRESSED == event->button.state ? true : false;
                       break;
                    case SDL_BUTTON_RIGHT:
                        m_aStatus.mouse_rbutton = SDL_PRESSED == event->button.state ? true : false;
                        break;
                }
            }
        }
        break;
        case SDL_MOUSEBUTTONUP:
        {
            if ( HitTest( event->button.x, event->button.y ) )
            {
                switch ( event->button.button )
                {
                    case SDL_BUTTON_LEFT:
                        m_aStatus.mouse_lbutton = SDL_PRESSED == event->button.state ? true : false;
                        break;
                    case SDL_BUTTON_MIDDLE:
                       m_aStatus.mouse_mbutton = SDL_PRESSED == event->button.state ? true : false;
                       break;
                    case SDL_BUTTON_RIGHT:
                        m_aStatus.mouse_rbutton = SDL_PRESSED == event->button.state ? true : false;
                        break;
                }
            }
        }
        break;
    }

    return false;
}
