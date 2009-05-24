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

#include "SDL_MenuListItem.h"
#include "SSC/SDL_WindowManager.h"
#include <SDL_gfxPrimitives.h>

SDL_MenuListItem::SDL_MenuListItem( SDL_Label * text ) 
{
	SDL_Label * label = new SDL_Label( L">" );
	label->SetLayoutProperty( SDL_BorderLayout::east );
	label->SetFont( SDL_FONTSIZE_NORMAL );
	label->SetColor( SDL_Theme::BtnText );
	label->SetAlign( -1 );
	label->SetVAlign( 0 );
	Add( label );

	assert( text );
	text->SetLayoutProperty( SDL_BorderLayout::fill );
	text->SetFont( SDL_FONTSIZE_BIG );
	text->SetColor( SDL_Theme::BtnText );
	text->SetAlign( -1 );
	text->SetVAlign( 0 );	
	Add( text );
}

SDL_Size SDL_MenuListItem::GetPreferedSize()	
{
	SDL_Size sz = SDL_ListItem::GetPreferedSize();
	sz.w += 30;
	sz.h += 10;
	return sz;
}

void SDL_MenuListItem::SetBounds( const SDL_Rect * lprc ) 
{
	SDL_Rect	rc = *lprc;
	rc.x += 15;
	rc.w -= 30;
	rc.y += 5;
	rc.h -= 10;
	SDL_ListItem::SetBounds( &rc );
	SDL_BoundingBox::SetBounds( lprc );
}

void SDL_MenuListItem::DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_WindowManager::Get()->GetTheme();

	SDL_Color	color = theme->GetColor( SDL_Theme::BtnText );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	int			x = m_pt.x;

	if ( GetSelected() )
		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, crSelect.r, crSelect.g, crSelect.b ) );

	rc.x += 15;
	rc.w -= 20;
	rc.y += 5;
	rc.h -= 10;

	//
	SDL_BorderLayout::DrawWidget( screen, lprc );

	hlineRGBA( screen, m_pt.x + 4, m_pt.x + m_sz.w - 4, m_pt.y + m_sz.h - 1, color.r, color.g, color.b, 100 ); 
}
