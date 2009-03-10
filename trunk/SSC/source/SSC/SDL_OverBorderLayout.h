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

#ifndef SDL_OVERBORDERLAYOUT_H_INCLUDED
#define SDL_OVERBORDERLAYOUT_H_INCLUDED

#include "SDL_Layout.h"
#include "SDL_Widget.h"

/// @brief ���н��沼�ֵĻ��࣬ʵ�̶ֹ�����
class SDL_OverBorderLayout : public SDL_Layout
{
public:
	enum { north, south, west, east, fill };

// ��������
public:
	SDL_OverBorderLayout()		  	{ }
    virtual ~SDL_OverBorderLayout()	{ }

	virtual const char * GetType()				{ return "SDL_OverBorderLayout"; }
	
// ����
public:
	virtual SDL_Size GetPreferedSize( SDL_Container * pContainer );

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void Update( SDL_Container * pContainer, const SDL_Rect * lprc );
	
	virtual void DrawWidget( SDL_Container * pContainer, SDL_Surface * screen );
 	virtual bool HandleMouseEvent( SDL_Container * pContainer, const SDL_Event *event, bool * bDraw );

};

#endif // SDL_OVERBORDERLAYOUT_H_INCLUDED
