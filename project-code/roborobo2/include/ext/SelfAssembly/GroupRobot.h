#ifndef ROBOROBO2_GROUPROBOT_H
#define ROBOROBO2_GROUPROBOT_H

#include "Agents/Robot.h"
#include "World/World.h"
class GroupRobot: public Robot
{
    public:
        GroupRobot( World*__world );
        void show();

    private:
        void drawConnectionPoint(int offsetOrientation);
};
#endif //ROBOROBO2_GROUPROBOT_H
