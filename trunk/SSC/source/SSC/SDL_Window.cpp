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

void SDL_Window::Show()		
{
	SDL_WindowManager::Get()->Add( this );
	SDL_WindowManager::Get()->SetActiveWidget( this );
}

void SDL_Window::SetTitle( const char *title )	
{
	if ( !m_strTitle.compare( title ) )
		return;

	m_strTitle = title;
	if ( m_bActive )
		SDL_WM_SetCaption( m_strTitle.c_str(), 0 );
}

void SDL_Window::Active()	
{
	if ( m_bActive )
		return;

	SDL_WM_SetCaption( m_strTitle.c_str(), 0 );
	m_bActive = true;
}

void SDL_Window::UnActive()	
{
	m_bActive = false;
}

void SDL_Window::Destory()
{
	SDL_WindowManager::Get()->Remove( this );
//	Release();
}