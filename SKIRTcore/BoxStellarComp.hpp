/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef BOXSTELLARCOMP_HPP
#define BOXSTELLARCOMP_HPP

#include "Box.hpp"
#include "StellarComp.hpp"

//////////////////////////////////////////////////////////////////////

/** The BoxStellarComp class is an abstract subclass of the StellarComp class, and represents any
    stellar component defined within a cuboidal volume with faces that are aligned with the planes
    of the coordinate system (a box). The class also inherits from the Box class. */
class BoxStellarComp : public StellarComp, public Box
{
    Q_OBJECT
    Q_CLASSINFO("Title", "a stellar component bounded by a box")

    Q_CLASSINFO("Property", "minX")
    Q_CLASSINFO("Title", "the start point of the box in the X direction")
    Q_CLASSINFO("Quantity", "length")

    Q_CLASSINFO("Property", "maxX")
    Q_CLASSINFO("Title", "the end point of the box in the X direction")
    Q_CLASSINFO("Quantity", "length")

    Q_CLASSINFO("Property", "minY")
    Q_CLASSINFO("Title", "the start point of the box in the Y direction")
    Q_CLASSINFO("Quantity", "length")

    Q_CLASSINFO("Property", "maxY")
    Q_CLASSINFO("Title", "the end point of the box in the Y direction")
    Q_CLASSINFO("Quantity", "length")

    Q_CLASSINFO("Property", "minZ")
    Q_CLASSINFO("Title", "the start point of the box in the Z direction")
    Q_CLASSINFO("Quantity", "length")

    Q_CLASSINFO("Property", "maxZ")
    Q_CLASSINFO("Title", "the end point of the box in the Z direction")
    Q_CLASSINFO("Quantity", "length")

    //============= Construction - Setup - Destruction =============

protected:
    /** The default constructor; it is protected since this is an abstract class. */
    BoxStellarComp();

    /** This function verifies that the box has a positive volume. */
    void setupSelfBefore();

    //======== Setters & Getters for Discoverable Attributes =======

public:
    /** Sets the start point \f$x_{\text{min}}\f$ of the box in the X direction. */
    Q_INVOKABLE void setMinX(double value);

    /** Returns the start point \f$x_{\text{min}}\f$ of the box in the X direction. */
    Q_INVOKABLE double minX() const;

    /** Sets the end point \f$x_{\text{max}}\f$ of the box in the X direction. */
    Q_INVOKABLE void setMaxX(double value);

    /** Returns the end point \f$x_{\text{max}}\f$ of the box in the X direction. */
    Q_INVOKABLE double maxX() const;

    /** Sets the start point \f$y_{\text{min}}\f$ of the box in the Y direction. */
    Q_INVOKABLE void setMinY(double value);

    /** Returns the start point \f$y_{\text{min}}\f$ of the box in the Y direction. */
    Q_INVOKABLE double minY() const;

    /** Sets the end point \f$y_{\text{max}}\f$ of the box in the Y direction. */
    Q_INVOKABLE void setMaxY(double value);

    /** Returns the end point \f$y_{\text{max}}\f$ of the box in the Y direction. */
    Q_INVOKABLE double maxY() const;

    /** Sets the start point \f$z_{\text{min}}\f$ of the box in the Z direction. */
    Q_INVOKABLE void setMinZ(double value);

    /** Returns the start point \f$z_{\text{min}}\f$ of the box in the Z direction. */
    Q_INVOKABLE double minZ() const;

    /** Sets the end point \f$z_{\text{max}}\f$ of the box in the Z direction. */
    Q_INVOKABLE void setMaxZ(double value);

    /** Returns the end point \f$z_{\text{max}}\f$ of the box in the Z direction. */
    Q_INVOKABLE double maxZ() const;

    //======================== Other Functions =======================

public:
    /** This function returns the dimension of the stellar component, which for this class is always 3
        since there are no symmetries in the geometry. */
    int dimension() const;
};

//////////////////////////////////////////////////////////////////////

#endif // BOXSTELLARCOMP_HPP
