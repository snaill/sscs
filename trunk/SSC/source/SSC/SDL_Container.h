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

#ifndef SDL_CONTAINER_H_INCLUDED
#define SDL_CONTAINER_H_INCLUDED

#include "SDL_Glyph.h"
#include "SDL_Layout.h"
#include "SDL_Iterator.h"

/// @brief 控件类的基类
class SDL_Container : public SDL_Glyph
{
public:
	SDL_Container() : m_pLayout(0) {}

	virtual ~SDL_Container() {
		log_f_start( "~SDL_Container" );

		if ( m_pLayout )
			m_pLayout->Release();
				
        Clear();
		log_f_end( "~SDL_Container" );
	}

	virtual const char * GetType() { return "SDL_Container"; }

	/// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
	virtual SDL_Size GetPreferedSize()	{
		log_f_start( "GetPreferedSize" );

		if ( GetLayout() )
			return GetLayout()->GetPreferedSize( this );

		log_f_end( "GetPreferedSize" );
		return SDL_Size( 0, 0 );
	}

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc ){
		SDL_Glyph::SetBounds( lprc );

		if ( GetLayout() )
			GetLayout()->Update( this, lprc );
	}

// 子图元操作
public:
    /// 添加一个图元
    virtual bool Add( SDL_Glyph * g )
    {
		log_f_start( "Add" );

		assert( g );
        m_aChildren.push_back( g );

		log_f_end( "Add" );
       return true;
    }

    /// 删除一个图元
    virtual void Remove( SDL_Glyph * g )
    {
		log_f_start( "Remove" );

        assert( g );
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( g == *pos ) {
                m_aChildren.erase( pos );
			}
		}

		log_f_end( "Remove" );
    }

    /// 清除所有子图元
    virtual void Clear()
    {
		log_f_start( "Clear" );

		for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			(*pos)->Release();
		}
		m_aChildren.clear();

		log_f_end( "Clear" );
    }

	template < class T >	
	void GetIterator( SDL_Iterator<T> * iter, bool r = false )	{
		if ( !r )
		{
	        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
			{
				T * pItem = dynamic_cast<T *>( *pos );
				if ( pItem )
					iter->Add( pItem->GetObj<T>() );
			}
		}
		else
		{
			for ( std::vector<SDL_Glyph *>::reverse_iterator pos = m_aChildren.rbegin(); pos != m_aChildren.rend(); pos ++ )
			{
				T * pItem = dynamic_cast<T *>( *pos );
				if ( pItem )
					iter->Add( pItem->GetObj<T>() );
			}
		}
	}

    /// 获取子图元个数
    virtual size_t	GetCount()
    {
        return m_aChildren.size();
    }

    /// 获取对应下标的子图元
    virtual SDL_Glyph * GetItem( size_t index )
    {
		if ( index < 0 || index >= GetCount() )
			return NULL;

        return m_aChildren[index];
    }

    virtual int GetItemID( SDL_Glyph * pItem )
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
//		RedrawWidget();
	}

	virtual void RedrawWidget()	{
		SDL_Event	event;
		event.type = SDL_VIDEOEXPOSE;
		SDL_PushEvent( &event );
	}

	///
    virtual SDL_Layout * GetLayout(){ 
		if ( !m_pLayout )
			m_pLayout = DefaultLayout();
		return m_pLayout;	
	}
    virtual void SetLayout( SDL_Layout * layout ){ m_pLayout = layout; }

protected:
	virtual SDL_Layout * DefaultLayout() { return 0; }

    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc ) {
		if ( GetLayout() )
			GetLayout()->DrawWidget( this, screen );
	}

protected:
    /// 子图元列表
	std::vector<SDL_Glyph *>	m_aChildren;
    /// 客户对象，允许是图元或布局
	SDL_Layout *	m_pLayout;
};

#endif // SDL_CONTAINER_H_INCLUDED
