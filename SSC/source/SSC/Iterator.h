#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <vector>

////////////////////////////////////////////////
//
template <class T>
class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual BOOL IsDone() = 0;
	virtual T GetCurrentItem() = 0;

	virtual void GetPos( void * ) = 0;
	virtual void SetPos( void * ) = 0;

	virtual void Release() { delete this; }

protected:
	Iterator()	{}
	virtual ~Iterator(){}
};

//////////////////////////////////////////////////
//
template <class T>
class CVectorIterator : public Iterator<T>
{
protected:
	std::vector<T> *	m_vector;
	int					m_nIndex;
	int					m_nStart;

public:
	CVectorIterator( std::vector<T> * vector, int nStart = 0 )	{
		m_vector = vector;
		m_nIndex = 0;
		m_nStart = nStart;
	}

	virtual void First()	{
		m_nIndex = 0;
	}

	virtual void Next()		{
		m_nIndex ++;
	}

	virtual BOOL IsDone()	{
		return m_nIndex + m_nStart >= (int)m_vector->size(); 		
	}

	virtual T GetCurrentItem() {
		return (*m_vector)[m_nIndex + m_nStart];
	}

	virtual void GetPos( void * p )	{
		int * n = ( int * )p;
		*n = IsDone() ? -1 : m_nIndex;
	}

	virtual void SetPos( void * p )	{
		int * n = ( int * )p;
		m_nIndex = *n; 
	}

};

//////////////////////////////////////////////////
//
template <class T>
class CVectorIteratorR : public Iterator<T>
{
protected:
	std::vector<T> *	m_vector;
	int					m_nIndex;

public:
	CVectorIteratorR( std::vector<T> * vector )	{
		m_vector = vector;
		m_nIndex = 0;
	}

	virtual void First()	{
		m_nIndex = m_vector->size() - 1;
	}

	virtual void Next()		{
		m_nIndex --;
	}

	virtual BOOL IsDone()	{
		return m_nIndex < 0; 		
	}

	virtual T GetCurrentItem() {
		return (*m_vector)[m_nIndex];
	}

	virtual void GetPos( void * p )	{
		int * n = ( int * )p;
		*n = IsDone() ? -1 : m_nIndex;
	}

	virtual void SetPos( void * p )	{
		int * n = ( int * )p;
		m_nIndex = *n; 
	}

};

/////////////////////////////////////////////////////
// 二分法遍历vector结构
template <class T>
class CVector2Iterator : public Iterator<T>
{
protected:
	std::vector<T> *	m_vector;
	int					m_nBegin;
	int					m_nEnd;
public:
	CVector2Iterator( std::vector<T> * vector )	{
		m_vector = vector;
		First();
	}

	virtual void First()	{
		m_nBegin = 0;
		m_nEnd = m_vector->size();
	}

	virtual void Next()		{
		m_nBegin = ( m_nBegin + m_nEnd ) / 2;
	}

	virtual BOOL IsDone()	{
		return m_nEnd - m_nBegin <= 1; 		
	}

	virtual T GetCurrentItem() {
		return (*m_vector)[ ( m_nBegin + m_nEnd ) / 2 ];
	}

	virtual void GetPos( void * p)	{
		int * n = ( int * )p;
		*n ( m_nBegin + m_nEnd ) / 2;
	}

	virtual void SetPos( void * )	{
	}
};
#endif //!__ITERATOR_H