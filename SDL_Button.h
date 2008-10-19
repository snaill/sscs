#ifndef SDL_BUTTON_H_INCLUDED
#define SDL_BUTTON_H_INCLUDED

#include "SDL_Widget.h"

class SDL_Button :	public SDL_Widget
{
public:
	SDL_Button( const char * );
	virtual ~SDL_Button(void);

	virtual const char * GetType()				{ return "button"; }

    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
    virtual void Draw( SDL_Surface * screen );

    /// @brief �����¼�
    /// @param evnet �¼���Ϣ
 	virtual bool HandleEvent(const SDL_Event *event);

public:
    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void SetBounds( const SDL_Rect * lprc );

protected:
    void OnMouseEnter();

    void OnMouseLeave();
};

#endif //!SDL_BUTTON_H_INCLUDED
