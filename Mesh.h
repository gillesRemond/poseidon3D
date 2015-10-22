/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
   
Author
	Gilles Remond

Class
	Mesh

Description
	

SourceFiles
	Mesh.cpp

\*---------------------------------------------------------------------------*/

#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <string>

#include "Point.h"
#include "Cell.h"
#include "constants.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


/*---------------------------------------------------------------------------*\
                           Class Mesh Declaration
\*---------------------------------------------------------------------------*/

class Mesh
{
private:

	// Private data
	
		//- The number of points in the mesh
		boost::numeric::ublas::vector< int > m_nbPoints;

		//- The number of cells in the mesh
		boost::numeric::ublas::vector< int > m_nbCells;

		//- The list of the points in the mesh
		boost::numeric::ublas::vector< Point* > m_points;

		//- The list of the cells in the mesh
		boost::numeric::ublas::vector< Cell* > m_cells;

public:

	// Constructors

		//- Construct null
		Mesh();

		//- Construct given parameters
		Mesh( Parameters const& parameters );

	// Destructor
	~Mesh();

	// Member Functions
	
		//- Get the number of cells in the i direction
		int getNbCells( int i );

		//- Get the cell of of the given index
		Cell* getCell( int index );

		//- Compute the point index given i, j and k coordinates
		int pointIndex( int i, int j, int k );

		//- Compute the cell index given i, j and k coordinates
		int cellIndex( int i, int j, int k );

		//- Generate the mesh given the parameters
		void generateMesh( Parameters const& parameters );

		//- Write all data of the mesh (OpenFOAM files)
		void write();
};