/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
\*---------------------------------------------------------------------------*/

#include "Mesher.h"
#include <cmath>

using namespace std;

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * *//

Mesher::Mesher() 
{
	m_mesh = 0;
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Mesher::readDict()
{
	m_nacaParameters.resize(4);
	m_nacaParameters[0] = 2; // chord of the profile
	m_nacaParameters[1] = 0.12; // maximum width
	m_nacaParameters[2] = 0; // chordwise coordinate of the maximum camber
	m_nacaParameters[3] = 0; // maximum camber

	m_domainLengths.resize(3);
	m_domainLengths[0] = 10;
	m_domainLengths[1] = 10;
	m_domainLengths[2] = 10;
	
	m_nbCells.resize(4);
	m_nbCells[0] = 20;
	m_nbCells[1] = 10;
	m_nbCells[2] = 10;
	m_nbCells[3] = 10;
}

void Mesher::generatePoints()
{
	// Allocate the pointer to mesh if not done yet
	if( m_mesh == 0)
		m_mesh = new Mesh();

	// 

	for( int i (0); i < m_nbCells[0] + 1; ++i )
	{
		double x = i * m_nacaParameters[0] / m_nbCells[0];
		double xAdim = x / m_nacaParameters[0];
		double y = 0;
		double z = -m_nacaParameters[1] / 0.2 * m_nacaParameters[0] * 
			( 0.2969 * sqrt( xAdim ) - 0.126 * xAdim - 0.3516 * xAdim * xAdim
			+ 0.2843 * pow( xAdim, 3.0 ) - 0.1015 * pow( xAdim, 4.0 ) );

		m_mesh -> addPoint(x, y, z);
	}

	for( int i (1); i < m_nbCells[0]; ++i )
	{
		double x = i * m_nacaParameters[0] / m_nbCells[0];
		double xAdim = x / m_nacaParameters[0];
		double y = 0;
		double z = m_nacaParameters[1] / 0.2 * m_nacaParameters[0] * 
			( 0.2969 * sqrt( xAdim ) - 0.126 * xAdim - 0.3516 * xAdim * xAdim
			+ 0.2843 * pow( xAdim, 3.0 ) - 0.1015 * pow( xAdim, 4.0 ) );

		m_mesh -> addPoint(x, y, z);
	}

}

Mesh* Mesher::getMesh()
{
	return m_mesh;
}