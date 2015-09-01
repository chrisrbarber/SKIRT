/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "Geometry.hpp"
#include "Random.hpp"

//////////////////////////////////////////////////////////////////////

Geometry::Geometry()
{
}

//////////////////////////////////////////////////////////////////////

void Geometry::setupSelfBefore()
{
    SimulationItem::setupSelfBefore();

    _random = find<Random>();
}

//////////////////////////////////////////////////////////////////////

double Geometry::probabilityForDirection(int /*ell*/, Position /*bfr*/, Direction /*bfk*/) const
{
    return 1.;
}

//////////////////////////////////////////////////////////////////////

Direction Geometry::generateDirection(int /*ell*/, Position /*bfr*/) const
{
    return _random->direction();
}

//////////////////////////////////////////////////////////////////////
