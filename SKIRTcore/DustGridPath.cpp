/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
//////////////////////////////////////////////////////////////////*/

#include "DustGridPath.hpp"
#include "Box.hpp"
#include <limits>

using namespace std;

//////////////////////////////////////////////////////////////////////

namespace
{
    const int INITIAL_CAPACITY = 1000;
}

//////////////////////////////////////////////////////////////////////

DustGridPath::DustGridPath(const Position& bfr, const Direction& bfk)
    : _bfr(bfr), _bfk(bfk), _s(0)
{
    _mv.reserve(INITIAL_CAPACITY);
    _sv.reserve(INITIAL_CAPACITY);
    _dsv.reserve(INITIAL_CAPACITY);
}

//////////////////////////////////////////////////////////////////////

DustGridPath::DustGridPath()
    : _s(0)
{
    _mv.reserve(INITIAL_CAPACITY);
    _sv.reserve(INITIAL_CAPACITY);
    _dsv.reserve(INITIAL_CAPACITY);
}

//////////////////////////////////////////////////////////////////////

void DustGridPath::clear()
{
    _s = 0;
    _mv.clear();
    _sv.clear();
    _dsv.clear();
}

//////////////////////////////////////////////////////////////////////

void DustGridPath::addSegment(int m, double ds)
{
    if (ds>0)
    {
        _s += ds;
        _mv.push_back(m);
        _sv.push_back(_s);
        _dsv.push_back(ds);
    }
}

//////////////////////////////////////////////////////////////////////

Position DustGridPath::moveInside(const Box& box, double eps)
{
    // a position that is certainly not inside any box
    static const Position OUTSIDE(numeric_limits<double>::infinity(),
                                  numeric_limits<double>::infinity(),
                                  numeric_limits<double>::infinity());

    // initial position and direction
    double kx,ky,kz;
    _bfk.cartesian(kx,ky,kz);
    double rx,ry,rz;
    _bfr.cartesian(rx,ry,rz);

    // --> x direction
    if (rx <= box.xmin())
    {
        if (kx <= 0.0) return OUTSIDE;
        else
        {
            double ds = (box.xmin()-rx)/kx;
            addSegment(-1,ds);
            rx = box.xmin() + eps;
            ry += ky*ds;
            rz += kz*ds;
        }
    }
    else if (rx >= box.xmax())
    {
        if (kx >= 0.0) return OUTSIDE;
        else
        {
            double ds = (box.xmax()-rx)/kx;
            addSegment(-1,ds);
            rx = box.xmax() - eps;
            ry += ky*ds;
            rz += kz*ds;
        }
    }

    // --> y direction
    if (ry <= box.ymin())
    {
        if (ky <= 0.0) return OUTSIDE;
        else
        {
            double ds = (box.ymin()-ry)/ky;
            addSegment(-1,ds);
            rx += kx*ds;
            ry = box.ymin() + eps;
            rz += kz*ds;
        }
    }
    else if (ry >= box.ymax())
    {
        if (ky >= 0.0) return OUTSIDE;
        else
        {
            double ds = (box.ymax()-ry)/ky;
            addSegment(-1,ds);
            rx += kx*ds;
            ry = box.ymax() - eps;
            rz += kz*ds;
        }
    }

    // --> z direction
    if (rz <= box.zmin())
    {
        if (kz <= 0.0) return OUTSIDE;
        else
        {
            double ds = (box.zmin()-rz)/kz;
            addSegment(-1,ds);
            rx += kx*ds;
            ry += ky*ds;
            rz = box.zmin() + eps;
        }
    }
    else if (rz >= box.zmax())
    {
        if (kz >= 0.0) return OUTSIDE;
        else
        {
            double ds = (box.zmax()-rz)/kz;
            addSegment(-1,ds);
            rx += kx*ds;
            ry += ky*ds;
            rz = box.zmax() - eps;
        }
    }

    // the position should now be just inside the box; although in rare cases, it may be still be outside!
    return Position(rx,ry,rz);
}

//////////////////////////////////////////////////////////////////////
