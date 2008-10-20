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

#ifndef SDL_GLYPH_H_INCLUDED
#define SDL_GLYPH_H_INCLUDED

#include "SDL_Setting.h"
#include <assert.h>
#include <vector>
#include <SDL.h>

/// @brief ����ͼԪ����Ļ��࣬��������ļ�������
class SDL_Glyph
{
protected:
    /// ͼԪ������������¼ͼԪ�����õĴ�����
    /// ��ʼΪ1��Ϊ0ʱͼԪ�������ͷ�
    int		m_nRef;

    /// ͼԪ�ľ��η�Χ
    SDL_Rect	m_rc;

// ��������
public:

    /// @brief ��ȡͼԪ���
    /// @return ���ص�ͼԪ���
    virtual const char * GetType() = 0;

    /// ��ȡͼԪ���ã�ͼԪ������1
    virtual SDL_Glyph * GetObject()
    {
        m_nRef ++;
        return this;
    }

    /// �ͷ�ͼԪ��ֻ���ڼ���Ϊ0������£�ͼԪ�Żᱻ����ͷ�
    virtual void Release()
    {
        m_nRef --;
        if ( !m_nRef )
            delete this;
    }

    /// @brief ��ȡͼԪ�������С����
    /// @param w ���صľ��ο��
    /// @param h ���صľ��ο��
    virtual void GetMinSize( int * w, int * h )
    {
        *w = m_rc.w;
        *h = m_rc.h;
    }

    /// @brief ��ȡͼԪ��������
    /// @param lprc ���صľ���λ��
    virtual void GetBounds( SDL_Rect * lprc )
    {
        memcpy( lprc, &m_rc, sizeof( SDL_Rect ) );
    }

    /// @brief ����ͼԪ��������
    /// @param lprc �����þ���λ��
    virtual void SetBounds( const SDL_Rect * lprc )
    {
        memcpy( &m_rc, lprc, sizeof( SDL_Rect ) );
    }

// ����
public:
    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
    virtual void Draw( SDL_Surface * screen ) = 0;

    /// @brief ������Ӧ���Ƿ���ͼԪ��Χ��
    /// @param x ��Ļ����x
    /// @param y ��Ļ����y
    virtual bool HitTest( int x, int y )
    {
        if ( ( x < m_rc.x || x > m_rc.x + m_rc.w )
                || ( y < m_rc.y || y > m_rc.y + m_rc.h ) )
            return false;

        return true;
    }

    /// @brief �����¼�
    /// @param evnet �¼���Ϣ
 	virtual bool HandleEvent(const SDL_Event *event)
 	{
 	    return false;
 	}

protected:
    /// ���캯��Ϊ�������ͣ�˵���û��಻��ֱ�Ӵ���
    SDL_Glyph() : m_nRef(1)
    {
        memset( &m_rc, 0x00, sizeof( SDL_Rect ) );
    }

    virtual ~SDL_Glyph()					{}

    ///
    void DrawPixel( SDL_Surface *screen, int x, int y, Uint32 color );
    void DrawLine( SDL_Surface *screen, int x, int y, int x2, int y2, Uint32 color );
    void DrawRgn( SDL_Surface *screen, int* xs, int* ys, int count, Uint32 color, bool bClose );
    void DrawRect( SDL_Surface *screen, SDL_Rect rect, Uint32 color );
    void Draw3DRect( SDL_Surface *screen, SDL_Rect rect, Uint32 clrTopLeft, Uint32 clrBottomRight );
};

#endif //!SDL_GLYPH_H_INCLUDED
