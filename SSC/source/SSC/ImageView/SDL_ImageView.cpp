#include "SDL_ImageView.h"
#include <SDL_image.h>

#define MIN_IMAGEMOVE	20

SDL_ImageView::SDL_ImageView(void)
{
	m_pszFilename = NULL;
	m_lRatio = 100;
	m_bPlay = false;
	m_pObject = NULL;
	m_nFitState = 0;
	memset( &m_rcImage, 0x00, sizeof( SDL_Rect ) );
}

SDL_ImageView::~SDL_ImageView(void)
{
	if ( m_pObject )
		SDL_FreeSurface( m_pObject );

	if ( m_pszFilename )
		delete m_pszFilename;
}

//ICommand * CImageView::Get(  int nGroup, int nIndex, int * pid )
//{
//	assert( m_pObject );
//
//	switch ( nGroup )
//	{
//	case 0:
//		switch ( nIndex )
//		{
//		case 0:	*pid = Command::Return; return NULL;
//		case 1:	*pid = Command::PrevFile; return NULL;
//		case 2: *pid = Command::NextFile; return NULL;
//			default: return NULL;
//		}
//		break;
//	case 1:
//		switch ( nIndex )
//		{
//		case 0: *pid = Command::FullScreen; return NULL;
//		case 1: *pid = Command::FitScreen; return new CCommandFitScreen( this );
//		case 2: *pid = Command::ZoomIn; return new CCommandZoomIn( this );
//		case 3: *pid = Command::ZoomOut; return new CCommandZoomOut( this );
//		case 4: *pid = Command::TurnRight; return new CCommandTurnRight( this );
//		//case 5: 
//		//	if ( 1 >= m_pObject->GetPageCount() )
//		//		return NULL;
//		//	*pid = Command::Play; 
//		//	return new CCommandPlay( this );
//		default: return NULL;
//		}
//		break;
//	default: 
//		return NULL;
//	}
//}

const char * SDL_ImageView::get_FileName()
{
	return m_pszFilename;
}

bool SDL_ImageView::Load( const char * lpsz )
{
	// 保存路径名
	if ( m_pszFilename )
	{
		delete m_pszFilename;
		m_pszFilename = 0;
	}

	m_pObject = IMG_Load( lpsz ); 
	if ( !m_pObject )
		return false;

	SDL_Rect	rc = GetBounds();
	m_rcImage.x = rc.x;
	m_rcImage.y = rc.y;
	m_rcImage.w = m_pObject->w;
	m_rcImage.h = m_pObject->h;

	m_pszFilename = new char[strlen( lpsz ) + 1];
	strcpy( m_pszFilename, lpsz );
	return true;
}

SDL_Surface * SDL_ImageView::get_Object()
{
	return m_pObject;
}

bool SDL_ImageView::put_Object( SDL_Surface * obj )
{
	m_pObject = obj;

	// 重新计算图片的矩形范围
	RecalcImageRect();
	return true;
}

void SDL_ImageView::RecalcImageRect()
{
	int nWidth = m_pObject->w * m_lRatio / 100;
	int nHeight = m_pObject->h * m_lRatio / 100;

	SDL_Point	ptCenter;
	SDL_Rect	m_rcClip = GetBounds();
	if ( m_rcClip.w > nWidth )
	{
		ptCenter.x = m_rcClip.x + ( m_rcClip.w ) / 2;
		m_rcImage.x = ptCenter.x - nWidth / 2;
	}
	else
	{
		ptCenter.x = m_rcImage.x + ( m_rcImage.w ) / 2;
		m_rcImage.x = ptCenter.x - nWidth / 2;
		
		// 偏移图片以保证显示区域完全被图片覆盖
		if ( m_rcImage.x > m_rcClip.x )
			m_rcImage.x = m_rcClip.x;

		if ( m_rcImage.x + m_rcImage.w < m_rcClip.x + m_rcClip.w )
			m_rcImage.x = m_rcClip.x + m_rcClip.w - nWidth;
	}

	if ( m_rcClip.h > nHeight )
	{
		ptCenter.y = m_rcClip.y + m_rcClip.h / 2;
		m_rcImage.y = ptCenter.y - nHeight / 2;
	}
	else
	{
		ptCenter.y = m_rcImage.y + m_rcImage.h / 2;
		m_rcImage.y = ptCenter.y - nHeight / 2;

		// 偏移图片以保证显示区域完全被图片覆盖
		if ( m_rcImage.y > m_rcClip.y )
			m_rcImage.y = m_rcClip.y;

		if ( m_rcImage.y + m_rcImage.h < m_rcClip.y + m_rcClip.h )
			m_rcImage.y = m_rcClip.y + m_rcClip.h - nHeight;
	}
}

void SDL_ImageView::DrawWidget( SDL_Surface * screen )
{
	SDL_FillRect( screen, &GetBounds(), SDL_MapRGB( screen->format, 0, 0, 0 ) ); 

	// 绘制位图
	SDL_Rect	rc = m_rcImage;
	SDL_BlitSurface( m_pObject, 0, screen, &rc );
}

bool SDL_ImageView::OnKeyDown( const SDL_KeyboardEvent * key, bool * bDraw )
{
	//CVirtualScreen	aScreen;
	//aScreen.SetDegree( GetObject()->GetDegree() );
	//aScreen.RealToVirtual( pArgs->KeyCode ); 

	//
//	IParameterService * pSrv = ( IParameterService * )_ServiceMgr->GetService( SERVICE_PARAMETER );
	int		nMinMove = MIN_IMAGEMOVE; //pSrv->GetDWORD( Parameter::MinImageMove );	
	switch ( key->keysym.sym )
	{
	case SDLK_UP:
		m_rcImage.y += nMinMove;
		break;
	case SDLK_DOWN:
		m_rcImage.y -= nMinMove;
		break;
	case SDLK_LEFT:
		m_rcImage.x += nMinMove;
		break;
	case SDLK_RIGHT:
		m_rcImage.x -= nMinMove;
		break;
	default:
		return false;
	//case VK_PRIOR:
	//	GetObject()->PrevImage();
	//	break;
	//case VK_NEXT:
	//	GetObject()->NextImage();
	//	break;
	}
	
	RecalcImageRect();
	*bDraw = true;

	return true;
}

bool SDL_ImageView::OnMouseMove( const SDL_MouseMotionEvent * motion, bool * bDraw )
{
	if ( !( motion->state & SDL_BUTTON(1) ) )
		return false;

	//CVirtualScreen	aScreen;
	//aScreen.SetDegree( GetObject()->GetDegree() );
	//aScreen.RealToVirtual( button->x, button->y, *GetClipRect() ); 

	m_rcImage.x += motion->xrel;
	m_rcImage.y += motion->yrel;
	RecalcImageRect();
	*bDraw = true;

	return true;
}
