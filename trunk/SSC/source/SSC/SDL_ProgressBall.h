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

#include "SDL_ProgressBar.h"

/// @brief �����������࣬�����ĵ����ȼ���ǰ�ķ�ҳ����
class SDL_ProgressBall : public SDL_ProgressBar
{
public:
	SDL_ProgressBall( );
	virtual ~SDL_ProgressBall(void);

	//
	virtual const char * GetType()			{ return "progressball";	}

	/// @brief ��ȡװ������ȥ�ͻ�ͼԪ�Ժ�ľ���λ��
	/// @param lprc ���صľ���λ��
	SDL_Size GetPreferedSize();

	/// @brief ����������ͼԪ���Σ������ͻ�ͼԪ�ľ��η�Χ������ͬʱ���¿ͻ�ͼԪ�ľ���
	/// @param lpsz ͼԪ����ָ��
	virtual void SetBounds( const SDL_Rect  * lpsz );

protected:
	virtual void DrawWidget( SDL_Surface * screen );
};
