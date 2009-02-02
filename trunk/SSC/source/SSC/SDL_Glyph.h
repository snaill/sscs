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

#ifndef SDL_GLYPH_H_INCLUDED
#define SDL_GLYPH_H_INCLUDED

#include "SDL_Object.h"

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_Glyph : public SDL_Object, public SDL_BoundingBox
{

// 基本属性
public:
    /// @brief 获取图元所需的最小区域
    /// @param w 返回的矩形宽度
    /// @param h 返回的矩形宽度
    virtual SDL_Size GetPreferedSize() = 0;


  //  /// @brief 获取图元所在区域
  //  /// @param lprc 返回的矩形位置
  //  virtual SDL_Rect GetBounds()
  //  {
		//SDL_Rect	rc;
		//rc.x = m_x;
		//rc.y = m_y;
		//rc.w = m_w;
		//rc.h = m_h;
		//return rc;
  //  }

  //  /// @brief 设置图元所在区域
  //  /// @param lprc 欲设置矩形位置
  //  virtual void SetBounds( const SDL_Rect * lprc )
  //  {
		//m_x = lprc->x;
		//m_y = lprc->y;
		//m_w = lprc->w;
		//m_h = lprc->h;
  //  }

// 方法
public:
    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen ) = 0;

    ///// @brief 测试相应点是否在图元范围内
    ///// @param x 屏幕坐标x
    ///// @param y 屏幕坐标y
    //virtual bool HitTest( int x, int y )
    //{
    //    if ( ( x < m_x || x > x + m_w ) || ( y < m_y || y > m_y + m_h ) )
    //        return false;

    //    return true;
    //}

    /// @brief 发送事件
    /// @param evnet 事件信息
	virtual bool HandleEvent(const SDL_Event *event, bool * bDraw ) = 0;

protected:
    /// 构造函数为保护类型，说明该基类不能直接创建
	SDL_Glyph()			{}

    virtual ~SDL_Glyph(){}
};

#endif //!SDL_GLYPH_H_INCLUDED
