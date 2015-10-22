/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
\*---------------------------------------------------------------------------*/

#include "Point.h"

using namespace boost::numeric::ublas;

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * *//

Point::Point() 
{
}

Point::Point( vector<double> position )
{
	m_position = position;
}

Point::Point( double x, double y, double z )
{
	m_position.resize( 3 );
	m_position[ 0 ] = x;
	m_position[ 1 ] = y;
	m_position[ 2 ] = z;
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Point::setIndex( int index )
{
	m_index = index;
}

void Point::setPosition( vector<double> position )
{
	m_position = position;
}

int Point::getIndex()
{
	return m_index;
}

vector<double> Point::getCoordinate()
{
	return m_position;
}

double Point::getCoordinate( int i )
{
	return m_position[ i ];
}

// ************************************************************************* //