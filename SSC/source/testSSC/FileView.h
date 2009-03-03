#pragma once

#include "SSC/SDL_SimpleControls.h"

class CFileView : public sigslot::has_slots<>
{
public:
	CFileView(void);
	~CFileView(void);

	operator SDL_Widget *() {
		return m_this;
	}

	void OnToolButtonClick( SDL_Widget * button );
	void OnItemSelected( SDL_ListBoxItem * button );

protected:
	SDL_Widget *		m_this;
	SDL_Toolbar	*		m_toolbar;
	SDL_ListBox	*		m_listbox;
	SDL_ImageList *		m_imgList;
	int					m_nClick;
};
