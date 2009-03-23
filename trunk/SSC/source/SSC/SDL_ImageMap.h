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
#include <map>

/// @brief ImageList
class SDL_ImageMap : public SDL_Object
{
	typedef std::map<unsigned long, SDL_Image *>	ImageMap;

// ��������
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
			m_images.erase( pos );
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

		return (*pos).second->GetObj<SDL_Image>();
	}
	
protected:
	unsigned long GetHash32( const wchar_t * lpsz ) {
		const unsigned int PRIME = 4294967291;

		// h������ʼ��Ϊ0�������ڵ���hashֵ
		unsigned int h = 0;
		unsigned int g;

		// ��p��ָ���ַ����������ַ�����
		wchar_t *	p = ( wchar_t * )lpsz;
		for( ; *p; ++p )
		{
			// h��ֵ������λ���൱�ڳ���16���ټ��ϵ�ǰ�ַ���ASCII��
			h = ( h << 4 ) + *p;

			// ��hֵ�ĸ��ֽڵ�ǰ4λ����g����Ӧλ��g������λ��0�����ж�g��ʵ������h�ĸ��ֽڵ�ǰ4λ���Ƿ�Ϊ0
			if( g = h & 0xf0000000 )
			{
				// ���Ϊ0����h��31~28λ��7~4λ������g����򣬽������h
				h = h ^ ( g >> 24 );
				h = h ^ g;
			}
			// ������һ�ַ�
		}

		// ����h��PRIME��������PRIMEʵ�����ǹ�ϣֵ�ķ�Χ��ͨ����Ϊȡ����Ч���Ϻ�
		return h % PRIME;
	}
protected:
	ImageMap	m_images;
};

#endif //!SDL_IMAGEMAP_H_INCLUDED
