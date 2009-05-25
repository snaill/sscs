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

#include "SDL_WindowManager.h"
#include <SDL_rotozoom.h>
#include <SDL_image.h>

SDL_WindowManager * SDL_WindowManager::m_this = NULL;

SDL_WindowManager::SDL_WindowManager( int width, int height, int bpp, int videoFlag )  
{ 
	TTF_Init();
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

	m_bpp = bpp;
	m_videoFlag = videoFlag;
	m_degree = 0;
	m_screen = SDL_SetVideoMode( width, height, bpp, videoFlag );
	m_screenBuffer = 0;

	m_this = this;
}

SDL_WindowManager::~SDL_WindowManager()	{
	if ( m_screen && SDL_WasInit(SDL_INIT_VIDEO) )
		SDL_FreeSurface( m_screen );

	 TTF_Quit();
}

SDL_WindowManager * SDL_WindowManager::Create( int width, int height, int bpp, int videoFlag )	
{
	if ( !m_this )
	{
		m_this = new SDL_WindowManager(width, height, bpp, videoFlag);
		m_this->m_sz.w = width;
		m_this->m_sz.h = height;
	}

	return m_this;
}

SDL_WindowManager * SDL_WindowManager::Get()	
{
	assert( m_this );
	return m_this;
}

SDL_Rect SDL_WindowManager::GetBounds()
{
	SDL_Rect	rc;
	rc.x = m_pt.x;
	rc.y = m_pt.y;
	if ( m_degree == 90 || m_degree == 270 )
	{
		rc.w = m_sz.h;
		rc.h = m_sz.w;
	}
	else
	{
		rc.w = m_sz.w;
		rc.h = m_sz.h;
	}
	return rc;
}

void SDL_WindowManager::SetBounds( const SDL_Rect * lprc )
{
	SDL_Rect	rc = *lprc;
	if ( m_degree == 90 || m_degree == 270 )
	{
		int tmp = rc.w;
		rc.w = rc.h;
		rc.h = tmp;
	}

	if ( lprc->w != m_sz.w || lprc->h != m_sz.h )
		m_screen = SDL_SetVideoMode( lprc->w, lprc->h, m_bpp, m_videoFlag );

	SDL_CardLayout::SetBounds( &rc );
}

void SDL_WindowManager::SetDegree( int nDegree )
{
	if ( m_degree == nDegree || 180 == abs(m_degree - nDegree ) )
		return;

	if ( m_screenBuffer )
	{
		SDL_FreeSurface( m_screenBuffer );
		m_screenBuffer = 0;
	}

	if ( !nDegree )
		return;

	if ( nDegree == 180 )
	{
		m_screenBuffer = SDL_CreateRGBSurface( 0, m_sz.w, m_sz.h, 32/*m_screen->format->BitsPerPixel*/, 
			m_screen->format->Rmask, m_screen->format->Gmask, m_screen->format->Bmask, m_screen->format->Amask );
	}
	else
	{
		m_screenBuffer = SDL_CreateRGBSurface( 0, m_sz.h, m_sz.w, 32/*m_screen->format->BitsPerPixel*/, 
			m_screen->format->Rmask, m_screen->format->Gmask, m_screen->format->Bmask, m_screen->format->Amask );
	}
	m_degree = nDegree;
}

SDL_Surface * SDL_WindowManager::GetScreen()
{
	if ( !m_degree )
		return m_screen;
	else
	{
		switch ( m_degree )
		{
		case 90:	
		case 180:	
		case 270:	
			return m_screenBuffer;
		}
	}

	assert(false);
	return 0;
}

void SDL_WindowManager::Update( )
{
	// 
	if ( !m_degree )
	{
		if ( m_screen->flags & SDL_DOUBLEBUF ) {
			SDL_Flip(m_screen);
		} else {
			SDL_UpdateRect(m_screen, 0, 0, 0, 0);
		}
	}
	else
	{
		SDL_Rect	rc;
		rc.x = m_pt.x;
		rc.y = m_pt.y;
		if ( m_degree == 90 || m_degree == 270 )
		{
			rc.w = m_sz.h;
			rc.h = m_sz.w;
		}
		else
		{
			rc.w = m_sz.w;
			rc.h = m_sz.h;
		}
		SDL_Surface * screen = rotateSurface90Degrees( m_screenBuffer, ( 360 - m_degree ) / 90 );
		SDL_BlitSurface( screen, 0, m_screen, &rc );

		if ( m_screen->flags & SDL_DOUBLEBUF ) {
			SDL_Flip(m_screen);
		} else {
			SDL_UpdateRect(m_screen, 0, 0, 0, 0);
		}
		SDL_FreeSurface( screen );
	}
}

void SDL_WindowManager::SetIcon( const char * icon )
{
	SDL_Surface * surface = IMG_Load( icon );
	SDL_WM_SetIcon( surface, NULL );
	SDL_FreeSurface( surface );
}
