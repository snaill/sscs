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

#include "SDL_BoxLayout.h"

/* SDL_HBoxLayout member function */
void SDL_HBoxLayout::SetBounds( const SDL_Rect * lprc )
{
    int w, h;
    GetMinSize( &w, &h );

    int xOff = lprc->x + ( lprc->w - w ) / 2;
    int yOff = lprc->y + ( lprc->h - h ) / 2;
    //for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
    //{
    //    SDL_Rect    rect;

    //    //(*pos)->GetMinSize( ( int * )&rect.w, ( int * )&rect.h );
    //    //rect.x = xOff;
    //    //rect.y = yOff + ( h - rect.h ) / 2;
    //    //(*pos)->SetBounds( &rect );

    //    xOff += rect.w;
    //}
}

void SDL_HBoxLayout::GetMinSize( int * w, int * h )
{
    int wSub, hSub;
    *w = *h = 0;
    //for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
    //{
    //    //(*pos)->GetMinSize( &wSub, &hSub );
    //    //*w += wSub;
    //    //if ( *h < hSub )
    //    //    *h = hSub;
    //}
}

/* SDL_VBoxLayout member function */
void SDL_VBoxLayout::SetBounds( const SDL_Rect * lprc )
{
    int w, h;
    GetMinSize( &w, &h );

    int xOff = lprc->x + ( lprc->w - w ) / 2;
    int yOff = lprc->y + ( lprc->h - h ) / 2;
    //for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
    //{
    //    SDL_Rect    rect;

    //    //(*pos)->GetMinSize( ( int * )&rect.w, ( int * )&rect.h );
    //    //rect.x = xOff + ( w - rect.w ) / 2;
    //    //rect.y = yOff;
    //    //(*pos)->SetBounds( &rect );

    //    yOff += rect.h;
    //}
}

void SDL_VBoxLayout::GetMinSize( int * w, int * h )
{
    int wSub, hSub;
    *w = *h = 0;
    //for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
    //{
    //    //(*pos)->GetMinSize( &wSub, &hSub );
    //    // if ( *w < wSub )
    //    //    *w = wSub;
    //    *h += hSub;
    //}
}

