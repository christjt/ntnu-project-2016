#include "SelfAssembly/GroupRobot.h"

double sign(double num);

GroupRobot::GroupRobot( World*__world ):Robot(__world)
{
    wm = (GroupRobotWorldModel*)_wm;
}

void GroupRobot::applyDynamics(){
    Robot::applyDynamics();
    wm->updateTranslationVector();
    ConnectionMechanisms& connectionMechanism = wm->getConnectionMechanism();
    if(connectionMechanism.numConnections() > 0){
        connectionMechanism.setRotationalVelocity(0);
        return;
    }
    double desired = fabs(connectionMechanism.getDesiredRotationalVelocity());
    if(desired > 0){
        if(desired < connectionMechanism.getMaxRotationalVelocity()){
            connectionMechanism.setRotationalVelocity(connectionMechanism.getDesiredRotationalVelocity());
        }else{
            connectionMechanism.setRotationalVelocity(sign(connectionMechanism.getDesiredRotationalVelocity())*connectionMechanism.getMaxRotationalVelocity());
        }
    }


}

double sign(double num){
    return num > 0 ? 1.0 : -1.0;
}

void GroupRobot::applyRobotPhysics()
{
    Robot::applyRobotPhysics();
    ConnectionMechanisms& connectionMechanism = wm->getConnectionMechanism();
    double orientation = connectionMechanism.getOrientation() + connectionMechanism.getRotationalVelocity();
    if(orientation > 360.0){
        orientation -= 360.0;
    }else{
        if(orientation < -360){
            orientation += 360;
        }
    }
    connectionMechanism.setOrientation(orientation);
}

void GroupRobot::show(){

    std::vector<std::shared_ptr<ConnectionPort>> ports = wm->getConnectionMechanism().getPorts();
    for(auto& port: ports){
        drawConnectionPoint(*(port.get()));
    }

    Robot::show();
}

void GroupRobot::drawConnectionPoint(const ConnectionPort& port){

    double offsetOrientation = port.getPosition().getOrientation();
    double x1 = (_wm->_xReal + cos((offsetOrientation) * M_PI / 180)*15);
    double y1 = (_wm->_yReal + sin((offsetOrientation) * M_PI / 180)*15);
    double x2 = (_wm->_xReal + cos((offsetOrientation) * M_PI / 180)*25);
    double y2 = (_wm->_yReal + sin((offsetOrientation) * M_PI / 180)*25);

    if(port.isEngaged()){
        traceRayRGBA(gScreen, x1, y1, x2, y2, 0 , 255 , 0 , 255);
        traceRayRGBA(gScreen, x1 + 1, y1 + 1, x2 + 1, y2 + 1, 0 , 255 , 0 , 255);
        traceRayRGBA(gScreen, x1 - 1, y1 - 1, x2 - 1, y2 - 1, 0 , 255 , 0 , 255);
    }else{
        traceRayRGBA(gScreen, x1, y1, x2, y2, 255 , 0 , 0 , 255);
        traceRayRGBA(gScreen, x1 + 1, y1 + 1, x2 + 1, y2 + 1, 255 , 0 , 0 , 255);
        traceRayRGBA(gScreen, x1 - 1, y1 - 1, x2 - 1, y2 - 1, 255 , 0 , 0 , 255);
    }


}