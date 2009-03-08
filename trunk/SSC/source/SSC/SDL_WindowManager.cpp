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
	m_curGlyph = 0;
	m_screen = SDL_SetVideoMode( width, height, bpp, videoFlag );

	m_this = this;
}

SDL_WindowManager::~SDL_WindowManager()	{
	if ( m_screen && SDL_WasInit(SDL_INIT_VIDEO) )
		SDL_FreeSurface( m_screen );

	 TTF_Quit();

	 disconnect_all();
}

SDL_WindowManager * SDL_WindowManager::Create( int width, int height, int bpp, int videoFlag )	
{
	if ( !m_this )
		m_this = new SDL_WindowManager(width, height, bpp, videoFlag);

	return m_this;
}

SDL_WindowManager * SDL_WindowManager::Get()	
{
	assert( m_this );
	return m_this;
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

	if ( GetLayout() )
		GetLayout()->Update( this, &rc );
	
	SDL_BoundingBox::SetBounds( lprc );
}

void SDL_WindowManager::Draw( SDL_Surface * screen )
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

bool SDL_WindowManager::HandleEvent(const SDL_Event *event, bool * b )
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

void SDL_WindowManager::Loop()
{
	/* Wait for a keystroke */
	int			done = 0;
	SDL_Event	event;

	while ( !done && SDL_WaitEvent(&event) ) {
		switch (event.type) {
			/* Any other key quits the application... */
			case SDL_QUIT:
				done = 1;
				break;			
			default:
				HandleEvent( &event, 0 );
				break;
		}
	}
}

void SDL_WindowManager::SetIcon( const char * icon )
{
	SDL_Surface * surface = IMG_Load( icon );
	SDL_WM_SetIcon( surface, NULL );
	SDL_FreeSurface( surface );

}

void SDL_WindowManager::SetActiveWidget( SDL_Widget * w )	
{
	SDL_CardLayout * pLayout = (SDL_CardLayout *)GetLayout();
	if ( pLayout )
	{
		pLayout->SetActiveItem( w );
		RecalcLayout();
	}
}

bool SDL_WindowManager::Add( SDL_Glyph * g )
{
	assert( g );
    m_aChildren.push_back( g );
   return true;
}

void SDL_WindowManager::Remove( SDL_Glyph * g )
{
    assert( g );
    for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
	{
		if ( g == *pos ) {
            m_aChildren.erase( pos );
		}
	}
}
