#include "ImageView.h"
#include "SSC/SDL_SimpleControls.h"
#include "SSC/ImageView/SDL_ImageView.h"

CImageView::CImageView(void)
{
	SDL_Color	crMask;
	crMask.r = 0;crMask.g = 0;crMask.b = 0;

	SDL_ImageView * imageView = new SDL_ImageView();
	imageView->SetLayoutProperty( SDL_BorderLayout::fill );
	imageView->Load( "test.bmp" );

	//
	SDL_Toolbar	*	toolbar = new SDL_Toolbar();
	SDL_ImageList * imgList = new SDL_ImageList();
	imgList->CreateFromBitmap( 48, SDL_LoadBMP("test.bmp"), crMask );
	toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton1" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton2" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton3" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton4" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
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
