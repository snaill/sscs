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

#include <SDL_ttf.h>

/* Status enumerations */
typedef enum {
       SDL_NOSTATUS = 0,	    /* Unused (do not remove) */
       SDL_TEXTSTATUS,
       SDL_WIDGETSTATUS
} SDL_StatusType;

typedef struct {
    Uint8    type;
    Uint32 align_left       :1;	/* 是否左对齐 */
    Uint32 align_right      :1;	/* 是否右对齐 */
    Uint32 align_top        :1; /* 是否顶边对齐 */
    Uint32 align_bottom     :1; /* 是否底边对齐 */
    Uint32 style_blod       :1;	/* 是否粗体 */
    Uint32 style_italic     :1;	/* 是否斜体 */
    Uint32 style_underline  :1;	/* 是否下划线 */
    Uint32 quality_high     :1; /* 是否高质量 */
    Uint32 transparent      :1; /* 是否透明 */
    Uint32 UnusedBits       :7;
    Uint32 size             :16;/* 字体大小 */
    SDL_Color   crBack;         /* 背景色 */
    SDL_Color   crText;         /* 前景色 */
} SDL_TextStatus;

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
    SDL_TextStatus      text;
    SDL_WidgetStatus    widget;
} SDL_Status;

/* Layout enumerations */

// @brief 设置类
class SDL_Setting
{
protected:
	static SDL_Setting * m_this;

public:
    SDL_Setting()   {
       TTF_Init();
    }

    ~SDL_Setting()  {
       TTF_Quit();
    }
	// 获取当时
	static SDL_Setting * Get()	{
		if ( !m_this )
			m_this = new SDL_Setting();

		return m_this;
	}

	void Release() {
        delete this;
	}
};

#endif // SDL_SETTING_H_INCLUDED
