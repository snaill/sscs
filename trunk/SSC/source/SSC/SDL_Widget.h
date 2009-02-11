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

#include "SDL_Object.h"
#include "SDL_Layout.h"
#include "sigslot.h"
#include "Iterator.h"

/// @brief 控件类的基类
class SDL_Widget : public SDL_Object, public SDL_BoundingBox, public sigslot::has_slots<>
{
public:
	sigslot::signal1<SDL_Widget *>		click;

public:
	SDL_Widget() : m_pLayout(0), m_nLayoutProperty(0), m_bHover(false), m_bVisible( true ), 
		m_pParent(0), m_bCheck( false ), m_bSelected( false ) {}

	~SDL_Widget() {
		if ( m_pLayout )
			m_pLayout->Release();
				
		disconnect_all();
        Clear();
	}

	virtual const char * GetType() { return "widget"; }

	/// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
	virtual SDL_Size GetPreferedSize()	{
		if ( GetLayout() )
			return GetLayout()->GetPreferedSize( this );

		return SDL_Size( 0, 0 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc ){
		if ( GetLayout() )
			GetLayout()->Update( this, lprc );
		
		m_pt.x = lprc->x;
		m_pt.y = lprc->y;
		m_sz.w = lprc->w;
		m_sz.h = lprc->h;
	}

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen )
	{
		SDL_Rect	rcOld;
		SDL_GetClipRect( screen, &rcOld );
		SDL_SetClipRect( screen, &And( rcOld ) );

		DrawWidget( screen );
		Iterator * pos = GetIterator();
		for ( pos->First(); !pos->IsDone(); pos->Next() )
		{
			SDL_Widget * pItem = pos->GetCurrentItem();
			pItem->Draw( screen );
		}
		pos->Release();


		SDL_SetClipRect( screen, &rcOld );
	}

 	virtual bool HandleMouseEvent(const SDL_Event *event, bool * bDraw){
		bool bHandled = false;
		for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( (*pos)->GetVisible() )
				bHandled =(*pos)->HandleMouseEvent( event, bDraw );
		}

		if ( bHandled )
			return true;

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
    virtual bool Add( SDL_Widget * g )
    {
        assert( g );
		g->SetParent( this );
        m_aChildren.push_back( g );
        return true;
    }

    /// 删除一个图元
    virtual void Remove( SDL_Widget * g )
    {
        assert( g );
        for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( g == *pos ) {
				(*pos)->click.disconnect( this );
                m_aChildren.erase( pos );
			}
		}
    }

    /// 清除所有子图元
    virtual void Clear()
    {
        for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
           (*pos)->Release();
        m_aChildren.clear();
    }

	Iterator * GetIterator( bool r = false )	{
		if ( !r )
			return new SDL_Iterator( &m_aChildren );
		else
			return new SDL_IteratorR( &m_aChildren );
	}

    /// 获取子图元个数
    virtual size_t	GetCount()
    {
        return m_aChildren.size();
    }

    /// 获取对应下标的子图元
    virtual SDL_Widget * GetItem( size_t index )
    {
		if ( index < 0 || index >= GetCount() )
			return NULL;

        return m_aChildren[index];
    }

    virtual int GetItemID( SDL_Widget * pItem )
    {
		for ( size_t i = 0; i < GetCount(); i ++ )
			if ( pItem == m_aChildren[ i ] )
				return i;

		return -1;
    }

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
    virtual SDL_Layout * GetLayout(){ return m_pLayout;	}
    virtual void SetLayout( SDL_Layout * layout ){ m_pLayout = layout; }
    virtual int GetLayoutProperty(){ return m_nLayoutProperty;	}
    virtual void SetLayoutProperty( int layoutProperty ){ m_nLayoutProperty = layoutProperty; }
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
	bool GetSelected()				{ return m_bSelected;		}
	void SetSelected( bool bSelected )	{ m_bSelected = bSelected;	}
	bool GetHover()					{ return m_bHover;		}
	void SetHover( bool bHover )	{ m_bHover = bHover;	}

protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen ) {}
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
    /// 子图元列表
	std::vector<SDL_Widget *>	m_aChildren;
    /// 客户对象，允许是图元或布局
	SDL_Layout *	m_pLayout;
	SDL_Widget *	m_pParent;
	int				m_nLayoutProperty;
	bool			m_bHover;
	bool			m_bVisible;
	bool			m_bCheck;
	bool			m_bSelected;
};

#endif // SDL_WIDGET_H_INCLUDED
