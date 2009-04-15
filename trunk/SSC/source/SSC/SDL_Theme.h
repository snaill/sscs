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

#define SDL_FONTSIZE_NORMAL		0
#define SDL_FONTSIZE_SMALL		(-1)
#define SDL_FONTSIZE_BIG		1

// @brief …Ë÷√¿‡
class SDL_Theme : public SDL_Object
{
public:
	enum {
		Background,
		BtnFace,
		BtnText,
		Selected,
		SelectedText
	};

public:
	virtual SDL_Color GetColor( int nParam ) = 0;
	virtual int GetValue( int nParam ) = 0;
	virtual SDL_Font * GetFont( int nParam ) = 0;
};

class SDL_DefaultTheme : public SDL_Theme
{
public:
    SDL_DefaultTheme( const char * font )   {
		m_strFont = font;
    }

    ~SDL_DefaultTheme()  {
		for ( std::map<int, SDL_Font *>::const_iterator pos = m_mapFonts.begin(); pos != m_mapFonts.end(); pos ++ )
			(*pos).second->Release();
		m_mapFonts.clear();
    }

	virtual const char * GetType()	{ return "SDL_DefaultTheme"; }

	SDL_Color GetColor( int nParam ) {
		SDL_Color	color;
		switch ( nParam )
		{
		case Background:
			color.r = color.g = color.b = 0xFF; color.unused = 0;
			break;
		case BtnFace:
			color.r = color.g = color.b = 192; color.unused = 0;
			break;
		case BtnText:
			color.r = color.g = color.b = 0; color.unused = 0;
			break;
		case Selected:
			color.r = 0; color.g = 0; color.b = 255; color.unused = 0;
			break;
		case SelectedText:
			color.r = color.g = color.b = 255; color.unused = 0;
			break;
		default:
			color.r = color.g = color.b = 0xFF; color.unused = 0;
		}

		return color;
	}

	int GetValue( int nParam ){
		return 0;
	}

	SDL_Font * GetFont( int nSize )	{
		if ( nSize < -1 || nSize > 1 )
			return 0;

		if ( m_mapFonts.find( nSize ) == m_mapFonts.end() )
		{
			switch ( nSize )
			{
			case -1: 
				m_mapFonts[ nSize ] = new SDL_Font( m_strFont.c_str(), 9 );
				break;
			case 0:
				m_mapFonts[ nSize ] = new SDL_Font( m_strFont.c_str(), 12 );
				break;
			case 1:
				m_mapFonts[ nSize ] = new SDL_Font( m_strFont.c_str(), 24 );
				break;
			default:
				return 0;
			}
		}

		return m_mapFonts[ nSize ]->GetObj<SDL_Font>();
	}

protected:
	std::map<int, SDL_Font *>	m_mapFonts;
	std::string					m_strFont;
};

#endif // SDL_THEME_H_INCLUDED
