/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
//////////////////////////////////////////////////////////////////*/

#include "CMamForsteriteGrainComposition.hpp"

//////////////////////////////////////////////////////////////////////

CMamForsteriteGrainComposition::CMamForsteriteGrainComposition()
{
}

//////////////////////////////////////////////////////////////////////

void CMamForsteriteGrainComposition::setupSelfBefore()
{
    GrainComposition::setupSelfBefore();

    setBulkDensity(3.33e3);
    loadLogHeatCapacityGrid("GrainComposition/DustEM/hcap/C_CM_amFo10Fe30FeS.DAT");
    loadOpticalGrid(true, "GrainComposition/Min/CM_amFo10Fe30FeS_Jones2013_SKIRT.dat", false, false, false, false);
}

//////////////////////////////////////////////////////////////////////

QString CMamForsteriteGrainComposition::name() const
{
    return "CMamForsterite";
}

//////////////////////////////////////////////////////////////////////
