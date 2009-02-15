#include "Iterator.h"
#include "SDL_Widget.h"

SDL_Iterator::SDL_Iterator( const std::vector<SDL_Widget *> * vector )	
{
	for ( size_t i = 0; i < vector->size(); i ++ )
		m_vector.push_back( ( SDL_Widget * )(*vector)[i]->GetObj() );
	First();
}

SDL_Iterator::~SDL_Iterator()
{
	for ( size_t i = 0; i < m_vector.size(); i ++ )
		m_vector[i]->Release();
	m_vector.clear();
}

void SDL_Iterator::First()	
{
	m_pos = m_vector.begin();
	if ( !IsDone() && !GetCurrentItem()->GetVisible() )
		Next();
}

void SDL_Iterator::Next()		
{
	m_pos ++;
	while ( !IsDone() )
	{
		if ( GetCurrentItem()->GetVisible() )
			break;
		m_pos ++;
	}
}

bool SDL_Iterator::IsDone()	
{
	return m_pos == m_vector.end(); 		
}

SDL_Widget * SDL_Iterator::GetCurrentItem() 
{
	return IsDone() ? 0 : *m_pos;
}

//////////////////////////////////////////////////
//

SDL_IteratorR::SDL_IteratorR( const std::vector<SDL_Widget *> * vector )	{
	for ( size_t i = 0; i < vector->size(); i ++ )
		m_vector.push_back( ( SDL_Widget * )(*vector)[i]->GetObj() );
	First();
}

SDL_IteratorR::~SDL_IteratorR()
{
	for ( size_t i = 0; i < m_vector.size(); i ++ )
		m_vector[i]->Release();
	m_vector.clear();
}

void SDL_IteratorR::First()	
{
	m_pos = m_vector.rbegin();
	if ( !IsDone() && !GetCurrentItem()->GetVisible() )
		Next();
}

void SDL_IteratorR::Next()		
{
	m_pos ++;
	while ( !IsDone() )
	{
		if ( GetCurrentItem()->GetVisible() )
			break;
		m_pos ++;
	}
}

bool SDL_IteratorR::IsDone()	
{
	return m_pos == m_vector.rend(); 		
}

SDL_Widget * SDL_IteratorR::GetCurrentItem() 
{
	return IsDone() ? 0 : *m_pos;
}
