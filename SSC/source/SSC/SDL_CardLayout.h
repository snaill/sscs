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

#ifndef SDL_CARDLAYOUT_H_INCLUDED
#define SDL_CARDLAYOUT_H_INCLUDED

#include "SDL_Layout.h"

/// @brief ���н��沼�ֵĻ��࣬ʵ�̶ֹ�����
class SDL_CardLayout : public SDL_Layout
{
// ��������
public:
	SDL_CardLayout() : m_nActiveItem(0)  	{ }
    virtual ~SDL_CardLayout()				{ }

	virtual const char * GetType()				{ return "cardlayout"; }
	
// ����
public:
	virtual SDL_Size GetPreferedSize( SDL_Container * pContainer )	{
		SDL_Glyph * p = pContainer->GetItem( m_nActiveItem );
		return p ? p->GetPreferedSize() : SDL_Size( 0, 0 );
	}

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void Update( SDL_Container * pContainer, const SDL_Rect * lprc )
    {
		if ( m_nActiveItem >= (int)pContainer->GetCount() )
			return;
		
		SDL_Glyph * p = pContainer->GetItem( m_nActiveItem );
		if ( p )
			p->SetBounds( lprc );
    }

protected:
	int			m_nActiveItem;
};

#endif // SDL_CARDLAYOUT_H_INCLUDED
