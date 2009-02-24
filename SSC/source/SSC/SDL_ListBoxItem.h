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

#ifndef SDL_LISTBOXITEM_H_INCLUDED
#define SDL_LISTBOXITEM_H_INCLUDED

#include "SDL_Widget.h"
#include "SDL_ImageList.h"
#include "SDL_Label.h"
#include "SDL_Image.h"
#include "SDL_BorderLayout.h"
#include <SDL_ttf.h>

/// @brief 所有图元对象的基类，包含对象的计数操作
class SDL_ListBoxItem : public SDL_Widget
{
public:
	SDL_ListBoxItem( const wchar_t * text, const wchar_t * remark, SDL_Image * image ) {
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

    SDL_ListBoxItem( const wchar_t * text, const wchar_t * remark, SDL_ImageList * imgList, int iImage ) {
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

    virtual ~SDL_ListBoxItem()		{}

	virtual const char * GetType()	{ return "listboxitem"; }
	//virtual SDL_Size GetPreferedSize();

    /// @brief 在制定区域绘制图元
    /// @param screen	屏幕Surface
	virtual void DrawWidget( SDL_Surface * screen );

	//virtual bool OnMouseDown( const SDL_MouseButtonEvent * button, bool * bDraw )	{
	//	if ( !IsIn( button->x, button->y ) )
	//		return false;

	//	if ( button->button == SDL_BUTTON_LEFT )
	//		click( this );
	//	return false;
	//}
};

#endif //!SDL_LISTBOXITEM_H_INCLUDED
