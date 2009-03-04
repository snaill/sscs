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

#include "SDL_ListBoxItem.h"
#include "SDL_MainFrame.h"
#include "SDL_BorderLayout.h"
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

SDL_ListBoxItem::SDL_ListBoxItem( SDL_Label * text, SDL_Label * remark, SDL_Image * image ) 
	: m_bSelected( false ) 
{
	assert( text );

	if ( image )
	{
		image->SetLayoutProperty( SDL_BorderLayout::west );
		Add( image );
	}

	if ( remark )
	{
		remark->SetLayoutProperty( SDL_BorderLayout::south );
		remark->SetFont( SDL_FONTSIZE_NORMAL );
		remark->SetColor( SDL_Theme::WindowText );
		remark->SetAlign( -1 );
		remark->SetVAlign( 0 );
		Add( remark );
	}

	text->SetLayoutProperty( SDL_BorderLayout::fill );
	text->SetFont( SDL_FONTSIZE_BIG );
	text->SetColor( SDL_Theme::WindowText );
	text->SetAlign( -1 );
	text->SetVAlign( 0 );	
	Add( text );
}

void SDL_ListBoxItem::DrawWidget( SDL_Surface * screen  )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_MainFrame::Get()->GetTheme();

	SDL_Color	color = theme->GetColor( SDL_Theme::WindowText );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	int			x = m_pt.x;

	if ( GetSelected() )
		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, crSelect.r, crSelect.g, crSelect.b ) );

	//
	SDL_Container::DrawWidget( screen );

	hlineRGBA( screen, m_pt.x + 4, m_pt.x + m_sz.w - 4, m_pt.y + m_sz.h - 1, color.r, color.g, color.b, 100 ); 
}
