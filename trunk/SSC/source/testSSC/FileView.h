#pragma once

#include "SSC/SDL_SimpleControls.h"

class CFileView : public sigslot::has_slots<>
{
public:
	CFileView(void);
	~CFileView(void);

	operator SDL_Glyph *() {
		return m_this;
	}

	void OnToolButtonClick( int index, SDL_ToolButton * button );

protected:
	SDL_Widget *		m_this;
	SDL_Toolbar	*		m_toolbar;
};
