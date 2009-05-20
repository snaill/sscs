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

/// @brief �ؼ���Ļ���
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
		log_f_start( "HandleMouseEvent" );

		if ( GetLayout() )
			GetLayout()->HandleMouseEvent( this, event, bDraw );

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

// ��ͼԪ����
public:
    /// ����һ��ͼԪ
    virtual bool Add( SDL_Glyph * g )
    {
		log_f_start( "Add" );

		SDL_Container::Add( g );
		SDL_Widget * w = dynamic_cast<SDL_Widget *>(g);
		add( w );

		log_f_end( "Add" );
       return true;
    }

    /// ɾ��һ��ͼԪ
    virtual void Remove( SDL_Glyph * g )
    {
		log_f_start( "Remove" );

        assert( g );
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( g == *pos ) {
                m_aChildren.erase( pos );
		
				SDL_Widget * w = dynamic_cast<SDL_Widget *>(g);
				remove( w );
			}
		}

		log_f_end( "Remove" );
    }

    /// ���������ͼԪ
    virtual void Clear()
    {
		log_f_start( "Clear" );

		for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			SDL_Widget * w = dynamic_cast<SDL_Widget *>( *pos );
			remove( w );
			(*pos)->Release();
		}
		m_aChildren.clear();

		log_f_end( "Clear" );
    }

public:
	virtual void RecalcLayout( bool bDraw = true )	{ 
		if ( !GetLayout() )
			return;

		GetLayout()->Update( this, &GetBounds() );
		if ( bDraw )
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
    /// @brief ���Ƶ�ǰͼԪ
    /// @param screen	��ĻSurface
	//virtual void DrawWidget( SDL_Surface * screen ) {
	//	
	//}
    void Draw3DRect( SDL_Surface *screen, SDL_Rect rect, SDL_Color clrTopLeft, SDL_Color clrBottomRight );

// �¼�
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