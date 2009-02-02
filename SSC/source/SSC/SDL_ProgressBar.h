#pragma once

#include "SDL_Widget.h"

/// @brief �����������࣬�����ĵ����ȼ���ǰ�ķ�ҳ����
class SDL_ProgressBar : public SDL_Widget
{
protected:
	int			m_nPos;

public:
	SDL_ProgressBar( );
	virtual ~SDL_ProgressBar(void);

	//
	virtual const char * GetType()			{ return "progressbar";	}

	/// @brief ��ȡװ������ȥ�ͻ�ͼԪ�Ժ�ľ���λ��
	/// @param lprc ���صľ���λ��
	SDL_Size GetPreferedSize();

	/// @brief ����������ͼԪ���Σ������ͻ�ͼԪ�ľ��η�Χ������ͬʱ���¿ͻ�ͼԪ�ľ���
	/// @param lpsz ͼԪ����ָ��
	virtual void SetBounds( const SDL_Rect  * lpsz );

	inline int GetPos()				{ return m_nPos;				}
	inline void SetPos( int nPos )	{ m_nPos = nPos;				}

	void HitTest( POINT pt, int &nCommand, int &nPos );
protected:
	virtual void DrawWidget( SDL_Surface * screen );
};
