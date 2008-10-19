#ifndef SDL_SETTING_H_INCLUDED
#define SDL_SETTING_H_INCLUDED

#include <SDL_ttf.h>

/* Event enumerations */
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
