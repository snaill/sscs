#include "View1.h"
#include "View2.h"

CView1::CView1(void)
{
	m_listbox = new SDL_ListBox( );
	m_itemView2 = new SDL_ListItem( new SDL_Label( L"View2"), new SDL_Label( L"ccccc"), 0 );
	m_listbox->Add( m_itemView2 );
	m_listbox->Add( new SDL_ListItem( new SDL_Label( L"Test6"), new SDL_Label( L"ccccc"), 0 ));
	m_listbox->SetLayoutProperty( SDL_BorderLayout::fill );
	m_listbox->select.connect( this, &CView1::OnItemSelected );

	//
	SDL_Button * pAction = new SDL_Button( new SDL_Label( L"Quit" ), 0 );
	pAction->click.connect( this, &CView1::OnBtnClose );
	SDL_ActionMenu * menu = new SDL_ActionMenu( pAction, 0 );
	menu->SetLayoutProperty( SDL_BorderLayout::south );

	//
	SDL_BorderLayout * layout = new SDL_BorderLayout();
	layout->Add( menu );
	layout->Add( m_listbox );
	SetContent( layout );
}

CView1::~CView1(void)
{
}

void CView1::OnItemSelected( SDL_ListItem * button )
{
	SDL_Window * view = 0;
	if ( button == m_itemView2 )
		view = new CView2();

	if ( !view )
		return;

	view->Show();
}

void CView1::OnBtnClose( SDL_Glyph * button )
{
	this->Destory();
}