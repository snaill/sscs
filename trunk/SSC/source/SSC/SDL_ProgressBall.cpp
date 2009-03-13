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

#include "SDL_ProgressBall.h"
#include <SDL_gfxPrimitives.h>

/// 进度条的高度
#define BALL_SIZE		9
/// ball半径
#define BALL_RAD		4
/// ball间距			
#define BALL_SPACE		2

SDL_ProgressBall::SDL_ProgressBall()
{
}

SDL_ProgressBall::~SDL_ProgressBall(void)
{
}

SDL_Size SDL_ProgressBall::GetPreferedSize()
{
	return SDL_Size( BALL_SIZE * 3 + BALL_SPACE * 4, BALL_SIZE + BALL_SPACE * 2 );
}

void SDL_ProgressBall::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc  )
{
	// 绘制背景
	SDL_FillRect( screen, ( SDL_Rect *)lprc, SDL_MapRGB( screen->format, 64, 64, 64 ) );

	SDL_Rect	rc = *lprc;
	///进度显示
	rc.x += ( rc.w - BALL_SIZE * 3 - BALL_SPACE * 2 ) / 2 + BALL_RAD;
	rc.y += ( rc.h - BALL_SIZE ) / 2 + BALL_RAD;
	rc.w = BALL_SIZE;
	rc.h = BALL_SIZE;

	filledCircleRGBA( screen, rc.x, rc.y, BALL_RAD, 0, 255, 0, 255 );
	if ( GetPos() > 98)
	{
		rc.x += BALL_SIZE + BALL_SPACE;
		filledCircleRGBA( screen, rc.x, rc.y, BALL_RAD, 0, 0, 255, 255 );
		if ( GetPos() > 99 )
		{
			rc.x += BALL_SIZE + BALL_SPACE;
			filledCircleRGBA( screen, rc.x, rc.y, BALL_RAD, 255, 0, 0, 255 );
		}
	}
}