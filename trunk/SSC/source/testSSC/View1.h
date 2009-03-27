#pragma once

#include "SSC/SDL_SimpleControls.h"

class CView1 : public SDL_Window, public sigslot::has_slots<>
{
public:
	CView1(void);
	~CView1(void);

	void OnToolButtonClick( SDL_Widget * button );
	void OnItemSelected( SDL_ListBoxItem * button );
	void OnBtnClose( SDL_Widget * button );

protected:
	SDL_Toolbar	*		m_toolbar;
	SDL_ListBox	*		m_listbox;
	SDL_ImageList *		m_imgList;
	int					m_nClick;
};
