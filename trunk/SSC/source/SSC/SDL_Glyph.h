/*
 * SDL_SimpleControls
 * Copyright (C) 2009 Snaill
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

#ifndef SDL_GLYPH_H_INCLUDED
#define SDL_GLYPH_H_INCLUDED

#include "SDL_Object.h"

/// @brief 控件类的基类
class SDL_Glyph : public SDL_Object, public SDL_BoundingBox
{
public:
	SDL_Glyph() :m_bHover(false), m_bVisible( true ), 
		m_pParent(0), m_bCheck( false ) {}

	virtual ~SDL_Glyph() {}

	virtual const char * GetType() = 0;

	/// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
	virtual SDL_Size GetPreferedSize() { return SDL_Size( 0, 0 ); }

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen )
	{
		SDL_Rect	rcOld;
		SDL_GetClipRect( screen, &rcOld );

		SDL_Rect	rcClip = And( rcOld );
		if ( !rcClip.w || !rcClip.h )
			return;

		SDL_SetClipRect( screen, &rcClip );

		DrawWidget( screen, &GetBounds() );

		SDL_SetClipRect( screen, &rcOld );
	}

	virtual int GetLayoutProperty(){ return m_nLayoutProperty;	}
    virtual void SetLayoutProperty( int layoutProperty ){ m_nLayoutProperty = layoutProperty; }

	SDL_Surface * ToSurface( SDL_Surface * screen );

 	virtual bool HandleMouseEvent(const SDL_Event *event, bool * bDraw){
		log_f_start( "HandleMouseEvent" );

		if ( GetContent() )
			GetContent()->HandleMouseEvent( event, bDraw );

		bool bHandled = false;
		switch ( event->type )
		{
			case SDL_MOUSEBUTTONUP: 
				bHandled = OnMouseUp( &event->button, bDraw );
				break;
			case SDL_MOUSEBUTTONDOWN: 
				bHandled = OnMouseDown( &event->button, bDraw );
				break;
			case SDL_MOUSEMOTION:		
				if ( IsIn( event->motion.x, event->motion.y ) )
				{
					if ( m_bHover )
						bHandled = OnMouseMove( &event->motion, bDraw );
					else
						bHandled = OnMouseEnter( &event->motion, bDraw );
				}
				else
					if ( m_bHover )
						bHandled = OnMouseLeave( &event->motion, bDraw );
				break;
		}

		log_f_end( "HandleMouseEvent" );
		return bHandled;
	}
	
	///
    virtual SDL_Glyph * GetContent(){ 	return m_pContent;	}
    virtual void SetContent( SDL_Glyph * content ){ m_pContent = content; }
	///
    virtual SDL_Glyph * GetParent(){ return m_pParent;	}
    virtual void SetParent( SDL_Glyph * parent ){ m_pParent = parent; }

public:
	virtual void RecalcLayout( bool bDraw = true )	{ 
		SetBounds( &GetBounds() );

		if ( bDraw )
			RedrawWidget();
	}

	virtual void RedrawWidget()	{
		SDL_Event	event;
		event.type = SDL_VIDEOEXPOSE;
		SDL_PushEvent( &event );
	}

public:
	bool GetVisible()			{ return m_bVisible;	}
	void SetVisible( bool bVisible ) { 
		if ( m_bVisible == bVisible )
			return;

		m_bVisible = bVisible;
		if ( GetParent() )
			GetParent()->RecalcLayout();
	}
	bool GetCheck()					{ return m_bCheck;		}
	void SetCheck( bool bCheck )	{ m_bCheck = bCheck;	}
	bool GetHover()					{ return m_bHover;		}
	void SetHover( bool bHover )	{ m_bHover = bHover;	}

protected:
protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc ) {}

    void Draw3DRect( SDL_Surface *screen, SDL_Rect rect, SDL_Color clrTopLeft, SDL_Color clrBottomRight );

// 事件
	virtual bool OnMouseEnter( const SDL_MouseMotionEvent * motion, bool * bDraw )	{ m_bHover = true; return false;	}
	virtual bool OnMouseLeave( const SDL_MouseMotionEvent * motion, bool * bDraw )	{ m_bHover = false; return false;	}
	virtual bool OnMouseUp( const SDL_MouseButtonEvent * button, bool * bDraw )	{ return false;	}
	virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	{ return false;	}
	virtual bool OnMouseMove( const SDL_MouseMotionEvent * motion, bool * bDraw )	{ return false;	}
	virtual bool OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw ) { return false;	}
	virtual bool OnKeyUp( const SDL_KeyboardEvent * key, bool * bDraw ) { return false;	}

protected:
	int				m_nLayoutProperty;
	/// 客户对象，允许是图元或布局
	SDL_Glyph *		m_pContent;
	SDL_Glyph *		m_pParent;
	bool			m_bHover;
	bool			m_bVisible;
	bool			m_bCheck;
};

#endif // SDL_GLYPH_H_INCLUDED
