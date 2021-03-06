/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include <cmath>
#include <limits>
#include "FatalError.hpp"
#include "Random.hpp"
#include "StellarSurfaceGeometry.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////

StellarSurfaceGeometry::StellarSurfaceGeometry()
{
}

//////////////////////////////////////////////////////////////////////

void
StellarSurfaceGeometry::setupSelfBefore()
{
    Geometry::setupSelfBefore();
    // verify property values
    if (_rstar <= 0) throw FATALERROR("the stellar radius rstar should be positive");
}

//////////////////////////////////////////////////////////////////////

int
StellarSurfaceGeometry::dimension()
const
{
    return 1;
}

////////////////////////////////////////////////////////////////////

void
StellarSurfaceGeometry::setRadius(double value)
{
    _rstar = value;
}

////////////////////////////////////////////////////////////////////

double
StellarSurfaceGeometry::radius()
const
{
    return _rstar;
}

//////////////////////////////////////////////////////////////////////

double
StellarSurfaceGeometry::density(Position bfr)
const
{
    return bfr.radius() == _rstar ? numeric_limits<double>::infinity() : 0.0;
}

//////////////////////////////////////////////////////////////////////

Position
StellarSurfaceGeometry::generatePosition()
const
{
    return Position(_rstar,_random->direction());
}

//////////////////////////////////////////////////////////////////////

double
StellarSurfaceGeometry::SigmaX()
const
{
    return 1.0/(2.0*M_PI*_rstar*_rstar);
}

//////////////////////////////////////////////////////////////////////

double
StellarSurfaceGeometry::SigmaY()
const
{
    return 1.0/(2.0*M_PI*_rstar*_rstar);
}

//////////////////////////////////////////////////////////////////////

double
StellarSurfaceGeometry::SigmaZ()
const
{
    return 1.0/(2.0*M_PI*_rstar*_rstar);
}

//////////////////////////////////////////////////////////////////////

double
StellarSurfaceGeometry::probabilityForDirection(int /*ell*/, Position bfr, Direction bfk)
const
{
    if (fabs(bfr.radius()/_rstar-1.0) > 1e-8)
        throw FATALERROR("the directional probability function is not defined for positions not on the stellar surface");
    double costhetap = Vec::dot(bfr,bfk)/_rstar;
    if (costhetap > 0.0)
        return 4.0*costhetap;
    else
        return 0.0;
}

//////////////////////////////////////////////////////////////////////

Direction
StellarSurfaceGeometry::generateDirection(int /*ell*/, Position bfr)
const
{
    if (fabs(bfr.radius()/_rstar-1.0) > 1e-8)
        throw FATALERROR("cannot generate directions for positions not on the stellar surface");

    // picking a random (theta',phi')
    double thetap = asin(sqrt(_random->uniform()));
    double phip = 2.0*M_PI*_random->uniform();
    Direction bfkp(thetap,phip);
    double kpx, kpy, kpz;
    bfkp.cartesian(kpx,kpy,kpz);

    // conversion to the regular coordinate system
    double r, theta, phi;
    bfr.spherical(r,theta,phi);
    double costheta = cos(theta);
    double sintheta = sin(theta);
    double cosphi = cos(phi);
    double sinphi = sin(phi);
    double kx = costheta*cosphi*kpx - sinphi*kpy + sintheta*cosphi*kpz;
    double ky = costheta*sinphi*kpx + cosphi*kpy + sintheta*sinphi*kpz;
    double kz = -sintheta*kpx + costheta*kpz;
    return Direction(kx,ky,kz);
}

//////////////////////////////////////////////////////////////////////
