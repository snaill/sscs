#pragma once

#include "SSC/SDL_SimpleControls.h"

class CFileView
{
public:
	CFileView(void);
	~CFileView(void);

	operator SDL_Glyph *() {
		return m_this;
	}

protected:
	SDL_Widget *		m_this;
};
