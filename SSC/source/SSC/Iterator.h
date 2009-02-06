#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <vector>

////////////////////////////////////////////////
//
class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual SDL_Glyph * GetCurrentItem() = 0;

	virtual void Release() { delete this; }

protected:
	Iterator()	{}
	virtual ~Iterator(){}
};

//////////////////////////////////////////////////
//
class SDL_Iterator : public Iterator
{
protected:
	std::vector<SDL_Glyph *>::iterator	m_pos;
	std::vector<SDL_Glyph *> *			m_vector;

public:
	SDL_Iterator( std::vector<SDL_Glyph *> * vector )	{
		m_vector = vector;
		First();
	}

	virtual void First()	{
		m_pos = m_vector->begin();
		if ( !IsDone() && !GetCurrentItem()->IsShow() )
			Next();
	}

	virtual void Next()		{
		m_pos ++;
		while ( !IsDone() )
		{
			if ( GetCurrentItem()->IsShow() )
				break;
			m_pos ++;
		}
	}

	virtual bool IsDone()	{
		return m_pos == m_vector->end(); 		
	}

	virtual SDL_Glyph * GetCurrentItem() {
		return IsDone() ? 0 : *m_pos;
	}
};

//////////////////////////////////////////////////
//
class SDL_IteratorR : public Iterator
{
protected:
	std::vector<SDL_Glyph *>::reverse_iterator	m_pos;
	std::vector<SDL_Glyph *> *					m_vector;

public:
	SDL_IteratorR( std::vector<SDL_Glyph *> * vector )	{
		m_vector = vector;
		First();
	}

	virtual void First()	{
		m_pos = m_vector->rbegin();
		if ( !IsDone() && !GetCurrentItem()->IsShow() )
			Next();
	}

	virtual void Next()		{
		m_pos ++;
		while ( !IsDone() )
		{
			if ( GetCurrentItem()->IsShow() )
				break;
			m_pos ++;
		}
	}

	virtual bool IsDone()	{
		return m_pos == m_vector->rend(); 		
	}

	virtual SDL_Glyph * GetCurrentItem() {
		return IsDone() ? 0 : *m_pos;
	}
};

#endif //!__ITERATOR_H