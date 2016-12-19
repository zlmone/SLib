#ifndef CHECKHEADER_SLIB_MAP_GEORECTANGLE
#define CHECKHEADER_SLIB_MAP_GEORECTANGLE

#include "definition.h"

#include "latlon.h"

SLIB_MAP_NAMESPACE_BEGIN

class SLIB_EXPORT GeoRectangle
{
public:
	LatLon bottomLeft;
	LatLon topRight;

public:
	GeoRectangle();

	GeoRectangle(const GeoRectangle& other);

	GeoRectangle(const LatLon& pt1, const LatLon& pt2);
	
public:
	GeoRectangle& operator=(const GeoRectangle& other);

public:
	sl_bool contains(const LatLon& pt) const;

	sl_bool isValid() const;
	
};

SLIB_MAP_NAMESPACE_END

#endif