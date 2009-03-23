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

#ifndef SDL_CONTAINER_H_INCLUDED
#define SDL_CONTAINER_H_INCLUDED

#include "SDL_Glyph.h"
#include "SDL_Layout.h"
#include "SDL_Iterator.h"

/// @brief �ؼ���Ļ���
class SDL_Container : public SDL_Glyph
{
public:
	SDL_Container() : m_pLayout(0) {}

	virtual ~SDL_Container() {
		log_f_start( "~SDL_Container" );

		if ( m_pLayout )
			m_pLayout->Release();
				
        Clear();
		log_f_end( "~SDL_Container" );
	}

	virtual const char * GetType() { return "SDL_Container"; }

	/// @brief ��ȡͼԪ�������С����
    /// @param w ���صľ��ο��
    /// @param h ���صľ��ο��
	virtual SDL_Size GetPreferedSize()	{
		log_f_start( "GetPreferedSize" );

		if ( GetLayout() )
			return GetLayout()->GetPreferedSize( this );

		log_f_end( "GetPreferedSize" );
		return SDL_Size( 0, 0 );
	}

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void SetBounds( const SDL_Rect * lprc ){
		SDL_Glyph::SetBounds( lprc );

		if ( GetLayout() )
			GetLayout()->Update( this, lprc );
	}

// ��ͼԪ����
public:
    /// ���һ��ͼԪ
    virtual bool Add( SDL_Glyph * g )
    {
		log_f_start( "Add" );

		assert( g );
        m_aChildren.push_back( g );

		log_f_end( "Add" );
       return true;
    }

    /// ɾ��һ��ͼԪ
    virtual void Remove( SDL_Glyph * g )
    {
		log_f_start( "Remove" );

        assert( g );
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( g == *pos ) {
                m_aChildren.erase( pos );
			}
		}

		log_f_end( "Remove" );
    }

    /// ���������ͼԪ
    virtual void Clear()
    {
		log_f_start( "Clear" );

		for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			(*pos)->Release();
		}
		m_aChildren.clear();

		log_f_end( "Clear" );
    }

	template < class T >	
	void GetIterator( SDL_Iterator<T> * iter, bool r = false )	{
		if ( !r )
		{
	        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
			{
				T * pItem = dynamic_cast<T *>( *pos );
				if ( pItem )
					iter->Add( pItem->GetObj<T>() );
			}
		}
		else
		{
			for ( std::vector<SDL_Glyph *>::reverse_iterator pos = m_aChildren.rbegin(); pos != m_aChildren.rend(); pos ++ )
			{
				T * pItem = dynamic_cast<T *>( *pos );
				if ( pItem )
					iter->Add( pItem->GetObj<T>() );
			}
		}
	}

    /// ��ȡ��ͼԪ����
    virtual size_t	GetCount()
    {
        return m_aChildren.size();
    }

    /// ��ȡ��Ӧ�±����ͼԪ
    virtual SDL_Glyph * GetItem( size_t index )
    {
		if ( index < 0 || index >= GetCount() )
			return NULL;

        return m_aChildren[index];
    }

    virtual int GetItemID( SDL_Glyph * pItem )
    {
		for ( size_t i = 0; i < GetCount(); i ++ )
			if ( pItem == m_aChildren[ i ] )
				return i;

		return -1;
    }

public:
	virtual void RecalcLayout()	{ 
		if ( !GetLayout() )
			return;

		GetLayout()->Update( this, &GetBounds() );
//		RedrawWidget();
	}

	virtual void RedrawWidget()	{
		SDL_Event	event;
		event.type = SDL_VIDEOEXPOSE;
		SDL_PushEvent( &event );
	}

	///
    virtual SDL_Layout * GetLayout(){ 
		if ( !m_pLayout )
			m_pLayout = DefaultLayout();
		return m_pLayout;	
	}
    virtual void SetLayout( SDL_Layout * layout ){ m_pLayout = layout; }

protected:
	virtual SDL_Layout * DefaultLayout() { return 0; }

    /// @brief ���Ƶ�ǰͼԪ
    /// @param screen	��ĻSurface
	virtual void DrawWidget( SDL_Surface * screen, const SDL_Rect * lprc ) {
		if ( GetLayout() )
			GetLayout()->DrawWidget( this, screen );
	}

protected:
    /// ��ͼԪ�б�
	std::vector<SDL_Glyph *>	m_aChildren;
    /// �ͻ�����������ͼԪ�򲼾�
	SDL_Layout *	m_pLayout;
};

#endif // SDL_CONTAINER_H_INCLUDED
