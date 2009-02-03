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

#ifndef SDL_LISTBOX_H_INCLUDED
#define SDL_LISTBOX_H_INCLUDED

#include "SDL_Widget.h"
#include "SDL_ListBoxItem.h"
#include "SDL_ScrollBoxLayout.h"

/// @brief 控件类的基类
class SDL_ListBox : public SDL_Widget
{
// 基本属性
public:
	SDL_ListBox()		{
		m_curIndex = -1;
		m_pLayout = new SDL_ScrollBoxLayout();
	}

	virtual ~SDL_ListBox()	{
		if ( m_imgList )
			delete m_imgList;
	}

	virtual const char * GetType()				{ return "listbox"; }

	virtual SDL_Size GetPreferedSize()	{
		SDL_Size	sz( 0, 0 );
		for ( int i = 0; i < GetCount(); i ++ )
		{
			SDL_Size size = GetItem(i)->GetPreferedSize();
			sz.h += size.h;
			if ( sz.w < size.w )
				sz.w = size.w;
		}

		return sz;
	}
public:
	SDL_ListBoxItem * AddItem( const char * text, const char * remark, int iImage )
	{
		SDL_ListBoxItem * pItem = new SDL_ListBoxItem( text, remark, iImage );
		pItem->select.connect( this, &SDL_ListBox::OnItemSelected );
		pItem->SetImageList( m_imgList );
		
		Add( pItem );
		return pItem;
	}

	void SetImageList( SDL_ImageList * imgList )	{
		m_imgList = imgList;
	}

protected:
	inline SDL_ScrollBoxLayout * GetCurrentLayout()	{ return (SDL_ScrollBoxLayout *)GetLayout(); }

	void OnItemSelected( SDL_ListBoxItem * pItem ) {
		SelectItem( GetItemID( pItem ) );

		SDL_Event	event;
		event.type = SDL_VIDEOEXPOSE;

		SDL_PushEvent( &event );
	}

	virtual bool OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw ) {
		switch ( key->keysym.sym )
		{
		case SDLK_UP:
			if ( 0 != m_curIndex )
			{
				if ( 0 > m_curIndex )
					SelectItem( GetCurrentLayout()->GetBottomIndex( this ) );
				else
				{
					SelectItem( m_curIndex - 1 );
				}
				*bDraw = true;
			}
			break;
		case SDLK_DOWN:
			if ( GetCount() - 1 != m_curIndex )
			{
				if ( 0 > m_curIndex )
					SelectItem( 0 );
				else
				{
					SelectItem( m_curIndex + 1 );
				}
				*bDraw = true;
			}
			break;		
		default:
			return false;
		}

		return true;
	}

    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
    virtual void DrawWidget( SDL_Surface * screen ){}

	void SelectItem( int iItem )	{
		if ( iItem == m_curIndex )
			return;

		SDL_ListBoxItem * pItem = ( SDL_ListBoxItem * )GetItem( m_curIndex );
		if ( pItem )
			pItem->SetCheck( false );
		
		pItem = ( SDL_ListBoxItem * )GetItem( iItem );
		if ( pItem )
			pItem->SetCheck( true );

		m_curIndex = iItem;

		SDL_Rect	rc = GetItem( iItem )->GetBounds();
		if ( rc.y < m_pt.y )
			GetCurrentLayout()->Scroll( m_pt.y - rc.y, this );
		if ( rc.y + rc.h > m_pt.y + m_sz.h )
			GetCurrentLayout()->Scroll( m_pt.y + m_sz.h - rc.h - rc.y, this );
	}

protected:
	Sint16				m_curIndex;
	SDL_ImageList *		m_imgList;	
};

#endif // SDL_LISTBOX_H_INCLUDED
