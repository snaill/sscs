/*
 * SDL_SimpleControls
 * Copyright (C) 2008 Snaill
 *
    SDL_SimpleControls is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SDL_SimpleControls is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Snaill  <snaill@jeebook.com>
 */

#ifndef SDL_IMAGEMAP_H_INCLUDED
#define SDL_IMAGEMAP_H_INCLUDED

#include "SDL_Object.h"
#include "SDL_Image.h"
#include <stdio.h>
#include <map.h>

/// @brief ImageList
class SDL_ImageMap : public SDL_Object
{
	typedef std::map<unsigned long, SDL_Image *>	ImageMap;

// »ù±¾ÊôÐÔ
public:
	SDL_ImageMap() {}

    virtual ~SDL_ImageMap()	{
		Clear();
	}

	virtual const char * GetType()	{ return "SDL_ImageMap"; }

	void Add( const wchar_t * key, SDL_Image * image ) {
		unsigned long uKey = GetHash32( key );
		ImageMap::const_iterator pos = m_images.find( uKey );
		if ( pos != m_images.end() )
			(*pos).second->Release();

		m_images[uKey] = image;
	}

	void Remove( const wchar_t * key )	{
		unsigned long uKey = GetHash32( key );
		ImageMap::const_iterator pos = m_images.find( uKey );
		if ( pos != m_images.end() )
		{
			(*pos).second->Release();
			m_image.erase( pos );
		}
	}

	void Clear()	{
		for ( ImageMap::const_iterator pos = m_images.begin(); pos != m_images.end(); pos ++ )
			(*pos).second->Release();
		m_images.clear();	
	}


	SDL_Image * GetImage( const wchar_t * key )	{
		unsigned long uKey = GetHash32( key );
		ImageMap::const_iterator pos = m_images.find( uKey );
		if ( pos == m_images.end() )
			return 0;

		return ( SDL_Image * )(*pos).second->GetObj();
	}
protected:
	ImageMap	m_images;
};

#endif //!SDL_IMAGEMAP_H_INCLUDED
