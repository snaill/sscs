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

/// @brief 所有界面布局的基类，并提供对布局内对象的访问
class SDL_Container : public SDL_Glyph
{
// 方法
public:
    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen )
    {
		SDL_Rect	rcOld;
		SDL_GetClipRect( screen, &rcOld );
		SDL_SetClipRect( screen, &GetBounds() );

		for ( size_t i = 0; i < GetCount(); i ++ )
		{
			SDL_Glyph * pItem = GetItem(i);
			if ( pItem->IsShow() )
				pItem->Draw( screen );
		}

		SDL_SetClipRect( screen, &rcOld );
    }

    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event, bool * bDraw)
	{
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( (*pos)->IsShow() )
			{
				if ( (*pos)->HandleEvent( event, bDraw ) )
					return true;
			}
		}
		return false;
	}


// 子图元操作
public:
    /// 添加一个图元
    virtual bool Add( SDL_Glyph * g )
    {
        assert( g );
        m_aChildren.push_back( g );
        return true;
    }

    /// 删除一个图元
    virtual void Remove( SDL_Glyph * g )
    {
        assert( g );
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            if ( g == *pos )
                m_aChildren.erase( pos );
    }

    /// 清除所有子图元
    virtual void Clear()
    {
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
           (*pos)->Release();
        m_aChildren.clear();
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
    /// 构造函数为保护类型，说明该基类不能直接创建
    SDL_Container()            { }
    virtual ~SDL_Container()   {
        Clear();
    }

protected:
    /// 子图元列表
	std::vector<SDL_Glyph *>	m_aChildren;
};

#endif // SDL_CONTAINER_H_INCLUDED
