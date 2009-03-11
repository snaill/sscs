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
	toolbar->Add( new SDL_Button( new SDL_Label( L"IVTB1" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	toolbar->Add( new SDL_Button( new SDL_Label( L"IVTB2" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	toolbar->Add( new SDL_Button( new SDL_Label( L"IVTB3" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );

	SDL_Button * btnClose = new SDL_Button( new SDL_Label( L"Close" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) );
	btnClose->click.connect( this, &CImageView::OnBtnClose );
	toolbar->Add( btnClose );
	toolbar->SetLayoutProperty( SDL_BorderLayout::north );

	//
	SetLayout( new SDL_BorderLayout() );
	Add( toolbar );
	Add( imageView );
}

CImageView::~CImageView(void)
{
}

void CImageView::OnBtnClose( SDL_Widget * button )
{
	this->Destory();
}
