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
class SDL_WindowManager : public SDL_Widget, public sigslot::has_slots<>
{
protected:
	SDL_WindowManager( int width, int height, int bpp, int videoFlag );
	virtual ~SDL_WindowManager();

public:
	virtual const char * GetType()				{ return "SDL_WindowManager"; }

    virtual void SetBounds( const SDL_Rect * lprc );

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen );;

    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event, bool * b = 0 );

    /// 添加一个图元
    virtual bool Add( SDL_Glyph * g );

    /// 删除一个图元
    virtual void Remove( SDL_Glyph * g );

public:
	inline SDL_Theme * GetTheme()				{ return m_theme;	}
	inline void SetTheme( SDL_Theme * pTheme )	{ m_theme = pTheme;	}
	inline SDL_Widget * GetFocusGlyph()				{ return m_curGlyph;	}
	inline void SetFocusGlyph( SDL_Widget * pFocus )	{ m_curGlyph = pFocus;	}
	void SetIcon (const char * icon );

	void ToggleFullScreen()	{
		SDL_WM_ToggleFullScreen( m_screen );
	}

	void SetActiveWidget( SDL_Widget * w );	
	void Loop();

	//void DoModal( SDL_Window * w )	{
	//	w->destroy.connect( this, &SDL_WindowManager::OnModalWidgetClosed );
	//	SetActiveWidget( w );
	//}
public:
	static SDL_WindowManager * Create( int width, int height, int bpp, int videoFlag );
	static SDL_WindowManager * Get();

protected:
	virtual SDL_Layout * DefaultLayout() { return new SDL_CardLayout(); }
	//void OnModalWidgetClosed( SDL_Widget * w )	{
	//	Remove( w );
	//}
protected:
	SDL_Surface *	m_screen;
	SDL_Theme *		m_theme;
	int				m_videoFlag;
	int				m_bpp;
	int				m_degree;
	SDL_Widget *		m_curGlyph;
	std::vector<SDL_Window *>	m_delWindows;

protected:
	static SDL_WindowManager * m_this;
};

#endif // SDL_WINDOWMANAGER_H_INCLUDED
