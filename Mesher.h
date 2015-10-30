/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
   
Author
	Gilles Remond

Class
	Mesher

Description
	Defines a C-mesh around a NACA 4-series airfoil

SourceFiles
	Mesher.cpp

\*---------------------------------------------------------------------------*/

#pragma once

#include "Mesh.h"
#include <vector>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


/*---------------------------------------------------------------------------*\
                           Mesher Point Declaration
\*---------------------------------------------------------------------------*/

class Mesher
{
private :

	// Private data

		//- Vector containing the parameters of the NACA profile
		std::vector<double> m_nacaParameters;

		//- Vector containing the dimensions of the domain
		std::vector<double> m_domainLengths;
	
		//- Vector containing the number of cells in each direction
		std::vector<int> m_nbCells;
		
		//- Pointer to the created mesh
		Mesh* m_mesh;

public :

	// Constructors

		//- Construct null
		Mesher();

	// Member Functions

		//- Read the parameters for the mesh definition
		void readDict();

		//- Generate the points of the mesh
		void generatePoints();

		//- Return the mesh
		Mesh* getMesh();
};

// ************************************************************************* //