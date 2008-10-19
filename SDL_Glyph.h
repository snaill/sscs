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

    /// ��ͼԪ�б�
	std::vector<SDL_Glyph *>	m_aChildren;

// ��������
public:
    virtual ~SDL_Glyph()					{}

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
        {
            Clear();
            delete this;
        }
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
        if ( ( x < m_rc.x || x > m_rc.x + m_rc.w )
                || ( y < m_rc.y || y > m_rc.y + m_rc.h ) )
            return false;

        return true;
    }

    /// @brief �����¼�
    /// @param evnet �¼���Ϣ
 	virtual bool HandleEvent(const SDL_Event *event)
	{
        for ( std::vector<SDL_Glyph *>::iterator pos = m_aChildren.begin(); pos != m_aChildren.end(); pos ++ )
            if ( (*pos)->HandleEvent( event ) )
                return true;
	    return false;
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
    SDL_Glyph() : m_nRef(1)
    {
        memset( &m_rc, 0x00, sizeof( SDL_Rect ) );
    }

    ///
    void DrawPixel( SDL_Surface *screen, int x, int y, Uint32 color );
    void DrawLine( SDL_Surface *screen, int x, int y, int x2, int y2, Uint32 color );
    void DrawRgn( SDL_Surface *screen, int* xs, int* ys, int count, Uint32 color, bool bClose );
    void DrawRect( SDL_Surface *screen, SDL_Rect rect, Uint32 color );
    void Draw3DRect( SDL_Surface *screen, SDL_Rect rect, Uint32 clrTopLeft, Uint32 clrBottomRight );
};

#endif //!SDL_GLYPH_H_INCLUDED
