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

#include "SDL_Object.h"

/// @brief ����ͼԪ����Ļ��࣬��������ļ�������
class SDL_Glyph : public SDL_Object, public SDL_BoundingBox
{

// ��������
public:
    /// @brief ��ȡͼԪ�������С����
    /// @param w ���صľ��ο��
    /// @param h ���صľ��ο��
    virtual SDL_Size GetPreferedSize() = 0;

	virtual bool IsShow()			{ return m_bShow;	}
	virtual void Show( bool bShow ) { m_bShow = bShow;	}
    virtual SDL_Glyph * GetParent(){ return m_pParent;	}
    virtual void SetParent( SDL_Glyph * parent ){ m_pParent = parent; }

// ����
public:
    /// @brief ���ƶ��������ͼԪ
    /// @param screen	��ĻSurface
    virtual void Draw( SDL_Surface * screen ) = 0;

    /// @brief �����¼�
    /// @param evnet �¼���Ϣ
	virtual bool HandleMouseEvent(const SDL_Event *event, bool * bDraw ) = 0;

	virtual bool HandleKeyEvent(const SDL_Event *event, bool * bDraw ) = 0;

protected:
    /// ���캯��Ϊ�������ͣ�˵���û��಻��ֱ�Ӵ���
	SDL_Glyph()	: m_bShow( true ), m_pParent(0)		{}

    virtual ~SDL_Glyph(){}

protected:
	SDL_Glyph *		m_pParent;
	bool			m_bShow;
};

#endif //!SDL_GLYPH_H_INCLUDED
