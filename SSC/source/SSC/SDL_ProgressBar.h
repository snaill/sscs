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
	virtual const char * GetType()			{ return "SDL_ProgressBar";	}

	/// @brief ��ȡװ������ȥ�ͻ�ͼԪ�Ժ�ľ���λ��
	/// @param lprc ���صľ���λ��
	SDL_Size GetPreferedSize();

	inline int GetPos()				{ return m_nPos;				}
	inline void SetPos( int nPos )	{ m_nPos = nPos;				}

	void HitTest( POINT pt, int &nCommand, int &nPos );
protected:
	virtual void DrawWidget( SDL_Surface * screen );
};
