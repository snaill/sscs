#include "FileView.h"

CFileView::CFileView(void)
{
	m_nClick = 0;

	SDL_Color	crMask;
	crMask.r = 0;crMask.g = 0;crMask.b = 0;

	SDL_ListBox	*	listbox = new SDL_ListBox( );
	SDL_ImageList * imgList = new SDL_ImageList();
	imgList->CreateFromBitmap( 48, SDL_LoadBMP("test.bmp"), crMask );
	m_imgList = imgList;
	m_listbox = listbox;
	listbox->SetLayoutProperty( SDL_BorderLayout::fill );
	listbox->select.connect( this, &CFileView::OnItemSelected );
	OnItemSelected( 0 );

	//
	m_toolbar = new SDL_Toolbar();
//	SDL_ImageList * imgList2 = new SDL_ImageList();
//	imgList2->Create( 48, SDL_LoadBMP("D:\\BookStar SDL\\bin\\win32\\test.bmp") );
//	toolbar->SetContent( listbox );
	m_toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton1" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	m_toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton2" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	m_toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton3" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	m_toolbar->Add( new SDL_Button( new SDL_Label( L"ToolButton4" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) ) );
	m_toolbar->SetLayoutProperty( SDL_BorderLayout::north );

	//
	//SDL_ProgressBar * progressBar = new SDL_ProgressBar();
	//progressBar->SetLayoutProperty( SDL_BorderLayout::fill );
	//progressBar->SetPos( 27 );

	//SDL_ProgressBall * progressBall = new SDL_ProgressBall();
	//progressBall->SetLayoutProperty( SDL_BorderLayout::east );
	//progressBall->SetPos( 100 );

	//SDL_Widget * progress = new SDL_Widget();
	//progress->SetLayoutProperty( SDL_BorderLayout::south );
	//progress->SetLayout( new SDL_BorderLayout() );
	//progress->Add( progressBall );
	//progress->Add( progressBar );

	SDL_Button * pAction = new SDL_Button( new SDL_Label( L"ToolButton1" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 0 ) );
	pAction->click.connect( this, &CFileView::OnToolButtonClick );
	SDL_ActionMenu * menu = new SDL_ActionMenu( pAction, 
		new SDL_Button( new SDL_Label( L"ToolButton2" ), new SDL_Image( (SDL_ImageList *)imgList->GetObj(), 1 ) ) );
	menu->SetLayoutProperty( SDL_BorderLayout::south );

	//
	SetLayout( new SDL_OverBorderLayout() );
	Add( m_toolbar );
//	Add( progress );
	Add( menu );
	Add( listbox );

	listbox->SetFocus();

}

CFileView::~CFileView(void)
{
}

void CFileView::OnItemSelected( SDL_ListBoxItem * button )
{
	m_listbox->Clear();

	//if ( m_nClick > 0 )
	//	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"2" ), 0, 0 ) );
	//if ( m_nClick > 1 )
	//	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"�й�" ), new SDL_Label( L"aaa" ), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 0 ) ) );
	//if ( m_nClick < 2 )
	//	m_listbox->Add( new SDL_Button( new SDL_Label( L"ToolButton4" ), 
	//		new SDL_Image( (SDL_ImageList *)m_imgList->GetObj(), 0 ) ) );
	//	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test2"), new SDL_Label( L"bbbb"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 1 ) ));
	//if ( m_nClick < 3 )
	//	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test3"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 2 ) ));
	//if ( m_nClick < 4 )
	//	m_listbox->Add( new SDL_CheckBox( L"CheckBox1" ) );

	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test5"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 4 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test6"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 5 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test7"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 6 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test8"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 7 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test9"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 8 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test10"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 9 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test11"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 10 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test12"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 11 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test13"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 12 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test14"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 13 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test15"), new SDL_Label( L"ccccc"), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 14 ) ));
	m_listbox->Add( new SDL_ListBoxItem( new SDL_Label( L"Test16"), new SDL_Label( L"ccccc" ), new SDL_Image( ( SDL_ImageList * )m_imgList->GetObj(), 15 ) ));

	m_nClick++;
	if ( m_nClick > 4 )
		m_nClick = 0;

	m_listbox->RecalcLayout();
}

void CFileView::OnToolButtonClick( SDL_Widget * button )
{
	OnItemSelected( 0 );
}