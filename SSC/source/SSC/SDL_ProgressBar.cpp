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

#include "SDL_ProgressBar.h"
#include <SDL_gfxPrimitives.h>

/// 进度条的高度
#define BAR_HEIGHT		5
/// 当前进度框的宽度
#define BAR_POINTWIDTH	10

SDL_ProgressBar::SDL_ProgressBar()
{
	m_nPos = 0;
}

SDL_ProgressBar::~SDL_ProgressBar(void)
{
}

void SDL_ProgressBar::HitTest( POINT pt, int &nCommand, int &nPos )
{
	//if ( pt.x >= m_rc.left && pt.x < m_rc.left + 5 + 4 )
	//	nCommand = Start;
	//else if ( pt.x >= m_rc.left + 5 + 4 && pt.x < m_rc.left + 5 + 4 + 2 + 3 + 2 )
	//	nCommand = PrevPage;
	//else if ( pt.x <= m_rc.right && pt.x > m_rc.right - 5 - 4 )
	//	nCommand = End;
	//else if ( pt.x <= m_rc.right - 5 - 4 && pt.x > m_rc.right - 5 - 4 - 2 - 3 - 2 )
	//	nCommand = NextPage;
	//else
	//{
	//	nCommand = Position;
	//	
	//	int nStart = m_rc.left + 5 + 4 + 2 + 3 + 2;
	//	int nEnd = m_rc.right - 5 - 4 - 2 - 3 - 2;
	//	nPos = ( pt.x - nStart ) * 100 / ( nEnd - nStart );
	//}
}

SDL_Size SDL_ProgressBar::GetPreferedSize()
{
	return SDL_Size( 0, BAR_HEIGHT );
}

void SDL_ProgressBar::DrawWidget( SDL_Surface * screen )
{
	SDL_Rect	rc = GetBounds();
		
	// 绘制背景
	SDL_FillRect( screen, &rc, SDL_MapRGB( screen->format, 64, 64, 64 ) );

	///进度显示
	int offset = rc.w * m_nPos / 100;
	hlineRGBA( screen, rc.x, rc.x + offset, rc.y, 128, 128, 128, 255 );
	hlineRGBA( screen, rc.x, rc.x + offset, rc.y + 1, 192, 192, 192, 255 );
	boxRGBA( screen, rc.x, rc.y + 2, rc.x + offset, rc.y + rc.h - 2, 255, 255, 255, 255 );
	//hlineRGBA( screen, rc.x, rc.x + offset, rc.y + 2, 255, 255, 255, 255 );
	//hlineRGBA( screen, rc.x, rc.x + offset, rc.y + 3, 255, 255, 255, 255 );
	hlineRGBA( screen, rc.x, rc.x + offset, rc.y + rc.h - 1, 192, 192, 192, 255 );
}