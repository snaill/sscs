#ifndef SDL_WIDGET_H_INCLUDED
#define SDL_WIDGET_H_INCLUDED

#include "SDL_Glyph.h"

/// @brief 控件类的基类
class SDL_Widget : public SDL_Glyph
{
public:
    /// @brief 发送事件
    /// @param evnet 事件信息
 	virtual bool HandleEvent(const SDL_Event *event);

protected:
    SDL_Widget();

    virtual void OnMouseEnter() {}
    virtual void OnMouseLeave() {}

protected:
    /// Widget状态
    SDL_WidgetStatus    m_aStatus;
};

#endif // SDL_WIDGET_H_INCLUDED
