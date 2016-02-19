#ifndef ROBOROBO2_GROUPROBOT_H
#define ROBOROBO2_GROUPROBOT_H

#include "Agents/Robot.h"
#include "World/World.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
class GroupRobot: public Robot
{
    public:
        GroupRobot( World*__world );
        void show();
        void applyDynamics();
        void registerRobot();
        void move( int __recursiveIt = 0 );
        void reset();

    protected:
        void applyRobotPhysics();
    private:
        void drawConnectionPoint(const ConnectionPort& port);
        GroupRobotWorldModel* wm;
        Vector2<double> backup;
};
#endif //ROBOROBO2_GROUPROBOT_H
