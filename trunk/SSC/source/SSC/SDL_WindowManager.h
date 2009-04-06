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

#ifndef SDL_WINDOWMANAGER_H_INCLUDED
#define SDL_WINDOWMANAGER_H_INCLUDED

#include "SDL_Window.h"
#include "SDL_Theme.h"
#include "SDL_CardLayout.h"

/// @brief 屏幕类负责管理页面Surface
class SDL_WindowManager : public SDL_Container
{
protected:
	SDL_WindowManager( int width, int height, int bpp, int videoFlag );
	virtual ~SDL_WindowManager();

public:
	virtual const char * GetType()				{ return "SDL_WindowManager"; }

    virtual void SetBounds( const SDL_Rect * lprc );

public:
	SDL_Surface * GetScreen();
	void Update();

	inline SDL_Theme * GetTheme()				{ return m_theme;	}
	inline void SetTheme( SDL_Theme * pTheme )	{ m_theme = pTheme;	}
	void SetIcon (const char * icon );

	void ToggleFullScreen()	{
		SDL_WM_ToggleFullScreen( m_screen );
	}

	SDL_Window * GetActiveWindow();

public:
	static SDL_WindowManager * Create( int width, int height, int bpp, int videoFlag );
	static SDL_WindowManager * Get();

protected:
	SDL_Surface *				m_screen;
	SDL_Surface *				m_screenBuffer;
	SDL_Theme *					m_theme;
	int							m_videoFlag;
	int							m_bpp;
	int							m_degree;

protected:
	static SDL_WindowManager * m_this;
};

#endif // SDL_WINDOWMANAGER_H_INCLUDED
