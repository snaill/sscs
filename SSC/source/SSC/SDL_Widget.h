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

#ifndef SDL_WIDGET_H_INCLUDED
#define SDL_WIDGET_H_INCLUDED

#include "SDL_Container.h"
#include "SDL_Layout.h"
#include "sigslot.h"

/// @brief 控件类的基类
class SDL_Widget : public SDL_Container, public sigslot::has_slots<>
{
public:
	SDL_Widget() : m_pLayout(0), m_nLayoutProperty(0) {}

	~SDL_Widget() {
		if ( m_pLayout )
			m_pLayout->Release();
				
		disconnect_all();
	}

	virtual const char * GetType() { return "widget"; }

	/// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
	virtual SDL_Size GetPreferedSize()	{
		if ( GetLayout() )
			return GetLayout()->GetPreferedSize();

		return SDL_Size( 32, 32 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc ){
		if ( GetLayout() )
			GetLayout()->Update( this, lprc );
		
		SDL_Glyph::SetBounds( lprc );
	}

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen )
	{
		SDL_Rect	rcOld;
		SDL_GetClipRect( screen, &rcOld );
		SDL_SetClipRect( screen, &And( rcOld ) );

		DrawWidget( screen );
		SDL_Container::Draw( screen );

		SDL_SetClipRect( screen, &rcOld );
	}

 	virtual bool HandleEvent(const SDL_Event *event, bool * bDraw){
		if ( SDL_Container::HandleEvent(event, bDraw ) )
			return true;

		switch ( event->type )
		{
			case SDL_KEYDOWN:			return OnKeyDown( &event->key, bDraw );
			case SDL_KEYUP:				return OnKeyUp( &event->key, bDraw );
			case SDL_MOUSEBUTTONDOWN:	return OnMouseDown( &event->button, bDraw );
			case SDL_MOUSEMOTION:		return OnMouseMove( &event->motion, bDraw );
		}

		return false;
	}

	virtual void Show( bool bShow ) { 
		if ( m_bShow == bShow )
			return;

		if ( GetParent() )
			( ( SDL_Widget * )GetParent() )->RecalcLayout();

		m_bShow = bShow;
	}

public:
	virtual void RecalcLayout()	{ 
		if ( GetLayout() )
			GetLayout()->Update( this, &GetBounds() );
	}

	///
    virtual SDL_Layout * GetLayout(){ return m_pLayout;	}
    virtual void SetLayout( SDL_Layout * layout ){ m_pLayout = layout; }
    virtual int GetLayoutProperty(){ return m_nLayoutProperty;	}
    virtual void SetLayoutProperty( int layoutProperty ){ m_nLayoutProperty = layoutProperty; }

protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen ) {}

// 事件
	virtual bool OnMouseUp( const SDL_MouseButtonEvent * button, bool * bDraw )	{ return false;	}
	virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	{ return false;	}
	virtual bool OnMouseMove( const SDL_MouseMotionEvent * motion, bool * bDraw )	{ return false;	}
	virtual bool OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw ) { return false;	}
	virtual bool OnKeyUp( const SDL_KeyboardEvent * key, bool * bDraw ) { return false;	}

protected:
    /// 客户对象，允许是图元或布局
	SDL_Layout *	m_pLayout;
	int				m_nLayoutProperty;
};

#endif // SDL_WIDGET_H_INCLUDED
