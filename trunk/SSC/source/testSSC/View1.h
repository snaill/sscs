#pragma once

#include "SSC/SDL_SimpleControls.h"

class CView1 : public SDL_Window, public sigslot::has_slots<>
{
public:
	CView1(void);
	~CView1(void);

	void OnItemSelected( SDL_ListBoxItem * button );
	void OnBtnClose( SDL_Glyph * button );

protected:
	SDL_ListBox	*		m_listbox;
	SDL_ListBoxItem *	m_itemView2;
};
