#ifndef SDL_IMAGE_H_INCLUDED
#define SDL_IMAGE_H_INCLUDED

#include "SDL_Glyph.h"

class SDL_Image :	public SDL_Glyph
{
protected:
	SDL_Surface	*	m_pBitmap;

public:
	SDL_Image( const char * );
	virtual ~SDL_Image(void);

	virtual const char * GetType()				{ return "image"; }

	virtual void GetBounds( SDL_Rect  * );
	virtual void Draw( SDL_Surface * screen );
};

#endif //!SDL_IMAGE_H_INCLUDED
