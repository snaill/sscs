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
#include <SDL_gfxPrimitives.h>

SDL_ListBoxItem::SDL_ListBoxItem( const wchar_t * text, const wchar_t * remark, SDL_Image * image ) 
	: m_bSelected( false ) 
{
	if ( image )
	{
		image->SetLayoutProperty( SDL_BorderLayout::west );
		Add( image );
	}

	if ( remark )
	{
		SDL_Label * remarkLabel = new SDL_Label( remark, SDL_Theme::Text, SDL_Theme::Text, -1 );
		remarkLabel->SetLayoutProperty( SDL_BorderLayout::south );
		Add( remarkLabel );
	}

	SDL_Label * textLabel = new SDL_Label( text, SDL_Theme::BigText, SDL_Theme::Text, -1 );
	textLabel->SetLayoutProperty( SDL_BorderLayout::fill );
	Add( textLabel );

	SetLayout( new SDL_BorderLayout() );
}

SDL_ListBoxItem::SDL_ListBoxItem( const wchar_t * text, const wchar_t * remark, SDL_ImageList * imgList, int iImage ) : m_bSelected( false )
{
	if ( imgList )
	{
		SDL_Image * img = new SDL_Image( imgList, iImage );
		img->SetLayoutProperty( SDL_BorderLayout::west );
		Add( img );
	}

	if ( remark )
	{
		SDL_Label * remarkLabel = new SDL_Label( remark, SDL_Theme::Text, SDL_Theme::Text, -1 );
		remarkLabel->SetLayoutProperty( SDL_BorderLayout::south );
		Add( remarkLabel );
	}

	SDL_Label * textLabel = new SDL_Label( text, SDL_Theme::BigText, SDL_Theme::Text, -1 );
	textLabel->SetLayoutProperty( SDL_BorderLayout::fill );
	Add( textLabel );

	SetLayout( new SDL_BorderLayout() );
}

void SDL_ListBoxItem::DrawWidget( SDL_Surface * screen  )   
{
    //打开字体文件并设置字体大小
	SDL_Theme * theme = SDL_MainFrame::Get()->GetTheme();

	SDL_Color	color = theme->GetColor( SDL_Theme::Text );
	SDL_Color	crSelect = theme->GetColor( SDL_Theme::Selected );

	SDL_Rect	rc = GetBounds();
	int			x = m_pt.x;

	if ( GetSelected() )
		SDL_FillRect( screen, ( SDL_Rect * )&rc, SDL_MapRGB( screen->format, crSelect.r, crSelect.g, crSelect.b ) );

	//
	SDL_Container::DrawWidget( screen );

	hlineRGBA( screen, m_pt.x + 4, m_pt.x + m_sz.w - 4, m_pt.y + m_sz.h - 1, color.r, color.g, color.b, 100 ); 
}
