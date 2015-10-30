/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
\*---------------------------------------------------------------------------*/

#include <fstream>
#include "Mesh.h"

using namespace std;

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * *//

Mesh::Mesh()
{
	m_totalNbPoints = 0;
	m_totalNbCells = 0;
	m_points.reserve(5000);
	m_cells.reserve(5000);
}

Mesh::Mesh( Parameters const& parameters )
{
	m_nbPoints.resize( 3 );
	m_nbPoints[ 0 ] = parameters.nbCells[ 0 ] + 1;
	m_nbPoints[ 1 ] = parameters.nbCells[ 1 ] + 1;
	m_nbPoints[ 2 ] = parameters.nbCells[ 2 ] + 1;

	m_nbCells.resize( 3 );
	m_nbCells[ 0 ] = parameters.nbCells[ 0 ];
	m_nbCells[ 1 ] = parameters.nbCells[ 1 ];
	m_nbCells[ 2 ] = parameters.nbCells[ 2 ];
}

// * * * * * * * * * * * * * * * * *Destructor* * * * * * * * * * * * * * * *//

Mesh::~Mesh(void)
{
	// Delete all the points of the mesh
	for ( int i ( 0 ); i < m_points.size(); ++i )
	{
		delete m_points[ i ];
	}

	// Delete all the cells of the mesh
	for ( int i ( 0 ); i < m_cells.size(); ++i )
	{
		delete m_cells[ i ];
	}
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

int Mesh::getNbCells( int i )
{
	return m_nbCells[ i ];
}

void Mesh::addPoint( double const& x, double const& y, double const& z )
{
	// Create a new point of coordinate (x,y,z)
	Point* point = new Point( x, y, z );

	// Attribute it the index (m_totalNbPoints)
	point -> setIndex( m_totalNbPoints );

	// Update the number of points in the mesh
	m_totalNbPoints++;

	// Add the point to the list
	m_points.push_back( point );
}


Cell* Mesh::getCell( int index )
{
	if ( index >= 0 && index < m_cells.size() )
		return m_cells[ index ];
	else
		return NULL;
}

int Mesh::pointIndex( int i, int j, int k )
{
	return ( i + j * m_nbPoints[ 0 ] + k * ( m_nbPoints[ 0 ] * m_nbPoints[ 1 ] ) );
}

int Mesh::cellIndex( int i, int j, int k )
{
	return ( i + j * m_nbCells[ 0 ] + k * ( m_nbCells[ 0 ] * m_nbCells[ 1 ] ) );
}

void Mesh::generateMesh( Parameters const& parameters )
{
	//////////////////////////////////////////////////////////
	// Create all the points
	
	// Compute the total number of points
	int nbPoints = m_nbPoints[ 0 ] * m_nbPoints[ 1 ] * m_nbPoints[ 2 ];

	// Resize the vectors for the points
	m_points.resize( nbPoints );

	// The mesh is uniform
	double cellLength_x = parameters.lengths[ 0 ] / m_nbCells[ 0 ];
	double cellLength_y = parameters.lengths[ 1 ] / m_nbCells[ 1 ];
	double cellLength_z = parameters.lengths[ 2 ] / m_nbCells[ 2 ];

	for ( int k (0); k < m_nbPoints[ 2 ]; ++k )
	{
		for ( int j (0); j < m_nbPoints[ 1 ]; ++j )
		{
			for ( int i (0); i < m_nbPoints[ 0 ]; ++i )
			{
				int index = pointIndex( i, j, k );
				m_points[ index ] = new Point( i * cellLength_x, j * cellLength_y, k * cellLength_z );
				m_points[ index ] -> setIndex( index );
			}
		}
	}
	
	////////////////////////////////////////////////////////////
	//// create all the cells

	//// Compute the total number of cells
	//int nbCells = m_nbCells[ 0 ] * m_nbCells[ 1 ] * m_nbCells[ 2 ];

	//// Resize the vectors for the cells
	//m_cells.resize( nbCells );

	//for ( int k (0); k < m_nbCells( 2 ); ++k )
	//{
	//	for ( int j (0); j < m_nbCells( 1 ); ++j )
	//	{
	//		for ( int i (0); i < m_nbCells( 0 ); ++i )
	//		{
	//			Cell* cell = new Cell( );

	//			// Construct the cell by affecting its vertexes
	//			cell -> setVertex_fsw( m_points[ pointIndex( i,   j,   k ) ] );
	//			cell -> setVertex_fse( m_points[ pointIndex( i+1, j,   k ) ] );
	//			cell -> setVertex_fne( m_points[ pointIndex( i+1, j,   k+1 ) ] );
	//			cell -> setVertex_fnw( m_points[ pointIndex( i,   j,   k+1 ) ] );
	//			cell -> setVertex_bsw( m_points[ pointIndex( i,   j+1, k ) ] );
	//			cell -> setVertex_bse( m_points[ pointIndex( i+1, j+1, k ) ] );
	//			cell -> setVertex_bne( m_points[ pointIndex( i+1, j+1, k+1 ) ] );
	//			cell -> setVertex_bnw( m_points[ pointIndex( i,   j+1, k+1 ) ] );
	//			
	//			// Set the boundary types
	//			vector<int> boundaryTypes ( 6 );

	//			// North
	//			if ( k == m_nbCells( 2 ) - 1 )
	//			{
	//				boundaryTypes[ NORTH ] = parameters.boundaryTypes[ NORTH ];
	//			}
	//			else
	//			{
	//				boundaryTypes[ NORTH ] = INNER;
	//			}

	//			// South
	//			if ( k == 0 )
	//			{
	//				boundaryTypes[ SOUTH ] = parameters.boundaryTypes[ SOUTH ];
	//			}
	//			else
	//			{
	//				boundaryTypes[ SOUTH ] = INNER;
	//			}

	//			// East
	//			if ( i == m_nbCells( 0 ) - 1 )
	//			{
	//				boundaryTypes[ EAST ] = parameters.boundaryTypes[ EAST ];
	//			}
	//			else
	//			{
	//				boundaryTypes[ EAST ] = INNER;
	//			}

	//			// West
	//			if ( i == 0 )
	//			{
	//				boundaryTypes[ WEST ] = parameters.boundaryTypes[ WEST ];
	//			}
	//			else
	//			{
	//				boundaryTypes[ WEST ] = INNER;
	//			}

	//			// Front
	//			if ( j == 0 )
	//			{
	//				boundaryTypes[ FRONT ] = parameters.boundaryTypes[ FRONT ];
	//			}
	//			else
	//			{
	//				boundaryTypes[ FRONT ] = INNER;
	//			}

	//			// Back
	//			if ( j == m_nbCells( 1 ) - 1 )
	//			{
	//				boundaryTypes[ BACK ] = parameters.boundaryTypes[ BACK ];
	//			}
	//			else
	//			{
	//				boundaryTypes[ BACK ] = INNER;
	//			}

	//			cell -> setBoundaryTypes( boundaryTypes );

	//			int index = cellIndex( i, j, k ) ;
	//			cell -> setIndex( index );
	//			m_cells[ index ] = cell; 

	//		} // end of loop in the x direction
	//	} // end of loop in the y direction
	//} // end of loop in the z direction
}

void Mesh::write()
{
	int nbPoints ( m_points.size() );

	/////////////////////////////////////////////////////////////////////
	// Create the point output file
	/////////////////////////////////////////////////////////////////////
	std::ofstream fout;
	fout.open ("points", std::ios::trunc);

	fout << nbPoints << "\n";
	fout << "(" << "\n";
	for( int i (0); i < m_points.size(); ++i )
	{
		//fout << "("  << m_points[ i ] -> getCoordinate( 0 ); // print the x-coordinate
		//fout << " "  << m_points[ i ] -> getCoordinate( 1 ); // print the y-coordinate
		//fout << " "  << m_points[ i ] -> getCoordinate( 2 ); // print the z-coordinate
		//fout << ")"  << "\n";
		fout << "a "  << m_points[ i ] -> getCoordinate( 0 ); // print the x-coordinate
		fout << " "  << m_points[ i ] -> getCoordinate( 1 ); // print the y-coordinate
		fout << " "  << m_points[ i ] -> getCoordinate( 2 ); // print the z-coordinate
		fout << "\n";
	}
	//fout << ")"  << "\n";

	fout.close();

	/////////////////////////////////////////////////////////////////////
	// Create the faces, owner and neighbour output files
	/////////////////////////////////////////////////////////////////////
	//std::ofstream facesFile;
	//std::ofstream ownerFile;
	//std::ofstream neighbourFile;
	//facesFile.open ("faces", std::ios::trunc);
	//ownerFile.open ("owner", std::ios::trunc);
	//neighbourFile.open ("neighbour", std::ios::trunc);

	//int nbFaces = 3*m_nbCells[0]*m_nbCells[1]*m_nbCells[2] 
	//	+ m_nbCells[0]*m_nbCells[1] + m_nbCells[0]*m_nbCells[2] + m_nbCells[1]*m_nbCells[2];

	//facesFile << nbFaces << "\n";
	//ownerFile << nbFaces << "\n";
	//neighbourFile << 3*m_nbCells[0]*m_nbCells[1]*m_nbCells[2] 
	//	- m_nbCells[0]*m_nbCells[1] - m_nbCells[0]*m_nbCells[2] - m_nbCells[1]*m_nbCells[2] << "\n";

	//facesFile << "(" << "\n";
	//ownerFile << "(" << "\n";
	//neighbourFile << "(" << "\n";

	//for ( int k (0); k < m_nbCells[ 2 ]; ++k )
	//{
	//	for ( int j (0); j < m_nbCells[ 1 ]; ++j )
	//	{
	//		for ( int i (0); i < m_nbCells[ 0 ]; ++i )
	//		{
	//			int cellIdx = cellIndex( i, j, k );

	//			if( i < m_nbCells[ 0 ] - 1 )
	//			{
	//				// Print the inner face normal to the x-axis
	//				facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_fse() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bse() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bne() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fne() -> getIndex();
	//				facesFile << ")"   << "\n";

	//				// Add the cell index to the owner and neighbour lists
	//				ownerFile << cellIdx << "\n";
	//				neighbourFile << cellIndex( i+1, j, k ) << "\n";
	//			}
	//			
	//			if( j < m_nbCells[ 1 ] - 1 )
	//			{
	//				// Print the inner face normal to the y-axis
	//				facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_bsw() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bnw() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bne() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bse() -> getIndex();
	//				facesFile << ")"   << "\n";

	//				// Add the cell index to the owner and neighbour lists
	//				ownerFile << cellIdx << "\n";
	//				neighbourFile << cellIndex( i, j+1, k ) << "\n";
	//			}

	//			if( k < m_nbCells[ 2 ] - 1 )
	//			{
	//				// Print the inner face normal to the z-axis
	//				facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_fnw() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fne() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bne() -> getIndex();
	//				facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bnw() -> getIndex();
	//				facesFile << ")"   << "\n";

	//				// Add the cell index to the owner and neighbour lists
	//				ownerFile << cellIdx << "\n";
	//				neighbourFile << cellIndex( i, j, k+1 ) << "\n";
	//			}
	//		}
	//	}
	//}

	//// The western boundary condition
	//for ( int k (0); k < m_nbCells[2]; ++k )
	//{
	//	for ( int j (0); j < m_nbCells[1]; ++j )
	//	{
	//		int cellIdx = cellIndex( 0, j, k );

	//		facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_fsw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fnw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bnw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bsw() -> getIndex();
	//		facesFile << ")"   << "\n";

	//		// Add the cell index to the owner and neighbour lists
	//		ownerFile << cellIdx << "\n";
	//	}
	//}

	//// The eastern boundary condition
	//for ( int k (0); k < m_nbCells[2]; ++k )
	//{
	//	for ( int j (0); j < m_nbCells[1]; ++j )
	//	{
	//		int cellIdx = cellIndex( m_nbCells[0] - 1, j, k );

	//		facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_fse() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bse() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bne() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fne() -> getIndex();
	//		facesFile << ")"   << "\n";

	//		// Add the cell index to the owner and neighbour lists
	//		ownerFile << cellIdx << "\n";
	//	}
	//}

	//// The front boundary condition
	//for ( int i (0); i < m_nbCells[0]; ++i )
	//{
	//	for ( int k (0); k < m_nbCells[2]; ++k )
	//	{
	//		int cellIdx = cellIndex( i, 0, k );

	//		facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_fsw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fse() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fne() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fnw() -> getIndex();
	//		facesFile << ")"   << "\n";

	//		// Add the cell index to the owner and neighbour lists
	//		ownerFile << cellIdx << "\n";
	//	}
	//}

	//// The back boundary condition
	//for ( int i (0); i < m_nbCells[0]; ++i )
	//{
	//	for ( int k (0); k < m_nbCells[2]; ++k )
	//	{
	//		int cellIdx = cellIndex( i, m_nbCells[1] - 1, k );

	//		facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_bsw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bnw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bne() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bse() -> getIndex();
	//		facesFile << ")"   << "\n";

	//		// Add the cell index to the owner and neighbour lists
	//		ownerFile << cellIdx << "\n";
	//	}
	//}

	//// The southern boundary condition
	//for ( int i (0); i < m_nbCells[0]; ++i )
	//{
	//	for ( int j (0); j < m_nbCells[1]; ++j )
	//	{
	//		int cellIdx = cellIndex( i, j, 0 );

	//		facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_fsw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bsw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bse() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fse() -> getIndex();
	//		facesFile << ")"   << "\n";

	//		// Add the cell index to the owner and neighbour lists
	//		ownerFile << cellIdx << "\n";
	//	}
	//}

	//// The northern boundary condition
	//for ( int i (0); i < m_nbCells[0]; ++i )
	//{
	//	for ( int j (0); j < m_nbCells[1]; ++j )
	//	{
	//		int cellIdx = cellIndex( i, j, m_nbCells[2] - 1 );

	//		facesFile << "4("  << m_cells[ cellIdx ] -> getVertex_fnw() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_fne() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bne() -> getIndex();
	//		facesFile << " "   << m_cells[ cellIdx ] -> getVertex_bnw() -> getIndex();
	//		facesFile << ")"   << "\n";

	//		// Add the cell index to the owner and neighbour lists
	//		ownerFile << cellIdx << "\n";
	//	}
	//}
	//
	//facesFile << ")"  << "\n";
	//ownerFile << ")"  << "\n";
	//neighbourFile << ")"  << "\n";

	//facesFile.close();
	//ownerFile.close();
	//neighbourFile.close();
}