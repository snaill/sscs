#pragma once

#include "SSC/SDL_SimpleControls.h"

class CImageView : public SDL_Window, public sigslot::has_slots<>
{
public:
	CImageView(void);
	~CImageView(void);

	void OnBtnClose( SDL_Widget * button );

};
