#include "SelfAssembly/GroupRobot.h"

GroupRobot::GroupRobot( World*__world ):Robot(__world)
{

}

void GroupRobot::show(){
    if(gNumberOfConnectionPoints > 0){
        int radCounter = 360/gNumberOfConnectionPoints;
        for (int i = 0; i < gNumberOfConnectionPoints; i++){
            drawConnectionPoint(radCounter*i);
        }
    }

    Robot::show();
}

void GroupRobot::drawConnectionPoint(int offsetOrientation){

    double x1 = (_wm->_xReal + cos((offsetOrientation) * M_PI / 180)*15);
    double y1 = (_wm->_yReal + sin((offsetOrientation) * M_PI / 180)*15);
    double x2 = (_wm->_xReal + cos((offsetOrientation) * M_PI / 180)*25);
    double y2 = (_wm->_yReal + sin((offsetOrientation) * M_PI / 180)*25);

    traceRayRGBA(gScreen, x1, y1, x2, y2, 255 , 0 , 0 , 255);
    traceRayRGBA(gScreen, x1 + 1, y1 + 1, x2 + 1, y2 + 1, 255 , 0 , 0 , 255);
    traceRayRGBA(gScreen, x1 - 1, y1 - 1, x2 - 1, y2 - 1, 255 , 0 , 0 , 255);

}