#include "SDL_Iterator.h"

SDL_Iterator<T>::SDL_Iterator()	
{
}

SDL_Iterator<T>::~SDL_Iterator()
{
	Clear();
}

void SDL_Iterator<T>::First()	
{
	m_pos = m_vector.begin();
}

void SDL_Iterator<T>::Next()		
{
	if ( !IsDone() )
		m_pos ++;
}

bool SDL_Iterator::IsDone()	
{
	return m_pos == m_vector.end(); 		
}

T * SDL_Iterator::GetCurrentItem() 
{
	return IsDone() ? 0 : *m_pos;
}

void SDL_Iterator::Add( T * p )
{
	m_vector.push_back( p );
}

void SDL_Iterator::Clear()
{
	for ( size_t i = 0; i < m_vector.size(); i ++ )
		m_vector[i]->Release();
	m_vector.clear();
}