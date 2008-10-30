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

#include "SDL_Glyph.h"
#include <SDL_draw.h>

void SDL_Glyph::Draw3DRect( SDL_Surface *screen, SDL_Rect rect, Uint32 clrTopLeft, Uint32 clrBottomRight )
{
    Draw_HLine( screen, rect.x, rect.y, rect.x + rect.w - 1, clrTopLeft );
    Draw_VLine( screen, rect.x, rect.y, rect.y + rect.h - 1, clrTopLeft );
    Draw_HLine( screen, rect.x, rect.y + rect.h - 1, rect.x + rect.w - 1, clrBottomRight );
    Draw_VLine( screen, rect.x + rect.w - 1, rect.y, rect.y + rect.h - 1, clrBottomRight );
}

