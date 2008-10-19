#ifndef SDL_GLYPH_H_INCLUDED
#define SDL_GLYPH_H_INCLUDED

#include "SDL_Setting.h"
#include <assert.h>
#include <vector>
#include <SDL.h>

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_Glyph
{
protected:
    /// 图元计数，用来记录图元被引用的次数，
    /// 初始为1，为0时图元被真正释放
    int		m_nRef;

    /// 图元的矩形范围
    SDL_Rect	m_rc;

    /// 子图元列表
	std::vector<SDL_Glyph *>	m_aChildren;

// 基本属性
public:
    virtual ~SDL_Glyph()					{}

    /// @brief 获取图元类别
    /// @return 返回的图元类别
    virtual const char * GetType() = 0;

    /// 获取图元引用，图元计数加1
    virtual SDL_Glyph * GetObject()
    {
        m_nRef ++;
        return this;
    }

    /// 释放图元，只有在计数为0的情况下，图元才会被真的释放
    virtual void Release()
    {
        m_nRef --;
        if ( !m_nRef )
        {
            Clear();
            delete this;
        }
    }

    /// @brief 获取图元所在区域
    /// @param lprc 返回的矩形位置
    virtual void GetBounds( SDL_Rect * lprc )
    {
        memcpy( lprc, &m_rc, sizeof( SDL_Rect ) );
    }

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc )
    {
        memcpy( &m_rc, lprc, sizeof( SDL_Rect ) );
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
        if ( ( x < m_rc.x || x > m_rc.x + m_rc.w )
                || ( y < m_rc.y || y > m_rc.y + m_rc.h ) )
            return false;

        return true;
    }

    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event)
	{
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            if ( (*pos)->HandleEvent( event ) )
                return true;
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
    SDL_Glyph() : m_nRef(1)
    {
        memset( &m_rc, 0x00, sizeof( SDL_Rect ) );
    }

    ///
    void DrawPixel( SDL_Surface *screen, int x, int y, Uint32 color );
    void DrawLine( SDL_Surface *screen, int x, int y, int x2, int y2, Uint32 color );
    void DrawRgn( SDL_Surface *screen, int* xs, int* ys, int count, Uint32 color, bool bClose );
    void DrawRect( SDL_Surface *screen, SDL_Rect rect, Uint32 color );
    void Draw3DRect( SDL_Surface *screen, SDL_Rect rect, Uint32 clrTopLeft, Uint32 clrBottomRight );
};

#endif //!SDL_GLYPH_H_INCLUDED
