/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "Sandbox/include/SandboxWorldObserver.h"

#include "World/World.h"


SandboxWorldObserver::SandboxWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

SandboxWorldObserver::~SandboxWorldObserver()
{
	// nothing to do.
}

void SandboxWorldObserver::reset()
{
	// nothing to do.
}

void SandboxWorldObserver::step()
{
	// nothing to do.
}
