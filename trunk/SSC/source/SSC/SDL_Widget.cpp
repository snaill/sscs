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
#include "SDL_WindowManager.h"
#include <SDL_gfxPrimitives.h>

void SDL_Widget::Draw3DRect( SDL_Surface *screen, SDL_Rect rect, SDL_Color clrTopLeft, SDL_Color clrBottomRight )
{
	hlineRGBA( screen, rect.x, rect.x + rect.w - 1, rect.y, clrTopLeft.r, clrTopLeft.g, clrTopLeft.b, 255 );
    vlineRGBA( screen, rect.x, rect.y, rect.y + rect.h - 1, clrTopLeft.r, clrTopLeft.g, clrTopLeft.b, 255 );
    hlineRGBA( screen, rect.x, rect.x + rect.w - 1, rect.y + rect.h - 1, clrBottomRight.r, clrBottomRight.g, clrBottomRight.b, 255 );
    vlineRGBA( screen, rect.x + rect.w - 1, rect.y, rect.y + rect.h - 1, clrBottomRight.r, clrBottomRight.g, clrBottomRight.b, 255 );
}

SDL_Widget * SDL_Widget::SetFocus()
{
	SDL_WindowManager * pScreen = SDL_WindowManager::Get();
	SDL_Widget * pOld = pScreen->GetFocusGlyph();
	if ( pOld == this )
		return this;

	pScreen->SetFocusGlyph( this );
	return pOld;
}