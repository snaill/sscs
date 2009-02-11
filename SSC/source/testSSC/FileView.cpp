#include "FileView.h"

CFileView::CFileView(void)
{
	SDL_Color	crMask;
	crMask.r = 0;crMask.g = 0;crMask.b = 0;

	SDL_ListBox	*	listbox = new SDL_ListBox( );
	SDL_ImageList * imgList = new SDL_ImageList();
	imgList->CreateFromBitmap( 48, SDL_LoadBMP("test.bmp"), crMask );
//	listbox->SetImageList( imgList );

	listbox->Add( new SDL_ListBoxItem( L"ÖÐ¹ú", L"aaa", ( SDL_ImageList * )imgList->GetObj(), 0 ) );
	listbox->Add( new SDL_ToolButton( L"ToolButton4", (SDL_ImageList *)imgList->GetObj(), 0 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test2", L"bbbb", ( SDL_ImageList * )imgList->GetObj(), 1 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test3", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 2 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test4", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 3 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test5", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 4 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test6", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 5 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test7", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 6 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test8", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 7 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test9", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 8 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test10", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 9 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test11", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 10 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test12", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 11 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test13", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 12 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test14", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 13 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test15", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 14 ) );
	listbox->Add( new SDL_ListBoxItem( L"Test16", L"ccccc", ( SDL_ImageList * )imgList->GetObj(), 15 ) );
	listbox->SetLayoutProperty( SDL_BorderLayout::fill );

	//
	m_toolbar = new SDL_Toolbar();
//	SDL_ImageList * imgList2 = new SDL_ImageList();
//	imgList2->Create( 48, SDL_LoadBMP("D:\\BookStar SDL\\bin\\win32\\test.bmp") );
//	toolbar->SetContent( listbox );
	m_toolbar->Add( new SDL_ToolButton( L"ToolButton1", (SDL_ImageList *)imgList->GetObj(), 0 ) );
	m_toolbar->Add( new SDL_ToolButton( L"ToolButton2", (SDL_ImageList *)imgList->GetObj(), 0 ) );
	m_toolbar->Add( new SDL_ToolButton( L"ToolButton3", (SDL_ImageList *)imgList->GetObj(), 0 ) );
	m_toolbar->Add( new SDL_ToolButton( L"ToolButton4", (SDL_ImageList *)imgList->GetObj(), 0 ) );
	m_toolbar->SetLayoutProperty( SDL_BorderLayout::north );

	m_toolbar->click.connect( this, &CFileView::OnToolButtonClick );

	//
	SDL_ProgressBar * progressBar = new SDL_ProgressBar();
	progressBar->SetLayoutProperty( SDL_BorderLayout::fill );
	progressBar->SetPos( 27 );

	SDL_ProgressBall * progressBall = new SDL_ProgressBall();
	progressBall->SetLayoutProperty( SDL_BorderLayout::east );
	progressBall->SetPos( 100 );

	SDL_Widget * progress = new SDL_Widget();
	progress->SetLayoutProperty( SDL_BorderLayout::south );
	progress->SetLayout( new SDL_BorderLayout() );
	progress->Add( progressBall );
	progress->Add( progressBar );

	//
	m_this = new SDL_Widget();
	m_this->SetLayout( new SDL_BorderLayout() );
	m_this->Add( m_toolbar );
	m_this->Add( progress );
	m_this->Add( listbox );

	listbox->SetFocus();

}

CFileView::~CFileView(void)
{
}

void CFileView::OnToolButtonClick( SDL_Widget * button )
{
	SDL_MainFrame::Get()->ToggleFullScreen();
//	m_toolbar->Show( false );
}