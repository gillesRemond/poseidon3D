/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
   
Author
	Gilles Remond

Class
	Point

Description
	A point is defined with a double vector containing the 3 coordinates (x, y, z).

SourceFiles
	Point.cpp

\*---------------------------------------------------------------------------*/

#pragma once

#include <boost/numeric/ublas/vector.hpp>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


/*---------------------------------------------------------------------------*\
                           Class Point Declaration
\*---------------------------------------------------------------------------*/

class Point
{
private :

	// Private data

		//- Index
		int m_index;

		//- Coordinates of the point
		boost::numeric::ublas::vector<double> m_position;

public :

	// Constructors

		//- Construct null
		Point();

		//- Construct given a vector
		Point( boost::numeric::ublas::vector<double> position );

		//- Construct given three doubles
		Point( double const& x, double const& y, double const& z );

	// Member Functions

		//- Set the point index
		void setIndex( int index );

		//- Set the position
		void setPosition(boost::numeric::ublas::vector<double> position);

		//- Return the point index
		int getIndex();

		//- Return the position
		boost::numeric::ublas::vector<double> getCoordinate();

		//- Return the ith coordinate
		double getCoordinate( int i );

};

// ************************************************************************* //