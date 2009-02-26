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

/// @brief �ؼ���Ļ���
class SDL_Container : public SDL_Glyph
{
public:
	SDL_Container() : m_pLayout(0) {}

	virtual ~SDL_Container() {
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::~%s Start\n", GetType(), GetType() );

		if ( m_pLayout )
			m_pLayout->Release();
				
        Clear();
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::~%s End\n", GetType(), GetType() );
	}

	virtual const char * GetType() { return "SDL_Container"; }

	/// @brief ��ȡͼԪ�������С����
    /// @param w ���صľ��ο��
    /// @param h ���صľ��ο��
	virtual SDL_Size GetPreferedSize()	{
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::GetPreferedSize Start\n", GetType() );

		if ( GetLayout() )
			return GetLayout()->GetPreferedSize( this );

		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::GetPreferedSize End\n", GetType() );
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
    virtual bool Add( SDL_Object * g )
    {
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Add Start\n", GetType() );

		assert( g );
		g->SetParent( this );
        m_aChildren.push_back( g );
		add( g );

 		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Add End\n", GetType() );
       return true;
    }

    /// ɾ��һ��ͼԪ
    virtual void Remove( SDL_Object * g )
    {
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Remove Start\n", GetType() );

        assert( g );
        for ( std::vector<SDL_Object *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			if ( g == *pos ) {
                m_aChildren.erase( pos );
				remove( g );
			}
		}

		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Remove End\n", GetType() );
    }

    /// ���������ͼԪ
    virtual void Clear()
    {
		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Clear Start\n", GetType() );

		for ( std::vector<SDL_Object *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
		{
			remove( *pos );
			(*pos)->Release();
		}
		m_aChildren.clear();

		LOG( LOG_LEVEL_FUNCTION_INOUT, "%s::Clear End\n", GetType() );
    }

	//void GetIterator( SDL_Iterator * iter, bool r = false )	{
	//	if ( !r )
	//	{
	//        for ( std::vector<SDL_Widget *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
	//		{
	//			if ( (*pos)->GetVisible() )
	//				iter->Add( ( SDL_Widget * )(*pos)->GetObj() );
	//		}
	//	}
	//	else
	//	{
	//		for ( std::vector<SDL_Widget *>::reverse_iterator pos = m_aChildren.rbegin(); pos != m_aChildren.rend(); pos ++ )
	//		{
	//			if ( (*pos)->GetVisible() )
	//				iter->Add( ( SDL_Widget * )(*pos)->GetObj() );
	//		}
	//	}
	//}

    /// ��ȡ��ͼԪ����
    virtual size_t	GetCount()
    {
        return m_aChildren.size();
    }

    /// ��ȡ��Ӧ�±����ͼԪ
    virtual SDL_Widget * GetItem( size_t index )
    {
		if ( index < 0 || index >= GetCount() )
			return NULL;

        return m_aChildren[index];
    }

    virtual int GetItemID( SDL_Widget * pItem )
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
    virtual SDL_Layout * GetLayout(){ return m_pLayout;	}
    virtual void SetLayout( SDL_Layout * layout ){ m_pLayout = layout; }
    virtual int GetLayoutProperty(){ return m_nLayoutProperty;	}
    virtual void SetLayoutProperty( int layoutProperty ){ m_nLayoutProperty = layoutProperty; }

protected:
    /// @brief ���Ƶ�ǰͼԪ
    /// @param screen	��ĻSurface
	virtual void DrawWidget( SDL_Surface * screen ) {
		SDL_Iterator pos;
		GetIterator( &pos );
		for ( pos.First(); !pos.IsDone(); pos.Next() )
		{
			SDL_Widget * pItem = pos.GetCurrentItem();
			pItem->Draw( screen );
		}
	}

protected:
    /// ��ͼԪ�б�
	std::vector<SDL_Object *>	m_aChildren;
    /// �ͻ�����������ͼԪ�򲼾�
	SDL_Layout *	m_pLayout;
	int				m_nLayoutProperty;
};

#endif // SDL_CONTAINER_H_INCLUDED
