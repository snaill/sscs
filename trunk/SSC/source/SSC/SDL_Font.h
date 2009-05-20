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

#ifndef SDL_FONT_H_INCLUDED
#define SDL_FONT_H_INCLUDED

#include "SDL_Object.h"
#include <SDL_ttf.h>

/// @brief �ؼ���Ļ���
class SDL_Font : public SDL_Object
{
// ��������
public:
	SDL_Font( const char * szName, int size )		{
		m_pFont = TTF_OpenFont( szName, size );
	}

	virtual ~SDL_Font()	{
		TTF_CloseFont( m_pFont );
	}

	virtual const char * GetType()				{ return "font"; }

	int GetStyle() { return TTF_GetFontStyle( m_pFont ); }
	void SetStyle( int style )	{
		TTF_SetFontStyle( m_pFont, style );
	}

	SDL_Size GetTextSize( const wchar_t * text )	{
		int w, h;
		TTF_SizeUNICODE( m_pFont, (const Uint16 *)text, &w, &h );
		return SDL_Size( w, h );
	}

	bool DrawText2( SDL_Surface * screen, const wchar_t * text, SDL_Rect rc, SDL_Color color, int align = 0, int valign = 0, bool bHighQuality = true )	{

		//ʹ�ô򿪵�����,���ַ���"��"���ڴ�(��ʾ����)��
		SDL_Surface  *pTextSurface = 0;
		if ( bHighQuality )
			pTextSurface = TTF_RenderUNICODE_Blended( m_pFont, (const Uint16 *)text, color );
		else
			pTextSurface = TTF_RenderUNICODE_Solid( m_pFont, (const Uint16 *)text, color );
	
		// ���Ƶ���Ļ����
		if ( !pTextSurface )
		{
			printf("call TTF_RenderUTF8_Solid failed %s\n", SDL_GetError());
			return false;
		}

		SDL_Rect  rect;
		rect.w = pTextSurface->w;
		rect.h = pTextSurface->h;

		if ( align < 0 )
			rect.x = rc.x;
		else if ( align > 0 )
			rect.x = rc.x + rc.w - rect.w;
		else
			rect.x = rc.x + ( rc.w - rect.w ) / 2;

		if ( valign < 0 )
			rect.y = rc.y;
		else if ( align > 0 )
			rect.y = rc.y + rc.h;
		else
			rect.y = rc.y + ( rc.h - rect.h ) / 2;

		//���ڴ�(��ʾ�����е�)���ݿ�������ǰ��ʾ�豸����
		SDL_BlitSurface( pTextSurface, 0, screen, &rect );

		//�ͷ��ڴ���ʾ����
		SDL_FreeSurface(pTextSurface);
		return true;
	}

	bool DrawText2( SDL_Surface * screen, const wchar_t * text, SDL_Rect rc, SDL_Color color, SDL_Color crBack, int align = 0, int valign = 0 )	{

		//ʹ�ô򿪵�����,���ַ���"��"���ڴ�(��ʾ����)��
		SDL_Surface  *pTextSurface = TTF_RenderUNICODE_Shaded( m_pFont, (const Uint16 *)text, color, crBack );

		// ���Ƶ���Ļ����
		if ( !pTextSurface )
		{
			printf("call TTF_RenderUTF8_Solid failed %s\n", SDL_GetError());
			return false;
		}

		SDL_Rect  rect;
		rect.w = pTextSurface->w;
		rect.h = pTextSurface->h;

		if ( align < 0 )
			rect.x = rc.x;
		else if ( align > 0 )
			rect.x = rc.x + rc.w - rect.w;
		else
			rect.x = rc.x + ( rc.w - rect.w ) / 2;

		if ( valign < 0 )
			rect.y = rc.y;
		else if ( valign > 0 )
			rect.y = rc.y + rc.h;
		else
			rect.y = rc.y + ( rc.h - rect.h ) / 2;

		//���ڴ�(��ʾ�����е�)���ݿ�������ǰ��ʾ�豸����
		SDL_BlitSurface( pTextSurface, 0, screen, &rect );

		//�ͷ��ڴ���ʾ����
		SDL_FreeSurface(pTextSurface);
		return true;
	}
protected:
	TTF_Font *		m_pFont;
};

#endif // SDL_FONT_H_INCLUDED
