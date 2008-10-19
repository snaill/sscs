#ifndef SDL_TEXT_H_INCLUDED
#define SDL_TEXT_H_INCLUDED

#include "SDL_Glyph.h"

class SDL_Text : public SDL_Glyph
{
// ʵ�ָ��ӿ�
public:
	SDL_Text( const char * );
	virtual ~SDL_Text(void);

	virtual const char * GetType()				{ return "text"; }

	virtual void GetBounds( SDL_Rect  * );
	virtual void Draw( SDL_Surface * screen );

// ���Ա����
public:
    void GetTextStatus( SDL_Status * status );
    void SetTextStatus( const SDL_Status * status );

protected:
    /// ͼԪ����ʾ���ı�
	char	*       m_pszText;

	/// �ı����뷽ʽ
	SDL_TextStatus  m_aStatus;
};

#endif //!SDL_TEXT_H_INCLUDED
