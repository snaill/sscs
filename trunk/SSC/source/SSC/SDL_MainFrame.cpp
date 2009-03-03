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

#include "SDL_MainFrame.h"
#include <SDL_rotozoom.h>

SDL_MainFrame * SDL_MainFrame::m_this = NULL;

SDL_MainFrame::SDL_MainFrame( int width, int height, int bpp, int videoFlag )  
{ 
	TTF_Init();
	SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );

	m_bpp = bpp;
	m_videoFlag = videoFlag;
	m_degree = 0;
	m_curGlyph = 0;
	m_screen = SDL_SetVideoMode( width, height, bpp, videoFlag );

	m_this = this;
}

SDL_MainFrame::~SDL_MainFrame()	{
	if ( m_screen && SDL_WasInit(SDL_INIT_VIDEO) )
		SDL_FreeSurface( m_screen );

	 TTF_Quit();
}

SDL_MainFrame * SDL_MainFrame::Create( int width, int height, int bpp, int videoFlag )	
{
	if ( !m_this )
		m_this = new SDL_MainFrame(width, height, bpp, videoFlag);

	return m_this;
}

SDL_MainFrame * SDL_MainFrame::Get()	
{
	assert( m_this );
	return m_this;
}

void SDL_MainFrame::SetBounds( const SDL_Rect * lprc )
{
	SDL_Rect	rc = *lprc;
	if ( m_degree == 90 || m_degree == 270 )
	{
		int tmp = rc.w;
		rc.w = rc.h;
		rc.h = tmp;
	}

	if ( GetLayout() )
		GetLayout()->Update( this, &rc );
	
	SDL_BoundingBox::SetBounds( lprc );
}

void SDL_MainFrame::Draw( SDL_Surface * screen )
{
	SDL_Rect	rect = GetBounds();
	if ( m_screen->w != rect.w || m_screen->h != rect.h )
	{
		rect.w = m_screen->w;
		rect.h = m_screen->h;
		SetBounds( &rect ); 
	}

	// 
	if ( !m_degree )
	{
		SDL_Widget::Draw( m_screen );
		if ( m_screen->flags & SDL_DOUBLEBUF ) {
			SDL_Flip(m_screen);
		} else {
			SDL_UpdateRect(m_screen, 0, 0, 0, 0);
		}
	}
	else
	{
		screen = rotateSurface90Degrees( m_screen, m_degree / 90 );
		SDL_Widget::Draw( screen );
		
		SDL_Surface * screen2 = rotateSurface90Degrees( screen, ( 360 - m_degree ) / 90 );
		SDL_BlitSurface( screen2, 0, m_screen, &GetBounds() );

		if ( m_screen->flags & SDL_DOUBLEBUF ) {
			SDL_Flip(m_screen);
		} else {
			SDL_UpdateRect(m_screen, 0, 0, 0, 0);
		}
		SDL_FreeSurface( screen );
		SDL_FreeSurface( screen2 );
	}
}

bool SDL_MainFrame::HandleEvent(const SDL_Event *event, bool * b )
{
	switch (event->type) {
		case SDL_VIDEOEXPOSE:
			Draw(m_screen);
			break;
		case SDL_VIDEORESIZE:
			m_screen = SDL_SetVideoMode( event->resize.w, event->resize.h, m_bpp, m_videoFlag );
			Draw(m_screen);
			break;
		default:
		{
			bool bDraw = false;
			switch ( event->type )	{
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEMOTION:
					SDL_Widget::HandleMouseEvent( event, &bDraw );
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					if ( GetFocusGlyph() )
						GetFocusGlyph()->HandleKeyEvent( event, &bDraw );
					break;
			}
			if ( bDraw )
				Draw( m_screen );
		}
	}

	return true;
}
