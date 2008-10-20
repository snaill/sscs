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

void SDL_BoxLayout::ReCalc()
{
    int w, h;
    GetMinSize( &w, &h );
}

void SDL_BoxLayout::GetMinSize( int * w, int * h )
{
    int wSub, hSub;
    *w = *h = 0;
    for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
    {
        (*pos)->GetMinSize( &wSub, &hSub );
        *w += wSub;
        if ( *h < hSub )
            *h = hSub;
    }
}
