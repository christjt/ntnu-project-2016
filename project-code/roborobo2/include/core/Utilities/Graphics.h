/*
 *  SDL_gfxRoborobo.h
 *  roborobo
 *
 *  Created by Nicolas on 16/01/09.
 *
 */

#ifndef SDL_GFXROBOROBO_H
#define SDL_GFXROBOROBO_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

extern int gScreenshotIndex;
extern int gRobotTrackerIndex; 
extern int gTrajectoryImageIndex;

bool initSDL(Uint32 flags = 0); // parameter is optional (default: SDL_HWSURFACE | SDL_DOUBLEBUF)

//Uint32 getPixel32( SDL_Surface *surface, int x, int y );
//void putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ); // color: BGRA

inline Uint32 getPixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[ ( y * surface->w ) + x ];
}

inline Uint32 getPixel32_secured( SDL_Surface *surface, int x, int y )
{
    //Get the requested pixel
	if ( x >= 0 && x < surface->w && y >= 0 && y < surface->h )
        return getPixel32(surface, x, y);
	else
		return -1;
}

inline void putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Set the pixel
	pixels[ ( y * (surface->w) ) + x ] = pixel;
}

inline void putPixel32_secured( SDL_Surface *surface, int x, int y, Uint32 pixel ) // check borders (8% slower)
{
    if ( x >= 0 && x < surface->w && y >= 0 && y < surface->h )
        putPixel32(surface, x, y, pixel);
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination , SDL_Rect* clip = NULL );
void register_robotMask( int __x, int __y, SDL_Surface* destination , int __id ); // use gRobotMaskData
void clean_robotMask( int __x, int __y, SDL_Surface* destination ); // use gRobotMaskData

void register_surface( int __x, int __y, SDL_Surface* source, SDL_Surface* destination , int __id ); // unused as of 2014-03-28
void clean_surface( int __x, int __y, SDL_Surface* source, SDL_Surface* destination ); // unused as of 2014-03-28

void toggle_fullscreen();

SDL_Surface *load_image( std::string filename );

void saveScreenshot( std::string __comment = "");
void saveRobotTrackerIndex( std::string __comment = "" );

void saveTrajectoryImage( std::string __comment = "" );

void saveImage ( SDL_Surface image, std::string __prefix, std::string __comment = "" );

#endif // SDL_GFXROBOROBO_H

