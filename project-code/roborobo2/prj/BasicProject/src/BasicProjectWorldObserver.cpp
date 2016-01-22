/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "BasicProject/include/BasicProjectWorldObserver.h"

#include "World/World.h"


BasicProjectWorldObserver::BasicProjectWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

BasicProjectWorldObserver::~BasicProjectWorldObserver()
{
	// nothing to do.
}

void BasicProjectWorldObserver::reset()
{
	// nothing to do.
}

void BasicProjectWorldObserver::step()
{
	// nothing to do.
}
