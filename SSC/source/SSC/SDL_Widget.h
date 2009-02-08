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

/// @brief �ؼ���Ļ���
class SDL_Widget : public SDL_Container, public sigslot::has_slots<>
{
public:
	SDL_Widget() : m_pLayout(0), m_nLayoutProperty(0), m_bHover(false) {}

	~SDL_Widget() {
		if ( m_pLayout )
			m_pLayout->Release();
				
		disconnect_all();
	}

	virtual const char * GetType() { return "widget"; }

	/// @brief ��ȡͼԪ�������С����
    /// @param w ���صľ��ο���
    /// @param h ���صľ��ο���
	virtual SDL_Size GetPreferedSize()	{
		if ( GetLayout() )
			return GetLayout()->GetPreferedSize( this );

		return SDL_Size( 0, 0 );
	}

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void SetBounds( const SDL_Rect * lprc ){
		if ( GetLayout() )
			GetLayout()->Update( this, lprc );
		
		SDL_Glyph::SetBounds( lprc );
	}

    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
    virtual void Draw( SDL_Surface * screen )
	{
		SDL_Rect	rcOld;
		SDL_GetClipRect( screen, &rcOld );
		SDL_SetClipRect( screen, &And( rcOld ) );

		DrawWidget( screen );
		SDL_Container::Draw( screen );

		SDL_SetClipRect( screen, &rcOld );
	}

 	virtual bool HandleMouseEvent(const SDL_Event *event, bool * bDraw){
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

		if ( bHandled )
			return true;

		return SDL_Container::HandleMouseEvent(event, bDraw );
	}

 	virtual bool HandleKeyEvent(const SDL_Event *event, bool * bDraw){
		switch ( event->type )
		{
			case SDL_KEYDOWN:			return OnKeyDown( &event->key, bDraw );
			case SDL_KEYUP:				return OnKeyUp( &event->key, bDraw );
		}

		return false;
	}

	virtual void Show( bool bShow ) { 
		if ( m_bShow == bShow )
			return;

		m_bShow = bShow;
		if ( GetParent() )
			( ( SDL_Widget * )GetParent() )->RecalcLayout();
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
	virtual SDL_Glyph * SetFocus();

protected:
    /// @brief ���Ƶ�ǰͼԪ
    /// @param screen	��ĻSurface
	virtual void DrawWidget( SDL_Surface * screen ) {}
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
    /// �ͻ�����������ͼԪ�򲼾�
	SDL_Layout *	m_pLayout;
	int				m_nLayoutProperty;
	bool			m_bHover;
};

#endif // SDL_WIDGET_H_INCLUDED