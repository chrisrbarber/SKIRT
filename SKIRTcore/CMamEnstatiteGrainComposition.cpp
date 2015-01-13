/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
//////////////////////////////////////////////////////////////////*/

#include "CMamEnstatiteGrainComposition.hpp"

//////////////////////////////////////////////////////////////////////

CMamEnstatiteGrainComposition::CMamEnstatiteGrainComposition()
{
}

//////////////////////////////////////////////////////////////////////

void CMamEnstatiteGrainComposition::setupSelfBefore()
{
    GrainComposition::setupSelfBefore();

    setBulkDensity(3.33e3);
    loadLogHeatCapacityGrid("GrainComposition/DustEM/hcap/C_CM_amEnst10Fe30FeS.DAT");
    loadOpticalGrid(true, "GrainComposition/Min/CM_amEnst10Fe30FeS_Jones2013_SKIRT.dat", false, false, false, false);
}

//////////////////////////////////////////////////////////////////////

QString CMamEnstatiteGrainComposition::name() const
{
    return "CMamEnstatite";
}

//////////////////////////////////////////////////////////////////////
