#ifndef SDL_BUTTON_H_INCLUDED
#define SDL_BUTTON_H_INCLUDED

#include "SDL_Widget.h"

class SDL_Button :	public SDL_Widget
{
public:
	SDL_Button( const char * );
	virtual ~SDL_Button(void);

	virtual const char * GetType()				{ return "button"; }

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
    virtual void Draw( SDL_Surface * screen );

    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event);

public:
    /// @brief 设置图元所在区域
    /// @param lprc 欲设置矩形位置
    virtual void SetBounds( const SDL_Rect * lprc );

protected:
    void OnMouseEnter();

    void OnMouseLeave();
};

#endif //!SDL_BUTTON_H_INCLUDED
