//
// Created by christopher on 05.02.16.
//

#ifndef ROBOROBO2_PORTPOSITION_H
#define ROBOROBO2_PORTPOSITION_H

#include "Utilities/Vector2.h"
class GroupRobotWorldModel;
class PortPosition {
    private:
        double orientation;
        GroupRobotWorldModel* _wm;

    public:
        PortPosition(GroupRobotWorldModel* sourceRobotModel, double orientation);
        Vector2<double> getPosition() const;
        double getOrientation() const;


};


#endif //ROBOROBO2_PORTPOSITION_H
