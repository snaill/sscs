#include "ImageView.h"
#include "SSC/SDL_SimpleControls.h"
#include "SSC/ImageView/SDL_ImageView.h"

CImageView::CImageView(void)
{
	SDL_Color	crMask;
	crMask.r = 0;crMask.g = 0;crMask.b = 0;

	SDL_ImageView * imageView = new SDL_ImageView();
	imageView->SetLayoutProperty( SDL_BorderLayout::fill );
	imageView->Load( "E:\\AppEngine\\sscs\\SSC\\bin\\win32\\test.bmp" );

	//
	SDL_Toolbar	*	toolbar = new SDL_Toolbar();
	SDL_ImageList * imgList = new SDL_ImageList();
	imgList->Create( 48, SDL_LoadBMP("E:\\AppEngine\\sscs\\SSC\\bin\\win32\\test.bmp"), crMask );
	toolbar->SetImageList( imgList );
	toolbar->AddItem( "ToolButton1", 0 );
	toolbar->AddItem( "ToolButton2", 0 );
	toolbar->AddItem( "ToolButton3", 0 );
	toolbar->AddItem( "ToolButton4", 0 );
	toolbar->SetLayoutProperty( SDL_BorderLayout::north );

	//
	m_this = new SDL_Widget();
	m_this->SetLayout( new SDL_BorderLayout() );
	m_this->Add( toolbar );
	m_this->Add( imageView );
}

CImageView::~CImageView(void)
{
}