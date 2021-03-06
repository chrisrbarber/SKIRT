/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include <QFileInfo>
#include "Image.hpp"
#include "FatalError.hpp"
#include "FilePaths.hpp"
#include "FITSInOut.hpp"
#include "Log.hpp"
#include "PeerToPeerCommunicator.hpp"
#include "SimulationItem.hpp"
#include "Units.hpp"

////////////////////////////////////////////////////////////////////

Image::Image()
    : _units(0), _xsize(0), _ysize(0), _nframes(0),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
}

////////////////////////////////////////////////////////////////////

Image::Image(int xsize, int ysize, int nframes)
    : _units(0), _xsize(xsize), _ysize(ysize), _nframes(nframes),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
}

////////////////////////////////////////////////////////////////////

Image::Image(const SimulationItem* item, QString filename)
    : _units(0), _xsize(0), _ysize(0), _nframes(0),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
    import(item, filename);
}

////////////////////////////////////////////////////////////////////

Image::Image(const SimulationItem* item, QString filename, QString directory)
    : _units(0), _xsize(0), _ysize(0), _nframes(0),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
    import(item, filename, directory);
}

////////////////////////////////////////////////////////////////////

Image::Image(const SimulationItem* item, QString filename, double xres, double yres, QString quantity, QString xyqty)
    : _units(0), _xsize(0), _ysize(0), _nframes(0),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
    import(item, filename);

    // Store a pointer to the units system
    _units = item->find<Units>();

    // Set physical image properties
    _incx = _units->out(xyqty, xres);
    _incy = _units->out(xyqty, yres);
    _dataunits = _units->unit(quantity);
    _xyunits = _units->unit(xyqty);
}

////////////////////////////////////////////////////////////////////

Image::Image(const SimulationItem* item, QString filename, QString directory, double xres, double yres,
             QString quantity, QString xyqty)
    : _units(0), _xsize(0), _ysize(0), _nframes(0),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
    import(item, filename, directory);

    // Store a pointer to the units system
    _units = item->find<Units>();

    // Set physical image properties
    _incx = _units->out(xyqty, xres);
    _incy = _units->out(xyqty, yres);
    _dataunits = _units->unit(quantity);
    _xyunits = _units->unit(xyqty);
}

////////////////////////////////////////////////////////////////////

Image::Image(const Image& header, const Array& data)
    : _data(data), _units(0), _xsize(header.xsize()), _ysize(header.ysize()), _nframes(header.numframes()),
      _incx(header.xres()), _incy(header.yres()), _xc(header.xc()), _yc(header.yc())
{
}

////////////////////////////////////////////////////////////////////

Image::Image(const SimulationItem* item, const Array& data, int xsize, int ysize, int nframes,
             double xres, double yres, QString quantity, QString xyqty)
    : _data(data), _units(0), _xsize(xsize), _ysize(ysize), _nframes(nframes),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
    // Store a pointer to the units system
    _units = item->find<Units>();

    // Set physical image properties
    _incx = _units->out(xyqty, xres);
    _incy = _units->out(xyqty, yres);
    _dataunits = _units->unit(quantity);
    _xyunits = _units->unit(xyqty);
}

////////////////////////////////////////////////////////////////////

Image::Image(const SimulationItem* item, int xsize, int ysize, int nframes,
             double xres, double yres, QString quantity, QString xyqty)
    : _units(0), _xsize(xsize), _ysize(ysize), _nframes(nframes),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
    // Store a pointer to the units system
    _units = item->find<Units>();

    // Set physical image properties
    _incx = _units->out(xyqty, xres);
    _incy = _units->out(xyqty, yres);
    _dataunits = _units->unit(quantity);
    _xyunits = _units->unit(xyqty);
}

////////////////////////////////////////////////////////////////////

Image::Image(const SimulationItem* item, int xsize, int ysize, int nframes,
             double xres, double yres, double xc, double yc, QString quantity, QString xyqty)
    : _units(0), _xsize(xsize), _ysize(ysize), _nframes(nframes),
      _incx(0), _incy(0), _xc(0), _yc(0)
{
    // Store a pointer to the units system
    _units = item->find<Units>();

    // Set physical image properties
    _incx = _units->out(xyqty, xres);
    _incy = _units->out(xyqty, yres);
    _xc = _units->out(xyqty, xc);
    _yc = _units->out(xyqty, yc);
    _dataunits = _units->unit(quantity);
    _xyunits = _units->unit(xyqty);
}

////////////////////////////////////////////////////////////////////

void Image::import(const SimulationItem *item, QString filename, QString directory)
{
    // Cache a pointer to the logger
    Log* log = item->find<Log>();

    // Store a pointer to the units system
    _units = item->find<Units>();

    // Determine the path of the input FITS file
    QString filepath;
    filename = filename.endsWith(".fits") ? filename : filename + ".fits";
    if (directory.isNull())
    {
        filepath = item->find<FilePaths>()->input(filename);
    }
    else
    {
        QFileInfo test(directory);
        if (!test.isDir()) throw FATALERROR("Import directory does not exist: " + directory);
        filepath = directory + "/" + filename;
    }

    // Read the input image and store it
    log->info("Reading FITS file " + filepath);
    FITSInOut::read(filepath, _data, _xsize, _ysize, _nframes);

    // Verify that the FITS file contains only one frame
    if (_nframes != 1) throw FATALERROR("FITS image contains multiple frames");

    // Log the dimensions of the image
    log->info("Frame dimensions: " + QString::number(_xsize) + " x " + QString::number(_ysize));
}

////////////////////////////////////////////////////////////////////

void Image::resize(int xsize, int ysize, int nframes)
{
    // Set the size in the x and y direction
    _xsize = xsize;
    _ysize = ysize;

    // Set the number of frames
    _nframes = nframes;

    // Resize the internal data container
    _data.resize(xsize*ysize*nframes);
}

////////////////////////////////////////////////////////////////////

void Image::steal(Array& data)
{
    swap(_data, data);
}

////////////////////////////////////////////////////////////////////

int Image::xsize() const
{
    return _xsize;
}

////////////////////////////////////////////////////////////////////

int Image::ysize() const
{
    return _ysize;
}

////////////////////////////////////////////////////////////////////

int Image::numframes() const
{
    return _nframes;
}

////////////////////////////////////////////////////////////////////

int Image::numpixels() const
{
    return xsize()*ysize();
}

////////////////////////////////////////////////////////////////////

double Image::xres() const
{
    return _incx;
}

////////////////////////////////////////////////////////////////////

double Image::yres() const
{
    return _incy;
}

////////////////////////////////////////////////////////////////////

double Image::xc() const
{
    return _xc;
}

////////////////////////////////////////////////////////////////////

double Image::yc() const
{
    return _yc;
}

////////////////////////////////////////////////////////////////////

double Image::sum() const
{
    return _data.sum();
}

////////////////////////////////////////////////////////////////////

const Array& Image::data() const
{
    return _data;
}

////////////////////////////////////////////////////////////////////

void Image::saveto(const SimulationItem* item, QString filename, QString description)
{
    saveto(item, _data, filename, description);
}

////////////////////////////////////////////////////////////////////

void Image::saveto(const SimulationItem* item, const Array& data, QString filename, QString description)
{
    // Cache a pointer to the logger
    Log* log = item->find<Log>();

    // Determine the path of the output FITS file
    QString filepath = item->find<FilePaths>()->output(filename.endsWith(".fits") ? filename : filename + ".fits");

    // Try to find a PeerToPeerCommunicator object
    PeerToPeerCommunicator* comm = 0;
    try {comm = item->find<PeerToPeerCommunicator>();}
    catch (FatalError) {}

    // Only write the FITS file if this process is the root or no PeerToPeerCommunicator was found
    if (!comm || comm->isRoot())
    {
        log->info("Writing " + description + " to " + filepath + "...");
        FITSInOut::write(filepath, data, _xsize, _ysize, _nframes, _incx, _incy, _xc, _yc, _dataunits, _xyunits);
    }
}

////////////////////////////////////////////////////////////////////
