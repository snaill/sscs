#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <vector>
class SDL_Widget;
////////////////////////////////////////////////
//
class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual SDL_Widget * GetCurrentItem() = 0;

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
	std::vector<SDL_Widget *>::iterator	m_pos;
	std::vector<SDL_Widget *>			m_vector;

public:
	SDL_Iterator( const std::vector<SDL_Widget *> * vector );
	~SDL_Iterator( );

	virtual void First();

	virtual void Next();
	virtual bool IsDone();
	virtual SDL_Widget * GetCurrentItem();
};

//////////////////////////////////////////////////
//
class SDL_IteratorR : public Iterator
{
protected:
	std::vector<SDL_Widget *>::reverse_iterator	m_pos;
	std::vector<SDL_Widget *>					m_vector;

public:
	SDL_IteratorR( const std::vector<SDL_Widget *> * vector );
	~SDL_IteratorR( );

	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual SDL_Widget * GetCurrentItem();
};

#endif //!__ITERATOR_H