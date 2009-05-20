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

#ifndef SDL_LAYOUT_H_INCLUDED
#define SDL_LAYOUT_H_INCLUDED

#include "SDL_Glyph.h"
#include "SDL_Layout.h"
#include "SDL_Iterator.h"
#include "sigslot.h"

/// @brief 所有界面布局的基类，实现固定布局，即对内部控件不做处理
class SDL_Layout : public SDL_Glyph
{
public:
	sigslot::signal1<SDL_Glyph *>		add;
	sigslot::signal1<SDL_Glyph *>		remove;

// 基本属性
public:
	virtual SDL_Size GetPreferedSize( ) = 0;

 	virtual bool HandleMouseEvent( const SDL_Event *event, bool * bDraw );

// 子图元操作
public:
    /// 添加一个图元
    virtual bool Add( SDL_Glyph * g )
    {
		log_f_start( "Add" );

		m_aChildren.push_back(g);

		SDL_Glyph * w = dynamic_cast<SDL_Glyph *>(g);
		add( w );

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
		
				SDL_Glyph * w = dynamic_cast<SDL_Glyph *>(g);
				remove( w );
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
			SDL_Glyph * w = dynamic_cast<SDL_Glyph *>( *pos );
			remove( w );
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

protected:
    /// @brief 绘制当前图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc );

protected:
    /// 子图元列表
	std::vector<SDL_Glyph *>	m_aChildren;
 
protected:
	SDL_Layout()	{}

	virtual ~SDL_Layout() {
		log_f_start( "~SDL_Layout" );

		Clear();
		
		log_f_end( "~SDL_Layout" );
	}
};

#endif // SDL_LAYOUT_H_INCLUDED
