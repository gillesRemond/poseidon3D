/*---------------------------------------------------------------------------*\
This file is part of Poseidon.
\*---------------------------------------------------------------------------*/

#include <boost/numeric/ublas/vector.hpp>
#include "Cell.h"

using namespace boost::numeric::ublas;

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * *//

Cell::Cell()
{
	m_vertex_fne = 0;
	m_vertex_fnw = 0;
	m_vertex_fse = 0;
	m_vertex_fsw = 0;
	m_vertex_bne = 0;
	m_vertex_bnw = 0;
	m_vertex_bse = 0;
	m_vertex_bsw = 0;
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Cell::setIndex( int index )
{
	m_index = index;
}

void Cell::setVertex_fne( Point* vertex )
{
	m_vertex_fne = vertex;
}

void Cell::setVertex_fnw( Point* vertex )
{
	m_vertex_fnw = vertex;
}

void Cell::setVertex_fse( Point* vertex )
{
	m_vertex_fse = vertex;
}

void Cell::setVertex_fsw( Point* vertex )
{
	m_vertex_fsw = vertex;
}

void Cell::setVertex_bne( Point* vertex )
{
	m_vertex_bne = vertex;
}

void Cell::setVertex_bnw( Point* vertex )
{
	m_vertex_bnw = vertex;
}

void Cell::setVertex_bse( Point* vertex )
{
	m_vertex_bse = vertex;
}

void Cell::setVertex_bsw( Point* vertex )
{
	m_vertex_bsw = vertex;
}

void Cell::setBoundaryTypes( boost::numeric::ublas::vector<int> boundaryTypes )
{
	m_boundaryTypes = boundaryTypes;
}

int Cell::getIndex()
{
	return m_index;
}

Point* Cell::getVertex_fne()
{
	return m_vertex_fne;
}

Point* Cell::getVertex_fnw()
{
	return m_vertex_fnw;
}

Point* Cell::getVertex_fse()
{
	return m_vertex_fse;
}

Point* Cell::getVertex_fsw()
{
	return m_vertex_fsw;
}

Point* Cell::getVertex_bne()
{
	return m_vertex_bne;
}

Point* Cell::getVertex_bnw()
{
	return m_vertex_bnw;
}

Point* Cell::getVertex_bse()
{
	return m_vertex_bse;
}

Point* Cell::getVertex_bsw()
{
	return m_vertex_bsw;
}

vector<int> Cell::getBoundaryTypes()
{
	return m_boundaryTypes;
}

int Cell::getBoundaryTypes( int i )
{
	return m_boundaryTypes[ i ];
}

// ************************************************************************* //