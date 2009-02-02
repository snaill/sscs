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

void SDL_ProgressBar::SetBounds( const SDL_Rect  * lpsz )
{
	SDL_Rect	rc;
	rc.x = lpsz->x;
	rc.y = lpsz->y + lpsz->h - BAR_HEIGHT;
	rc.w = lpsz->w;
	rc.h = BAR_HEIGHT;

	SDL_Glyph::SetBounds( &rc );
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
	hlineRGBA( screen, rc.x, rc.x + offset, rc.y + 2, 255, 255, 255, 255 );
	hlineRGBA( screen, rc.x, rc.x + offset, rc.y + 3, 255, 255, 255, 255 );
	hlineRGBA( screen, rc.x, rc.x + offset, rc.y + 4, 192, 192, 192, 255 );
}