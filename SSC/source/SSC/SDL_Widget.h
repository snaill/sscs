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
#include "sigslot.h"

struct SDL_WidgetStatus {
	long			lParam;
	long			m_bHover : 1;
	long			m_bVisible : 1;
	long			m_bCheck : 1;
	long			m_bSelected : 1;
};
/// @brief 控件类的基类
class SDL_Widget : public SDL_Container
{
public:
	sigslot::signal1<SDL_Widget *>		add;
	sigslot::signal1<SDL_Widget *>		remove;

public:
	SDL_Widget() :m_bHover(false), m_bVisible( true ), 
		m_pParent(0), m_bCheck( false ) {}

	virtual ~SDL_Widget() {}

	virtual const char * GetType() { return "SDL_Widget"; }

 	virtual bool HandleMouseEvent(const SDL_Event *event, bool * bDraw){
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::HandleMouseEvent Start\n", GetType() );

		SDL_Iterator<SDL_Widget> pos; 
		GetIterator<SDL_Widget>( &pos );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Widget * pItem = dynamic_cast<SDL_Widget *>( pos.GetCurrentItem() );
			if ( pItem && pItem->GetVisible() )
				if ( pItem->HandleMouseEvent( event, bDraw ) )
					return true;
		}

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

		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::HandleMouseEvent End\n", GetType() );
		return bHandled;
	}

 	virtual bool HandleKeyEvent(const SDL_Event *event, bool * bDraw){
		switch ( event->type )
		{
			case SDL_KEYDOWN:			return OnKeyDown( &event->key, bDraw );
			case SDL_KEYUP:				return OnKeyUp( &event->key, bDraw );
		}

		return false;
	}

// 子图元操作
public:
    /// 添加一个图元
    virtual bool Add( SDL_Glyph * g )
    {
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Add Start\n", GetType() );

		SDL_Container::Add( g );
		SDL_Widget * w = dynamic_cast<SDL_Widget *>(g);
		add( w );

 		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Add End\n", GetType() );
       return true;
    }

    /// 删除一个图元
    virtual void Remove( SDL_Glyph * g )
    {
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Remove Start\n", GetType() );

        assert( g );
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( g == *pos ) {
                m_aChildren.erase( pos );
		
				SDL_Widget * w = dynamic_cast<SDL_Widget *>(g);
				remove( w );
			}
		}

		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Remove End\n", GetType() );
    }

    /// 清除所有子图元
    virtual void Clear()
    {
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Clear Start\n", GetType() );

		for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			SDL_Widget * w = dynamic_cast<SDL_Widget *>( *pos );
			remove( w );
			(*pos)->Release();
		}
		m_aChildren.clear();

		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Clear End\n", GetType() );
    }

	//template< class T >
	//void GetIterator( SDL_Iterator * iter, bool r = false )	{
	//	if ( !r )
	//	{
	//        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
	//		{
	//			SDL_Widget * w = dynamic_cast<SDL_Widget *>( *pos );
	//			if ( w && w->GetVisible() )
	//				iter->Add( ( SDL_Glyph * )w->GetObj() );
	//		}
	//	}
	//	else
	//	{
	//		for ( std::vector<SDL_Widget *>::reverse_iterator pos = m_aChildren.rbegin(); pos != m_aChildren.rend(); pos ++ )
	//		{
	//			SDL_Widget * w = dynamic_cast<SDL_Widget *>( *pos );
	//			if ( w && w->GetVisible() )
	//				iter->Add( ( SDL_Glyph * )w->GetObj() );
	//		}
	//	}
	//}

public:
	virtual void RecalcLayout()	{ 
		if ( !GetLayout() )
			return;

		GetLayout()->Update( this, &GetBounds() );
		RedrawWidget();
	}

	virtual void RedrawWidget()	{
		SDL_Event	event;
		event.type = SDL_VIDEOEXPOSE;
		SDL_PushEvent( &event );
	}

	///
    virtual SDL_Widget * GetParent(){ return m_pParent;	}
    virtual void SetParent( SDL_Widget * parent ){ m_pParent = parent; }

	virtual SDL_Widget * SetFocus();

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
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
	//virtual void DrawWidget( SDL_Surface * screen ) {
	//	
	//}
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
	SDL_Widget *	m_pParent;
	bool			m_bHover;
	bool			m_bVisible;
	bool			m_bCheck;
};

#endif // SDL_WIDGET_H_INCLUDED
