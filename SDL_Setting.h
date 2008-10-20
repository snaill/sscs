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
    Uint32 align_left       :1;	/* �Ƿ������ */
    Uint32 align_right      :1;	/* �Ƿ��Ҷ��� */
    Uint32 align_top        :1; /* �Ƿ񶥱߶��� */
    Uint32 align_bottom     :1; /* �Ƿ�ױ߶��� */
    Uint32 style_blod       :1;	/* �Ƿ���� */
    Uint32 style_italic     :1;	/* �Ƿ�б�� */
    Uint32 style_underline  :1;	/* �Ƿ��»��� */
    Uint32 quality_high     :1; /* �Ƿ������ */
    Uint32 transparent      :1; /* �Ƿ�͸�� */
    Uint32 UnusedBits       :7;
    Uint32 size             :16;/* �����С */
    SDL_Color   crBack;         /* ����ɫ */
    SDL_Color   crText;         /* ǰ��ɫ */
} SDL_TextStatus;

typedef struct {
    Uint8   type;
    Uint32  mouse_on        :1;	    /* �Ƿ���������� */
    Uint32  mouse_lbutton   :1;	    /* �Ƿ����������� */
    Uint32  mouse_mbutton   :1;	    /* �Ƿ�����м����� */
    Uint32  mouse_rbutton   :1;	    /* �Ƿ�����Ҽ����� */
    Uint32  UnusedBits      :28;
} SDL_WidgetStatus;

typedef union {
    Uint8               type;
    SDL_TextStatus      text;
    SDL_WidgetStatus    widget;
} SDL_Status;

/* Layout enumerations */

// @brief ������
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
	// ��ȡ��ʱ
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
