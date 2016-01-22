/*
 *  PassiveObject.h
 *  roborobo
 *
 *  Created by Nicolas on 29/4/2011. Revised 4/1/2014.
 *
 */

#ifndef LANDMARKOBJECT_H
#define LANDMARKOBJECT_H

#include "RoboroboMain/common.h"
#include "Utilities/Geometry.h"

class LandmarkObject
{
	private :
    int _id;
    static int _nextId;
	
	protected :
    
    // coordinates
    Point2d _position;
    Sint16 _xCenterPixel;
    Sint16 _yCenterPixel;
    
    double _radius; // radius, in pixels.
    bool _visible; // display option (default: true)
    
    int _state; // a state value, not used. Could be used for any particular purpose.
    
	public :
    
    LandmarkObject();
    ~LandmarkObject();
    
    int getId()
    {
        return _id;
    }
    
    void setPosition(Point2d position)
    {
        _position = position;
        _xCenterPixel = position.x;
        _yCenterPixel = position.y;
    }
    
    Point2d getPosition()
    {
        return _position;
    }
    
    int getState() { return _state; }
    void setState( int state ) { _state = state; }
    
    virtual void step();
    
    virtual void display();
    virtual void hide();
	
};

#endif
