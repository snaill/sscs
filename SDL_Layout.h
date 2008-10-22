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

/// @brief 所有界面布局的基类，并提供对布局内对象的访问
class SDL_Layout : public SDL_Glyph
{
// 基本属性
public:
	virtual const char * GetType()				{ return "boxlayout"; }

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc )
    {
        if ( m_rc.w != lprc->w || m_rc.h != lprc->h )
        {
            SDL_Glyph::SetBounds( lprc );
            ReCalc( );
        }
        else
        {
            if ( m_rc.x != lprc->x || m_rc.y != lprc->y )
            {
                // 如果只是位移，则更新位移偏移量
                SDL_Rect    rect;
                Uint16      xOff = lprc->x - m_rc.x;
                Uint16      yOff = lprc->y - m_rc.y;
                for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
                {
                    (*pos)->GetBounds( &rect );
                    rect.x += xOff;
                    rect.y += yOff;
                    (*pos)->SetBounds( &rect );
                }
            }
        }
    }

// 方法
public:
    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen )
    {
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            (*pos)->Draw( screen );
    }


    /// @brief 测试相应点是否在图元范围内
    /// @param x 屏幕坐标x
    /// @param y 屏幕坐标y
    virtual bool HitTest( int x, int y )
    {
//        if ( ( x < m_rc.x || x > m_rc.x + m_rc.w )
//                || ( y < m_rc.y || y > m_rc.y + m_rc.h ) )
            return false;

//        return true;
    }

    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event)
	{
	    bool bHandled = false;
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            if ( (*pos)->HandleEvent( event ) )
                bHandled = true;
	    return bHandled;
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
    virtual size_t	GetChildCount()
    {
        return m_aChildren.size();
    }

    /// 获取对应下标的子图元
    virtual SDL_Glyph * GetChild( int index )
    {
        return m_aChildren[index];
    }

protected:
    /// 构造函数为保护类型，说明该基类不能直接创建
    SDL_Layout()            { }
    virtual ~SDL_Layout()	{
        Clear();
    }

    virtual void ReCalc( ) = 0;

protected:
    /// 子图元列表
	std::vector<SDL_Glyph *>	m_aChildren;
};

#endif // SDL_LAYOUT_H_INCLUDED
