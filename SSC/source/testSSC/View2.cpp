#include "View2.h"
#include "SSC/SDL_SimpleControls.h"
#include "SSC/ImageView/SDL_ImageView.h"

CView2::CView2(void)
{
	SDL_Color	crMask;
	crMask.r = 0;crMask.g = 0;crMask.b = 0;

	SDL_ListBox	*	listbox = new SDL_ListBox( );
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test1"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test2"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test3"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test4"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test5"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test6"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test7"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test8"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test9"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test10"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test11"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test12"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test13"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test14"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test15"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test16"), new SDL_Label( L"ccccc"), 0 ));
	listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test17"), new SDL_Label( L"ccccc"), 0 ));
	listbox->SetLayoutProperty( SDL_BorderLayout::fill );

	//
	SDL_Toolbar	*	toolbar = new SDL_Toolbar();
	SDL_ImageList * imgList = new SDL_ImageList();
	imgList->CreateFromBitmap( 48, SDL_LoadBMP("test.bmp"), crMask );
	toolbar->Add( new SDL_Button( new SDL_Label( L"IVTB1" ), new SDL_Image( imgList->GetObj<SDL_ImageList>(), 0 ) ) );
	toolbar->Add( new SDL_Button( new SDL_Label( L"IVTB2" ), new SDL_Image( imgList->GetObj<SDL_ImageList>(), 0 ) ) );
	toolbar->Add( new SDL_Button( new SDL_Label( L"IVTB3" ), new SDL_Image( imgList->GetObj<SDL_ImageList>(), 0 ) ) );

	SDL_Button * btnClose = new SDL_Button( new SDL_Label( L"Close" ), new SDL_Image(  imgList->GetObj<SDL_ImageList>(), 0 ) );
	btnClose->click.connect( this, &CView2::OnBtnReturn );
	toolbar->Add( btnClose );
	toolbar->SetLayoutProperty( SDL_BorderLayout::north );

	SDL_Button * pAction = new SDL_Button( new SDL_Label( L"Return" ), 0 );
	pAction->click.connect( this, &CView2::OnBtnReturn );
	SDL_ActionMenu * menu = new SDL_ActionMenu( pAction, new SDL_Button( new SDL_Label( L"ToolButton2" ), 0 ) );
	menu->SetLayoutProperty( SDL_BorderLayout::south );

	//
	SetLayout( new SDL_BorderLayout() );
	Add( toolbar );
	Add( menu );
	Add( listbox );
}

CView2::~CView2(void)
{
}

void CView2::OnBtnReturn( SDL_Widget * button )
{
	Destory();
}
