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

// 基本属性
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

		// h参数初始化为0，它用于调整hash值
		unsigned int h = 0;
		unsigned int g;

		// 对p所指的字符串进行逐字符遍历
		wchar_t *	p = ( wchar_t * )lpsz;
		for( ; *p; ++p )
		{
			// h的值左移四位（相当于乘以16）再加上当前字符的ASCII码
			h = ( h << 4 ) + *p;

			// 将h值的高字节的前4位赋给g的相应位，g的其它位置0，并判断g（实际上是h的高字节的前4位）是否为0
			if( g = h & 0xf0000000 )
			{
				// 如果为0，则将h的31~28位及7~4位依次与g作异或，结果传回h
				h = h ^ ( g >> 24 );
				h = h ^ g;
			}
			// 继续下一字符
		}

		// 返回h除PRIME的余数，PRIME实际上是哈希值的范围，通常认为取质数效果较好
		return h % PRIME;
	}
protected:
	ImageMap	m_images;
};

#endif //!SDL_IMAGEMAP_H_INCLUDED
