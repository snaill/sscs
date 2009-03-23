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

#ifndef SDL_OBJECT_H_INCLUDED
#define SDL_OBJECT_H_INCLUDED

#include <assert.h>
#include <vector>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>

#define   MAX(a,   b)     (((a)   >   (b))   ?   (a)   :   (b))
#define   MIN(a,   b)     (((a)   <   (b))   ?   (a)   :   (b))

class SDL_Size
{
public:
	SDL_Size() {
		w = h = 0;
	}

	SDL_Size(int w1, int h1) {
		w = w1;
		h = h1;
	}
public:
	Uint16	w, h;
};

class SDL_Point
{
public:
	SDL_Point() {
		x = y = 0;
	}

	SDL_Point(int x1, int y1) {
		x = x1;
		y = y1;
	}
public:
	Sint16	x, y;
};

class SDL_BoundingBox
{
public:
	SDL_Point		m_pt;
	SDL_Size		m_sz;

public:
	SDL_BoundingBox() {}

	/// @brief 获取图元所在区域
    /// @param lprc 返回的矩形位置
    virtual SDL_Rect GetBounds()
    {
		SDL_Rect	rc;
		rc.x = m_pt.x;
		rc.y = m_pt.y;
		rc.w = m_sz.w;
		rc.h = m_sz.h;
		return rc;
    }

    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc )
    {
		m_pt.x = lprc->x;
		m_pt.y = lprc->y;
		m_sz.w = lprc->w;
		m_sz.h = lprc->h;
    }

    /// @brief 测试相应点是否在图元范围内
    /// @param x 屏幕坐标x
    /// @param y 屏幕坐标y
    virtual bool IsIn( int x, int y )
    {
        if ( ( x < m_pt.x || x > m_pt.x + m_sz.w ) || ( y < m_pt.y || y > m_pt.y + m_sz.h ) )
            return false;

        return true;
    }

	virtual SDL_Rect And( SDL_Rect	rc )	{
		SDL_Rect	rcRet = GetBounds();
		rcRet.x = MAX( m_pt.x, rc.x );
		rcRet.y = MAX( m_pt.y, rc.y );
		rcRet.w = MIN( m_pt.x + m_sz.w, rc.x + rc.w ) < rcRet.x ? 0 : MIN( m_pt.x + m_sz.w, rc.x + rc.w ) - rcRet.x;
		rcRet.h = MIN( m_pt.y + m_sz.h, rc.y + rc.h ) < rcRet.y ? 0 : MIN( m_pt.y + m_sz.h, rc.y + rc.h ) - rcRet.y;
		return rcRet;
	}

};

#define LOG_LEVEL	SDL_Object::warning

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_Object
{
protected:
	enum {
		debug = 0,
		info = 100,
		warning = 200,
		error = 300,
		fatal = 400
	};
protected:
    /// 图元计数，用来记录图元被引用的次数，
    /// 初始为1，为0时图元被真正释放
    Uint16		m_ref;

// 基本属性
public:
    /// @brief 获取图元类别
    /// @return 返回的图元类别
    virtual const char * GetType() = 0;

    /// 获取图元引用，图元计数加1
    template<class T> T * GetObj()
    {
        m_ref ++;
        return dynamic_cast<T *>(this);
    }

    /// 释放图元，只有在计数为0的情况下，图元才会被真的释放
    virtual void Release()
    {
        m_ref --;
        if ( !m_ref )
			delete this;
    }

protected:
	void log_f_start( const char * name )	{
		char cLog[4096];
		sprintf( cLog, "%s::%s start", GetType(), name );
		log( info, cLog );
	}
	
	void log_f_end( const char * name )	{
		char cLog[4096];
		sprintf( cLog, "%s::%s end", GetType(), name );
		log( info, cLog );
	}

	void log( int nLevel, const char* log )	{
		if ( nLevel < LOG_LEVEL )
			return;

		time_t t = time(0); 
		struct tm * time = localtime(&t);
		fprintf( stdout, "[%d-%d-%d %d:%d:%d] %s\n", time->tm_year, time->tm_mon, time->tm_yday, time->tm_hour, time->tm_min, time->tm_sec, log );
	}

protected:
    /// 构造函数为保护类型，说明该基类不能直接创建
	SDL_Object() : m_ref(1)	{}

    virtual ~SDL_Object()	{}
};

#endif //!SDL_OBJECT_H_INCLUDED
