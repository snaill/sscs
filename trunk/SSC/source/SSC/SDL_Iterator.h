#ifndef __SDL_ITERATOR_H
#define __SDL_ITERATOR_H

#include "SDL_Glyph.h"
#include <vector>

//////////////////////////////////////////////////
//
template< class T >
class SDL_Iterator 
{
protected:
	std::vector<SDL_Glyph *>::iterator	m_pos;
	std::vector<SDL_Glyph *>			m_vector;

public:
	SDL_Iterator( )	{}
	~SDL_Iterator( ){
		Clear();
	}

	virtual void First()	{
		m_pos = m_vector.begin();
	}

	virtual void Next()	{
		if ( !IsDone() )
			m_pos ++;
	}
	virtual bool IsDone()	{
		return m_pos == m_vector.end(); 		
	}
	virtual T * GetCurrentItem(){
		return IsDone() ? 0 : dynamic_cast<T *>(*m_pos);
	}

	void Add( SDL_Glyph * p )	{
		m_vector.push_back( p );
	}

	void Clear()	{
		for ( size_t i = 0; i < m_vector.size(); i ++ )
			m_vector[i]->Release();
		m_vector.clear();
	}
};

#endif //!__SDL_ITERATOR_H