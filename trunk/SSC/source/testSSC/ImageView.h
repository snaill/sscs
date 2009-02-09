#pragma once

#include "SSC/SDL_SimpleControls.h"

class CImageView
{
public:
	CImageView(void);
	~CImageView(void);

	operator SDL_Widget *() {
		return m_this;
	}

protected:
	SDL_Widget *		m_this;
};
