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

#include "SDL_SwitchUI.h"
#include "SDL_WindowManager.h"

void SDL_SwitchUI::SetOld( SDL_Glyph * g )
{
	m_old = g->ToSurface( SDL_WindowManager::Get()->GetScreen() );
	m_rcClip = g->GetBounds();
}

void SDL_SwitchUI::SetNew( SDL_Glyph * g )
{
	m_new = g->ToSurface( SDL_WindowManager::Get()->GetScreen() );
}

void SDL_SwitchUI::Switch( int nMode )
{
	switch ( nMode )
	{
	case toLeft:
		ToLeft( SDL_WindowManager::Get()->GetScreen(), &m_rcClip, m_old, m_new );
		break;
	case toRight:
		ToRight( SDL_WindowManager::Get()->GetScreen(), &m_rcClip, m_old, m_new );
		break;
	}
}

void SDL_SwitchUI::ToLeft( SDL_Surface * screen, const SDL_Rect * lprc, SDL_Surface * oldSurface, SDL_Surface * newSurface )
{
	SDL_Rect	rcOld;
	SDL_GetClipRect( screen, &rcOld );
//	SDL_SetClipRect( screen, lprc );

	SDL_Rect	rcOldScreen;
	rcOldScreen.x = lprc->x;
	rcOldScreen.y = 0;
	rcOldScreen.w = lprc->w;
	rcOldScreen.h = lprc->h;

	SDL_Rect	rcOldSurface;
	rcOldSurface.x = 0;
	rcOldSurface.y = 0;
	rcOldSurface.w = rcOldScreen.w;
	rcOldSurface.h = rcOldScreen.h;

	SDL_Rect	rcNewScreen;
	rcNewScreen.x = lprc->x + lprc->w;
	rcNewScreen.y = 0;
	rcNewScreen.w = 0;
	rcNewScreen.h = lprc->h;

	SDL_Rect	rcNewSurface;
	rcNewSurface.x = 0;
	rcNewSurface.y = 0;
	rcNewSurface.w = 0;
	rcNewSurface.h = rcNewScreen.h;

	int xOff = lprc->w / 10;
	for ( int i = 0; i < 9; i ++ )
	{
		rcOldScreen.w -= xOff;
		rcOldSurface.x += xOff;
		rcOldSurface.w -= xOff;

		rcNewScreen.x -= xOff;
		rcNewScreen.w += xOff;
		rcNewSurface.w += xOff;

		SDL_BlitSurface( oldSurface, &rcOldSurface, screen, &rcOldScreen );
		SDL_BlitSurface( newSurface, &rcNewSurface, screen, &rcNewScreen );

		SDL_UpdateRect(screen, lprc->x, lprc->y, lprc->w, lprc->h);

		SDL_Delay( 20 );
	}
		
	SDL_BlitSurface( newSurface, 0, screen, ( SDL_Rect * )lprc );

	SDL_SetClipRect( screen, &rcOld );
}


void SDL_SwitchUI::ToRight( SDL_Surface * screen, const SDL_Rect * lprc, SDL_Surface * oldSurface, SDL_Surface * newSurface )
{
	SDL_Rect	rcOld;
	SDL_GetClipRect( screen, &rcOld );
//	SDL_SetClipRect( screen, lprc );

	SDL_Rect	rcOldScreen;
	rcOldScreen.x = lprc->x;
	rcOldScreen.y = 0;
	rcOldScreen.w = lprc->w;
	rcOldScreen.h = lprc->h;

	SDL_Rect	rcOldSurface;
	rcOldSurface.x = 0;
	rcOldSurface.y = 0;
	rcOldSurface.w = rcOldScreen.w;
	rcOldSurface.h = rcOldScreen.h;

	SDL_Rect	rcNewScreen;
	rcNewScreen.x = 0;
	rcNewScreen.y = 0;
	rcNewScreen.w = lprc->w;
	rcNewScreen.h = lprc->h;

	SDL_Rect	rcNewSurface;
	rcNewSurface.x = rcNewScreen.w;
	rcNewSurface.y = 0;
	rcNewSurface.w = 0;
	rcNewSurface.h = rcNewScreen.h;

	int xOff = lprc->w / 10;
	for ( int i = 0; i < 9; i ++ )
	{
		rcOldScreen.x += xOff;
		rcOldScreen.w -= xOff;
		rcOldSurface.w -= xOff;

		rcNewScreen.w += xOff;
		rcNewSurface.x -= xOff;
		rcNewSurface.w += xOff;

		SDL_BlitSurface( oldSurface, &rcOldSurface, screen, &rcOldScreen );
		SDL_BlitSurface( newSurface, &rcNewSurface, screen, &rcNewScreen );

		SDL_UpdateRect(screen, lprc->x, lprc->y, lprc->w, lprc->h);

		SDL_Delay( 20 );
	}
		
	SDL_BlitSurface( newSurface, 0, screen, ( SDL_Rect * )lprc );

	SDL_SetClipRect( screen, &rcOld );
}

void SDL_SwitchUI::Move( SDL_Surface * screen, SDL_Surface * oldSurface, SDL_Surface * newSurface, int nMode, bool bOldMove, const SDL_Rect * lprc )
{
	SDL_Rect	rcOldScreen, rcOldSurface, rcNewScreen, rcNewSurface;

	rcOldScreen = *lprc;

	rcOldSurface.x = 0;
	rcOldSurface.y = 0;
	rcOldSurface.w = rcOldScreen.w;
	rcOldSurface.h = rcOldScreen.h;

	rcNewScreen = rcOldScreen;
	rcNewSurface = rcOldSurface;

	switch ( nMode )	{
		case toLeft:
			rcNewScreen.x = rcOldScreen.x + rcOldScreen.w;
			rcNewScreen.w = 0;
			rcNewSurface.w = 0;
			break;
		case toRight:
			break;
	}

	int xOff = lprc->w / 10;
	int yOff = lprc->h / 10;
	for ( int i = 0; i < 9; i ++ )
	{
		switch ( nMode )
		{
		case toLeft:
			if ( bOldMove )
			{
				rcOldScreen.w -= xOff;
				rcOldSurface.x += xOff;
				rcOldSurface.w -= xOff;
			}
			rcNewScreen.x -= xOff;
			rcNewScreen.w += xOff;
			rcNewSurface.w += xOff;
			break;
		case toRight:
			if ( bOldMove )
			{
				rcOldScreen.x += xOff;
				rcOldScreen.w -= xOff;
				rcOldSurface.w -= xOff;
			}
			rcNewScreen.w += xOff;
			rcNewSurface.x -= xOff;
			rcNewSurface.w += xOff;
			break;
		}


		SDL_BlitSurface( oldSurface, &rcOldSurface, screen, &rcOldScreen );
		SDL_BlitSurface( newSurface, &rcNewSurface, screen, &rcNewScreen );

		SDL_UpdateRect(screen, lprc->x, lprc->y, lprc->w, lprc->h);

		SDL_Delay( 20 );
	}
		
	SDL_BlitSurface( newSurface, 0, screen, ( SDL_Rect * )lprc );
}

void SDL_SwitchUI::Switch( int nMode, bool bOldMove, SDL_Glyph * gOld, SDL_Glyph * gNew )
{
	SDL_Surface *	sOld = gOld->ToSurface( SDL_WindowManager::Get()->GetScreen() );
	SDL_Surface *	sNew = gNew->ToSurface( SDL_WindowManager::Get()->GetScreen() );
	SDL_Rect		rcClip = gOld->GetBounds();
	Move( SDL_WindowManager::Get()->GetScreen(), sOld, sNew, nMode, bOldMove, &rcClip );

}

void SDL_SwitchUI::Switch( int nMode, SDL_Glyph * g, SwitchUIFunc f, long lParam, bool bOldMove )
{
	SDL_Surface *	sOld = g->ToSurface( SDL_WindowManager::Get()->GetScreen() );
	SDL_Rect		rcClip = g->GetBounds();
	
	f( lParam );
	
	SDL_Surface *	sNew = g->ToSurface( SDL_WindowManager::Get()->GetScreen() );
	Move( SDL_WindowManager::Get()->GetScreen(), sOld, sNew, nMode, bOldMove, &rcClip );
}