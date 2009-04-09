#pragma once

#include "SSC/SDL_SimpleControls.h"

class CView2 : public SDL_Window, public sigslot::has_slots<>
{
public:
	CView2(void);
	~CView2(void);

	void OnBtnReturn( SDL_Widget * button );

};
