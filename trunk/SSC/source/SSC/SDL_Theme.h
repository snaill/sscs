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

#ifndef SDL_THEME_H_INCLUDED
#define SDL_THEME_H_INCLUDED

#include "SDL_Object.h"
#include "SDL_Font.h"
#include <map>

// @brief …Ë÷√¿‡
class SDL_Theme : public SDL_Object
{
public:
	enum {
		BigText,
		Text,
		Selected
	};

public:
	virtual SDL_Color GetColor( int nParam ) = 0;
	virtual int GetValue( int nParam ) = 0;
	virtual SDL_Font * GetFont( int nParam ) = 0;
};

class SDL_DefaultTheme : public SDL_Theme
{
public:
    SDL_DefaultTheme()   {
		m_pTextFont = 0;
		m_pBigTextFont = 0;
    }

    ~SDL_DefaultTheme()  {
		for ( std::map<int, SDL_Font *>::const_iterator pos = m_mapFonts.begin(); pos != m_mapFonts.end(); pos ++ )
			(*pos).second->Release();
		m_mapFonts.clear();
    }

	virtual const char * GetType()	{ return "defaulttheme"; }

	SDL_Color GetColor( int nParam ) {
		SDL_Color	color;
		switch ( nParam )
		{
		case Text:
			color.r = color.g = color.b = 255; color.unused = 0;
			break;
		case Selected:
			color.r = 255; color.g = 0; color.b = 0; color.unused = 0;
			break;
		default:
			color.r = color.g = color.b = color.unused = 0;
		}

		return color;
	}

	int GetValue( int nParam ){
		return 0;
	}

	SDL_Font * GetFont( int nParam )	{
		if ( m_mapFonts.find( nParam ) == m_mapFonts.end() )
		{
			switch ( nParam )
			{
			case Text: 
				m_mapFonts[ nParam ] = new SDL_Font( "C:\\Windows\\Fonts\\arial.ttf", 12 );
				break;
			case BigText:
				m_mapFonts[ nParam ] = new SDL_Font( "C:\\Windows\\Fonts\\arial.ttf", 24 );
				break;
			default:
				return 0;
			}
		}

		return ( SDL_Font * )m_mapFonts[ nParam ]->GetObj();
	}

protected:
	std::map<int, SDL_Font *>	m_mapFonts;
	SDL_Font *		m_pTextFont;
	SDL_Font *		m_pBigTextFont;
};

#endif // SDL_THEME_H_INCLUDED
