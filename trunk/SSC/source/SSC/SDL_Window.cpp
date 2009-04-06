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

#include "SDL_Window.h"
#include "SDL_WindowManager.h"
#include "SDL_SwitchUI.h"
#include <SDL_rotozoom.h>

void SDL_Window::SetTitle( const char *title )	
{
	if ( !m_strTitle.compare( title ) )
		return;

	m_strTitle = title;
}

void SDL_Window::Show()		
{
	SDL_WindowManager * wm = SDL_WindowManager::Get();
	SDL_Rect			rc = wm->GetBounds();

	SetBounds( &rc );
	wm->Add( this );

	SDL_SwitchUI	sui;
	sui.Switch( SDL_SwitchUI::toLeft, true, SDL_WindowManager::Get()->GetActiveWindow(), this );

	Loop();
}

void SDL_Window::Destory()
{
	SDL_WindowManager::Get()->Remove( this );

	SDL_SwitchUI	sui;
	sui.Switch( SDL_SwitchUI::toRight, true, this, SDL_WindowManager::Get()->GetActiveWindow() );

	m_bLoop = false;
}

void SDL_Window::Draw( SDL_Surface * screen )
{
	SDL_Widget::Draw( screen );
	SDL_WindowManager::Get()->Update();
}

void SDL_Window::Loop()
{
	/* Wait for a keystroke */
	SDL_Event	event;
	
	m_bLoop = true;
	while ( m_bLoop && SDL_WaitEvent(&event) ) 
	{
		switch (event.type) 
		{
			/* Any other key quits the application... */
			case SDL_QUIT:
				SDL_PushEvent( &event );
				return;			
			case SDL_VIDEOEXPOSE:
				Draw( SDL_WindowManager::Get()->GetScreen() );
				break;
			case SDL_VIDEORESIZE:
				{
					SDL_Rect	rc = SDL_WindowManager::Get()->GetBounds();
					rc.w = event.resize.w;
					rc.h = event.resize.h;
					SDL_WindowManager::Get()->SetBounds( &rc );
					Draw( SDL_WindowManager::Get()->GetScreen() );
				}
				break;
			default:
			{
				bool bDraw = false;
				switch ( event.type )	
				{
					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
					case SDL_MOUSEMOTION:
						HandleMouseEvent( &event, &bDraw );
						break;
				}
				if ( bDraw )
					Draw( SDL_WindowManager::Get()->GetScreen() );
			}
		}
	}
}