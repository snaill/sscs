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

#ifndef SDL_LAYOUT_H_INCLUDED
#define SDL_LAYOUT_H_INCLUDED

#include "SDL_Glyph.h"

/// @brief ���н��沼�ֵĻ��࣬���ṩ�Բ����ڶ���ķ���
class SDL_Layout : public SDL_Glyph
{
// ��������
public:
	virtual const char * GetType()				{ return "boxlayout"; }

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void SetBounds( const SDL_Rect * lprc )
    {
        if ( m_rc.w != lprc->w || m_rc.h != lprc->h )
        {
            SDL_Glyph::SetBounds( lprc );
            ReCalc( );
        }
        else
        {
            if ( m_rc.x != lprc->x || m_rc.y != lprc->y )
            {
                // ���ֻ��λ�ƣ������λ��ƫ����
                SDL_Rect    rect;
                Uint16      xOff = lprc->x - m_rc.x;
                Uint16      yOff = lprc->y - m_rc.y;
                for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
                {
                    (*pos)->GetBounds( &rect );
                    rect.x += xOff;
                    rect.y += yOff;
                    (*pos)->SetBounds( &rect );
                }
            }
        }
    }

// ����
public:
    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
    virtual void Draw( SDL_Surface * screen )
    {
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            (*pos)->Draw( screen );
    }


    /// @brief ������Ӧ���Ƿ���ͼԪ��Χ��
    /// @param x ��Ļ����x
    /// @param y ��Ļ����y
    virtual bool HitTest( int x, int y )
    {
//        if ( ( x < m_rc.x || x > m_rc.x + m_rc.w )
//                || ( y < m_rc.y || y > m_rc.y + m_rc.h ) )
            return false;

//        return true;
    }

    /// @brief �����¼�
    /// @param evnet �¼���Ϣ
 	virtual bool HandleEvent(const SDL_Event *event)
	{
	    bool bHandled = false;
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            if ( (*pos)->HandleEvent( event ) )
                bHandled = true;
	    return bHandled;
	}

// ��ͼԪ����
public:
    /// ���һ��ͼԪ
    virtual bool Add( SDL_Glyph * g )
    {
        assert( g );
        m_aChildren.push_back( g );
        return true;
    }

    /// ɾ��һ��ͼԪ
    virtual void Remove( SDL_Glyph * g )
    {
        assert( g );
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            if ( g == *pos )
                m_aChildren.erase( pos );
    }

    /// ���������ͼԪ
    virtual void Clear()
    {
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
           (*pos)->Release();
        m_aChildren.clear();
    }

    /// ��ȡ��ͼԪ����
    virtual size_t	GetChildCount()
    {
        return m_aChildren.size();
    }

    /// ��ȡ��Ӧ�±����ͼԪ
    virtual SDL_Glyph * GetChild( int index )
    {
        return m_aChildren[index];
    }

protected:
    /// ���캯��Ϊ�������ͣ�˵���û��಻��ֱ�Ӵ���
    SDL_Layout()            { }
    virtual ~SDL_Layout()	{
        Clear();
    }

    virtual void ReCalc( ) = 0;

protected:
    /// ��ͼԪ�б�
	std::vector<SDL_Glyph *>	m_aChildren;
};

#endif // SDL_LAYOUT_H_INCLUDED
