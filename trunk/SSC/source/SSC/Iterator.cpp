#include "Iterator.h"
#include "SDL_Widget.h"

SDL_Iterator::SDL_Iterator( std::vector<SDL_Widget *> * vector )	
{
	m_vector = vector;
	First();
}

void SDL_Iterator::First()	
{
	m_pos = m_vector->begin();
	if ( !IsDone() && !GetCurrentItem()->IsShow() )
		Next();
}

void SDL_Iterator::Next()		
{
	m_pos ++;
	while ( !IsDone() )
	{
		if ( GetCurrentItem()->IsShow() )
			break;
		m_pos ++;
	}
}

bool SDL_Iterator::IsDone()	
{
	return m_pos == m_vector->end(); 		
}

SDL_Widget * SDL_Iterator::GetCurrentItem() 
{
	return IsDone() ? 0 : *m_pos;
}

//////////////////////////////////////////////////
//

SDL_IteratorR::SDL_IteratorR( std::vector<SDL_Widget *> * vector )	{
	m_vector = vector;
	First();
}

void SDL_IteratorR::First()	
{
	m_pos = m_vector->rbegin();
	if ( !IsDone() && !GetCurrentItem()->IsShow() )
		Next();
}

void SDL_IteratorR::Next()		
{
	m_pos ++;
	while ( !IsDone() )
	{
		if ( GetCurrentItem()->IsShow() )
			break;
		m_pos ++;
	}
}

bool SDL_IteratorR::IsDone()	
{
	return m_pos == m_vector->rend(); 		
}

SDL_Widget * SDL_IteratorR::GetCurrentItem() 
{
	return IsDone() ? 0 : *m_pos;
}
