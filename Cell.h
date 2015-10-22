/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
   
Author
	Gilles Remond

Class
	Cell

Description
	A hexaedral cell is defined with its vertices.

SourceFiles
	Cell.cpp

\*---------------------------------------------------------------------------*/

#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


/*---------------------------------------------------------------------------*\
                           Class Cell Declaration
\*---------------------------------------------------------------------------*/

class Cell
{
private:
	
	// Private data

		//- Cell index
		int m_index;

		//- The front northeastern vertex
		Point* m_vertex_fne;

		//- The front northwestern vertex
		Point* m_vertex_fnw;

		//- The front southeastern vertex
		Point* m_vertex_fse;

		//- The front southwestern vertex
		Point* m_vertex_fsw;

		//- The back northeastern vertex
		Point* m_vertex_bne;

		//- The back northwestern vertex
		Point* m_vertex_bnw;

		//- The back southeastern vertex
		Point* m_vertex_bse;

		//- The back southwestern vertex
		Point* m_vertex_bsw;

		//- The boundary type of the faces
		boost::numeric::ublas::vector<int> m_boundaryTypes;

public:
	
	// Constructors

		//- Construct null
		Cell();

	// Member Functions
		
		// Edit
		
			//- Set the cell index
			void setIndex( int index );

			//- Set the front northeastern vertex
			void setVertex_fne( Point* vertex );

			//- Set the front northwestern vertex
			void setVertex_fnw( Point* vertex );

			//- Set the front southeastern vertex
			void setVertex_fse( Point* vertex );

			//- Set the front southwestern vertex
			void setVertex_fsw( Point* vertex );

			//- Set the back northeastern vertex
			void setVertex_bne( Point* vertex );

			//- Set the back northwestern vertex
			void setVertex_bnw( Point* vertex );

			//- Set the back southeastern vertex
			void setVertex_bse( Point* vertex );

			//- Set the back southwestern vertex
			void setVertex_bsw( Point* vertex );

			//- Set the boundary types
			void setBoundaryTypes( boost::numeric::ublas::vector<int> boundaryTypes );

		// Access

			//- Get the cell index
			int getIndex();

			//- Get the front northeastern vertex
			Point* getVertex_fne();

			//- Get the front northwestern vertex
			Point* getVertex_fnw();

			//- Get the front southeastern vertex
			Point* getVertex_fse();

			//- Get the front southwestern vertex
			Point* getVertex_fsw();

			//- Get the back northeastern vertex
			Point* getVertex_bne();

			//- Get the back northwestern vertex
			Point* getVertex_bnw();

			//- Get the back southeastern vertex
			Point* getVertex_bse();

			//- Get the back southwestern vertex
			Point* getVertex_bsw();

			//- Get the boundary types
			boost::numeric::ublas::vector<int> getBoundaryTypes();

			//- Get the boundary type of the ith face
			int getBoundaryTypes( int i );
};

// ************************************************************************* //