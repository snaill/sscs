#ifndef SDL_WIDGET_H_INCLUDED
#define SDL_WIDGET_H_INCLUDED

#include "SDL_Glyph.h"

/// @brief �ؼ���Ļ���
class SDL_Widget : public SDL_Glyph
{
public:
    /// @brief �����¼�
    /// @param evnet �¼���Ϣ
 	virtual bool HandleEvent(const SDL_Event *event);

protected:
    SDL_Widget();

    virtual void OnMouseEnter() {}
    virtual void OnMouseLeave() {}

protected:
    /// Widget״̬
    SDL_WidgetStatus    m_aStatus;
};

#endif // SDL_WIDGET_H_INCLUDED
