#ifndef __COMMANDS_H
#define __COMMANDS_H

#include "../CORE/MiniCOM.h"
#include "../CORE/CommandArgs.h"
#include "../CORE/VirtualScreen.h"
#include "../Platform/Platform.h"
#include "ImageView.h"
#include <stdlib.h>

class CBaseImpl
{
protected:
	CImageView * m_view;

public:
	CBaseImpl( CImageView * view )	
	{
		m_view = view;
		if ( m_view )
			m_view->AddRef();
	}

	virtual ~CBaseImpl()
	{
		if ( m_view )
			m_view->Release();
	}

	IImageObject * GetObject()	{
		return m_view->m_pObject;
	}

	LPPOINT	GetOrigPoint()	{
		return &m_view->m_ptOrig;
	}

	LPRECT GetImageRect()	{
		return &m_view->m_rcImage;
	}

	LPRECT GetClipRect()	{
		return &m_view->m_rcClip;
	}
	
	LONG GetRatio()	{
		return m_view->m_lRatio;
	}

	void SetRatio( LONG lRatio )	{
		m_view->m_lRatio = lRatio;
	}

	bool GetPlayFlag() {
		return m_view->m_bPlay;
	}

	void SetPlayFlag() {
		m_view->m_bPlay = !m_view->m_bPlay;
	}

	int GetFitState()	{
		return m_view->m_nFitState;
	}

	void ResetFitState()	{
		m_view->m_nFitState ++;
		if ( m_view->m_nFitState > 3 )
			m_view->m_nFitState = 0;
	}
};

class CEventBase :  public IBaseImpl<IEvent, MINI_IID_Event>, 
					public CBaseImpl
{
public:
	CEventBase( CImageView * view ) : CBaseImpl( view ) {}
};

class CCommandBase : public IBaseImpl<ICommand, MINI_IID_Command>, 
					 public CBaseImpl
{
public:
	CCommandBase( CImageView * view ) : CBaseImpl( view ) {}

	virtual bool IsExecuting( void * param ) {
		return false;
	}
};

/////////////////////////////////////////////////////////////////
class CCommandZoom : public CCommandBase
{
public:
	CCommandZoom( CImageView * view ) : CCommandBase( view ) {}

	void Execute( void * param )
	{
		long lRatio = ( param == NULL ) ? 100 : *( long * )param;
		SetRatio( lRatio );
		m_view->RecalcImageRect();
	}
};

class CCommandZoomIn : public CCommandBase
{
public:
	CCommandZoomIn( CImageView * view ) : CCommandBase( view ) {}

	void Execute( void * param )
	{
		SetRatio( ( long )( GetRatio() * 1.2 ) );
		m_view->RecalcImageRect();
	}

	bool CanExecute( void * param )
	{
		return GetRatio() < 400;
	}
};

class CCommandZoomOut : public CCommandBase
{
public:
	CCommandZoomOut( CImageView * view ) : CCommandBase( view ) {}

	void Execute( void * param )
	{
		SetRatio( ( long )( GetRatio() * 0.8 ) );
		m_view->RecalcImageRect();
	}

	bool CanExecute( void * param )
	{
		return GetRatio() > 0.1;
	}
};

class CCommandPlay : public CCommandBase
{
public:
	CCommandPlay( CImageView * view ) : CCommandBase( view ) {}

	void Execute( void * param )
	{
		SetPlayFlag();
	}

	bool CanExecute( void * param )
	{
		return GetObject()->GetPageCount() > 1;
	}
		
	bool IsExecuting( void * param ) 
	{
		return GetPlayFlag();
	}
};	

class CCommandRotate : public CCommandBase
{
public:
	CCommandRotate( CImageView * view ) : CCommandBase( view ) {}

	void Execute( void * param )
	{
		GetObject()->Rotate( *((int *)param), false );
		m_view->RecalcImageRect();
	}
};

class CCommandTurnRight : public CCommandRotate
{
public:
	CCommandTurnRight( CImageView * view ) : CCommandRotate( view ) {}

	void Execute( void * param )
	{
		int nDegree = GetObject()->GetDegree() + 90 <= 270 ? GetObject()->GetDegree() + 90 : 0;
		CCommandRotate::Execute( &nDegree );
	}

	bool CanExecute( void * param )
	{
		return true;
	}
};

class CCommandFitScreen : public CCommandBase
{
public:
	CCommandFitScreen( CImageView * view ) : CCommandBase( view ) {}

	void Execute( void * param )
	{
		ResetFitState();

		switch ( GetFitState() )
		{
		case 0:
			SetRatio( 100 );
			break;
		case 1:
			SetRatio( ( GetClipRect()->right - GetClipRect()->left ) * 100 / GetObject()->GetWidth() );	
			break;
		case 2:
			SetRatio( ( GetClipRect()->bottom - GetClipRect()->top ) * 100 / GetObject()->GetHeight() );	
			break;
		case 3:
			SetRatio( min( ( GetClipRect()->right - GetClipRect()->left ) * 100 / GetObject()->GetWidth(),
						( GetClipRect()->bottom - GetClipRect()->top ) * 100 / GetObject()->GetHeight() ) );
			break;
		default:
			assert( false );
			return;
		}

		m_view->RecalcImageRect();
	}

	bool CanExecute( void * param )
	{
		return true;
	}
};
//
//class CCommandPrevImage : public CCommandBase
//{
//public:
//	CCommandPrevImage( CImageView * view ) : CCommandBase( view ) {}
//
//	void Execute( void * param )
//	{
//		GetObject()->PrevImage();
//		m_view->RecalcImageRect();
//	}
//
//	BOOL CanExecute( void * param )
//	{
//		return GetObject()->GetPageCount() > 1;
//	}
//};
//
//class CCommandNextImage : public CCommandBase
//{
//public:
//	CCommandNextImage( CImageView * view ) : CCommandBase( view ) {}
//
//	void Execute( void * param )
//	{
//		GetObject()->NextImage();
//		m_view->RecalcImageRect();
//	}
//
//	BOOL CanExecute( void * param )
//	{
//		return GetObject()->GetPageCount() > 1;
//	}
//};

//////////////////////////////////////////////////////////////////////////
//
class CEventMouseDown : public CEventBase
{
public:
	CEventMouseDown( CImageView * view ) : CEventBase( view ) {}

	void Execute( EventArgs * pe )
	{
		MouseEventArgs * pArgs = ( MouseEventArgs * )pe;

		CVirtualScreen	aScreen;
		aScreen.SetDegree( GetObject()->GetDegree() );
		GetOrigPoint()->x = pArgs->x;
		GetOrigPoint()->y = pArgs->y;
	}
};

class CEventMouseMove : public CEventBase
{
public:
	CEventMouseMove( CImageView * view ) : CEventBase( view ) {}

	void Execute( EventArgs * pe )
	{
		MouseEventArgs * pArgs = ( MouseEventArgs * )pe;

		if ( pArgs->button == MouseEventArgs::Left )
		{
			CVirtualScreen	aScreen;
			aScreen.SetDegree( GetObject()->GetDegree() );
			aScreen.RealToVirtual( pArgs->x, pArgs->y, *GetClipRect() ); 
			
			POINT	ptDelta;
			ptDelta.x = GetOrigPoint()->x - pArgs->x;
			ptDelta.y = GetOrigPoint()->y - pArgs->y;

			IParameterService * pSrv = ( IParameterService * )_ServiceMgr->GetService( SERVICE_PARAMETER );
			int		nMinMove = pSrv->GetDWORD( Parameter::MinImageMove );	

			if (abs(ptDelta.x) > nMinMove || abs(ptDelta.y) > nMinMove )
			{
				if (ptDelta.x > 0 && GetImageRect()->right >= GetClipRect()->right)
				{
					// Left
					GetImageRect()->left -= nMinMove;
					GetImageRect()->right -= nMinMove;
				}
				if (ptDelta.y > 0 && GetImageRect()->bottom >= GetClipRect()->bottom)
				{
					// Up
					GetImageRect()->top -= nMinMove;
					GetImageRect()->bottom -= nMinMove;
				}
				if (ptDelta.x < 0 && GetImageRect()->left <= GetClipRect()->left)
				{
					// Right
					GetImageRect()->left += nMinMove;
					GetImageRect()->right += nMinMove;
				}
				if (ptDelta.y < 0 && GetImageRect()->top <= GetClipRect()->top)
				{
					// Down
					GetImageRect()->top += nMinMove;
					GetImageRect()->bottom += nMinMove;
				}

				GetOrigPoint()->x = pArgs->x;
				GetOrigPoint()->y = pArgs->y;
				m_view->RecalcImageRect();
			}
		}
	}
};

class CEventKeyDown : public CEventBase
{
public:
	CEventKeyDown( CImageView * view ) : CEventBase( view ) {}

	void Execute( EventArgs * pe )
	{
		KeyEventArgs * pArgs = ( KeyEventArgs * )pe;

		CVirtualScreen	aScreen;
		aScreen.SetDegree( GetObject()->GetDegree() );
		aScreen.RealToVirtual( pArgs->KeyCode ); 
		
		//
		IParameterService * pSrv = ( IParameterService * )_ServiceMgr->GetService( SERVICE_PARAMETER );
		int		nMinMove = pSrv->GetDWORD( Parameter::MinImageMove );	
		switch ( pArgs->KeyCode )
		{
		case VK_UP:
			GetImageRect()->top += nMinMove;
			GetImageRect()->bottom += nMinMove;
			m_view->RecalcImageRect();
			break;
		case VK_DOWN:
			GetImageRect()->top -= nMinMove;
			GetImageRect()->bottom -= nMinMove;
			m_view->RecalcImageRect();
			break;
		case VK_LEFT:
			GetImageRect()->left += nMinMove;
			GetImageRect()->right += nMinMove;
			m_view->RecalcImageRect();
			break;
		case VK_RIGHT:
			GetImageRect()->left -= nMinMove;
			GetImageRect()->right -= nMinMove;
			m_view->RecalcImageRect();
			break;
		case VK_PRIOR:
			GetObject()->PrevImage();
			m_view->RecalcImageRect();
			break;
		case VK_NEXT:
			GetObject()->NextImage();
			m_view->RecalcImageRect();
			break;
		}
		//!!!!! 关于按键配置的功能,需要和KeyboardService统一考虑，暂时屏蔽
//		IKeyboardService * pSrv = ( IKeyboardService * )_ServiceMgr->GetService( SERVICE_KEYBOARD );
//		OnCommand( pSrv->GetCommadID( MINI_IID_ImageView, nVirtualKey ), -1 );

//		OnPaint( hWnd );

	}
};

class CEventSizeChanged : public CEventBase
{
public:
	CEventSizeChanged( CImageView * view ) : CEventBase( view ) {}

	void Execute( EventArgs * pe )
	{
		SizeChangedEventArgs * pArgs = ( SizeChangedEventArgs * )pe;

		// 设置裁剪区大小
		GetClipRect()->left = 0;
		GetClipRect()->top = 0;
		GetClipRect()->right = pArgs->newWidth;
		GetClipRect()->bottom = pArgs->newHeight;

		m_view->RecalcImageRect();
	}
};

class CEventPaint : public CEventBase
{
public:
	CEventPaint( CImageView * view ) : CEventBase( view ) {}

	void Execute( EventArgs * pe )
	{
		PaintEventArgs * pArgs = ( PaintEventArgs * )pe;

		CMemDC_P	dc;
		dc.Create( ( HDC )pArgs->hDC, pArgs->rcClip );

		// 填充背景
		dc.FillRect( GetClipRect(), RGB( 0, 0, 0 ) );

		// 初始化图片矩形范围
		if ( GetImageRect()->left == GetImageRect()->right || GetImageRect()->top == GetImageRect()->bottom ) 
			m_view->RecalcImageRect();

		// 绘制位图
		GetObject()->Draw( &dc, GetImageRect()->left, GetImageRect()->top, GetImageRect()->right - GetImageRect()->left, 
			GetImageRect()->bottom - GetImageRect()->top, *GetClipRect() );

		dc.Destory();

		m_view->SetRedrawFlag( false );
	}
};

#endif //!__COMMANDS_H