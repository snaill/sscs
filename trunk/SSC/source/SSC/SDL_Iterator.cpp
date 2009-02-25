#include "SDL_Iterator.h"
#include "SDL_Widget.h"

SDL_Iterator::SDL_Iterator()	
{
}

SDL_Iterator::~SDL_Iterator()
{
	Clear();
}

void SDL_Iterator::First()	
{
	m_pos = m_vector.begin();
}

void SDL_Iterator::Next()		
{
	if ( !IsDone() )
		m_pos ++;
}

bool SDL_Iterator::IsDone()	
{
	return m_pos == m_vector.end(); 		
}

SDL_Widget * SDL_Iterator::GetCurrentItem() 
{
	return IsDone() ? 0 : *m_pos;
}

void SDL_Iterator::Add( SDL_Widget * p )
{
	m_vector.push_back( p );
}

void SDL_Iterator::Clear()
{
	for ( size_t i = 0; i < m_vector.size(); i ++ )
		m_vector[i]->Release();
	m_vector.clear();
}