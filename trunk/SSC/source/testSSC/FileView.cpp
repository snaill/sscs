#include "FileView.h"

CFileView::CFileView(void)
{
	SDL_Color	crMask;
	crMask.r = 0;crMask.g = 0;crMask.b = 0;

	SDL_ListBox	*	listbox = new SDL_ListBox( );
	SDL_ImageList * imgList = new SDL_ImageList();
	imgList->Create( 48, SDL_LoadBMP("test.bmp"), crMask );
	listbox->SetImageList( imgList );

	listbox->AddItem( L"ÖÐ¹ú", L"aaa", 0 );
	listbox->AddItem( L"Test2", L"bbbb", 1 );
	listbox->AddItem( L"Test3", L"ccccc", 2 );
	listbox->AddItem( L"Test4", L"ccccc", 3 );
	listbox->AddItem( L"Test5", L"ccccc", 4 );
	listbox->AddItem( L"Test6", L"ccccc", 5 );
	listbox->AddItem( L"Test7", L"ccccc", 6 );
	listbox->AddItem( L"Test8", L"ccccc", 7 );
	listbox->AddItem( L"Test9", L"ccccc", 8 );
	listbox->AddItem( L"Test10", L"ccccc", 9 );
	listbox->AddItem( L"Test11", L"ccccc", 10 );
	listbox->AddItem( L"Test12", L"ccccc", 11 );
	listbox->AddItem( L"Test13", L"ccccc", 12 );
	listbox->AddItem( L"Test14", L"ccccc", 13 );
	listbox->AddItem( L"Test15", L"ccccc", 14 );
	listbox->AddItem( L"Test16", L"ccccc", 15 );
	listbox->SetLayoutProperty( SDL_BorderLayout::fill );

	//
	m_toolbar = new SDL_Toolbar();
//	SDL_ImageList * imgList2 = new SDL_ImageList();
//	imgList2->Create( 48, SDL_LoadBMP("D:\\BookStar SDL\\bin\\win32\\test.bmp") );
//	toolbar->SetContent( listbox );
	m_toolbar->SetImageList( (SDL_ImageList *)imgList->GetObj() );
	m_toolbar->AddItem( L"ToolButton1", 0 );
	m_toolbar->AddItem( L"ToolButton2", 0 );
	m_toolbar->AddItem( L"ToolButton3", 0 );
	m_toolbar->AddItem( L"ToolButton4", 0 );
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

void CFileView::OnToolButtonClick( SDL_ToolButton * button )
{
	m_toolbar->Show( false );
}