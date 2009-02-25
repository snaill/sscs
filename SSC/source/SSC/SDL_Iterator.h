#ifndef __SDL_ITERATOR_H
#define __SDL_ITERATOR_H

#include <vector>
class SDL_Widget;
//////////////////////////////////////////////////
//
class SDL_Iterator 
{
protected:
	std::vector<SDL_Widget *>::iterator	m_pos;
	std::vector<SDL_Widget *>			m_vector;

public:
	SDL_Iterator( );
	~SDL_Iterator( );

	virtual void First();

	virtual void Next();
	virtual bool IsDone();
	virtual SDL_Widget * GetCurrentItem();

	void Add( SDL_Widget * );
	void Clear();
};

#endif //!__SDL_ITERATOR_H