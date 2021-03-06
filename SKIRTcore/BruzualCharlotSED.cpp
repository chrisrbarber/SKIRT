/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "BruzualCharlotSED.hpp"
#include "BruzualCharlotSEDFamily.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////

BruzualCharlotSED::BruzualCharlotSED()
    : _t(0)
{
}

////////////////////////////////////////////////////////////////////

void BruzualCharlotSED::setupSelfBefore()
{
    StellarSED::setupSelfBefore();

    // construct the library of SED models
    BruzualCharlotSEDFamily bc(this);

    // get the luminosities for arbitrary mass and for the appropriate Z and t
    setluminosities(bc.luminosities(1., _Z, _t*1e9));
}

////////////////////////////////////////////////////////////////////

void BruzualCharlotSED::setMetallicity(double value)
{
    _Z = value;
}

////////////////////////////////////////////////////////////////////

double BruzualCharlotSED::metallicity() const
{
    return _Z;
}

////////////////////////////////////////////////////////////////////

void BruzualCharlotSED::setAge(double value)
{
    _t = value;
}

////////////////////////////////////////////////////////////////////

double BruzualCharlotSED::age() const
{
    return _t;
}

////////////////////////////////////////////////////////////////////
