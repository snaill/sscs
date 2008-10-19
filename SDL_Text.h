#ifndef SDL_TEXT_H_INCLUDED
#define SDL_TEXT_H_INCLUDED

#include "SDL_Glyph.h"

class SDL_Text : public SDL_Glyph
{
// 实现父接口
public:
	SDL_Text( const char * );
	virtual ~SDL_Text(void);

	virtual const char * GetType()				{ return "text"; }

	virtual void GetBounds( SDL_Rect  * );
	virtual void Draw( SDL_Surface * screen );

// 类成员函数
public:
    void GetTextStatus( SDL_Status * status );
    void SetTextStatus( const SDL_Status * status );

protected:
    /// 图元所显示的文本
	char	*       m_pszText;

	/// 文本对齐方式
	SDL_TextStatus  m_aStatus;
};

#endif //!SDL_TEXT_H_INCLUDED
