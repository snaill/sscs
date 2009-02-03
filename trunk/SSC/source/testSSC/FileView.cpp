#include "FileView.h"

CFileView::CFileView(void)
{
	SDL_Color	crMask;
	crMask.r = 0;crMask.g = 0;crMask.b = 0;

	SDL_ListBox	*	listbox = new SDL_ListBox( );
	SDL_ImageList * imgList = new SDL_ImageList();
	imgList->Create( 48, SDL_LoadBMP("test.bmp"), crMask );
	listbox->SetImageList( imgList );

	listbox->AddItem( "ÖÐ¹ú", "aaa", 0 );
	listbox->AddItem( "Test2", "bbbb", 1 );
	listbox->AddItem( "Test3", "ccccc", 2 );
	listbox->AddItem( "Test4", "ccccc", 3 );
	listbox->AddItem( "Test5", "ccccc", 4 );
	listbox->AddItem( "Test6", "ccccc", 5 );
	listbox->AddItem( "Test7", "ccccc", 6 );
	listbox->AddItem( "Test8", "ccccc", 7 );
	listbox->AddItem( "Test9", "ccccc", 8 );
	listbox->AddItem( "Test10", "ccccc", 9 );
	listbox->AddItem( "Test11", "ccccc", 10 );
	listbox->AddItem( "Test12", "ccccc", 11 );
	listbox->AddItem( "Test13", "ccccc", 12 );
	listbox->AddItem( "Test14", "ccccc", 13 );
	listbox->AddItem( "Test15", "ccccc", 14 );
	listbox->AddItem( "Test16", "ccccc", 15 );
	listbox->SetLayoutProperty( SDL_BorderLayout::fill );

	//
	m_toolbar = new SDL_Toolbar();
//	SDL_ImageList * imgList2 = new SDL_ImageList();
//	imgList2->Create( 48, SDL_LoadBMP("D:\\BookStar SDL\\bin\\win32\\test.bmp") );
//	toolbar->SetContent( listbox );
	m_toolbar->SetImageList( (SDL_ImageList *)imgList->GetObj() );
	m_toolbar->AddItem( "ToolButton1", 0 );
	m_toolbar->AddItem( "ToolButton2", 0 );
	m_toolbar->AddItem( "ToolButton3", 0 );
	m_toolbar->AddItem( "ToolButton4", 0 );
	m_toolbar->SetLayoutProperty( SDL_BorderLayout::north );

	m_toolbar->click.connect( this, &CFileView::OnToolButtonClick );

	//
	m_this = new SDL_Widget();
	m_this->SetLayout( new SDL_BorderLayout() );
	m_this->Add( m_toolbar );
	m_this->Add( listbox );
}

CFileView::~CFileView(void)
{
}

void CFileView::OnToolButtonClick( int index, SDL_ToolButton * button )
{
	m_toolbar->Show( false );
}