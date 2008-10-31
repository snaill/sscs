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

	virtual void GetMinSize( int * w, int * h );
	virtual void Draw( SDL_Surface * screen );

protected:
    /// 图元所显示的文本
	char	*       m_pszText;
};

#endif //!SDL_TEXT_H_INCLUDED
