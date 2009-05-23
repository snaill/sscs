#pragma once

#include "SSC/SDL_SimpleControls.h"

class CView3 : public SDL_Window, public sigslot::has_slots<>
{
public:
	CView3(void);
	~CView3(void);

	void OnToolButtonClick( SDL_Glyph * button );
	void OnItemSelected( SDL_ListItem * button );
	void OnBtnClose( SDL_Glyph * button );

protected:
	SDL_Toolbar	*		m_toolbar;
	SDL_ListBox	*		m_listbox;
	SDL_ImageList *		m_imgList;
	int					m_nClick;
};
