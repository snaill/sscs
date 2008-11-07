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

#ifndef SDL_SETTING_H_INCLUDED
#define SDL_SETTING_H_INCLUDED

#include "SDL_DC.h"

/* Status enumerations */
typedef enum {
       SDL_STATUS_UNKNOWN = 0,	    /* Unused (do not remove) */
       SDL_STATUS_WIDGET
} SDL_StatusType;

typedef struct {
    Uint8   type;
    Uint32  mouse_on        :1;	    /* 是否鼠标在上面 */
    Uint32  mouse_lbutton   :1;	    /* 是否鼠标左键按下 */
    Uint32  mouse_mbutton   :1;	    /* 是否鼠标中键按下 */
    Uint32  mouse_rbutton   :1;	    /* 是否鼠标右键按下 */
    Uint32  UnusedBits      :28;
} SDL_WidgetStatus;

typedef union {
    Uint8               type;
    SDL_WidgetStatus    widget;
} SDL_Status;

/* Layout enumerations */
typedef enum {
       SDL_LAYOUT_UNKNOWN = 0,	    /* Unused (do not remove) */
       SDL_LAYOUT_BOX
} SDL_LayoutType;

typedef enum {
       SDL_DOCK_MIN = 0,	    /* Unused (do not remove) */
       SDL_DOCK_FIXED,
       SDL_DOCK_FILL
} SDL_DockType;

typedef struct {
    Uint8   type;
    Uint8   dock;
} SDL_BoxLayoutObject;

typedef union {
    Uint8                   type;
    SDL_BoxLayoutObject     box;
} SDL_LayoutObject;

// @brief 设置类
class SDL_Setting
{
protected:
	static SDL_Setting * m_this;

public:
    SDL_Setting()   {
    }

    ~SDL_Setting()  {
    }
	// 获取当时
	static SDL_Setting * Get()	{
		if ( !m_this )
			m_this = new SDL_Setting();

		return m_this;
	}

	void Release()      {
        delete this;
	}

    SDL_DC * GetDC()    {
        return &m_dc;
    }

protected:
    SDL_DC      m_dc;
};

#endif // SDL_SETTING_H_INCLUDED
