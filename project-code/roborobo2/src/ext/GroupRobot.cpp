#include "SelfAssembly/GroupRobot.h"
#include "SelfAssembly/ConnectionPort.h"
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
    }else{
        connectionMechanism.setRotationalVelocity(0);
    }
}


void GroupRobot::move( int __recursiveIt )
{

    Robot::move(__recursiveIt);
    for(auto& connection: wm->getConnectionMechanism().getConnections()){
        auto other = connection.first;
        if(other->hasPendingMove())
            continue;

        auto port = connection.second;
        if(port->isBroken()){
            auto backup = wm->getBackupPosition();
            auto otherBackup = other->getBackupPosition();
            auto otherRobot = other->getWorld()->getRobot(other->getId());
            otherRobot->unregisterRobot();

            _wm->_xReal = backup.x;
            _wm->_yReal = backup.y;
            setCoord((int)_wm->_xReal+0.5,(int)_wm->_yReal+0.5);
            other->_xReal = otherBackup.x;
            other->_yReal = otherBackup.y;
            other->getWorld()->getRobot(other->getId())->setCoord((int)other->_xReal+0.5,(int)other->_yReal+0.5);
            otherRobot->registerRobot();

        }
    }
    wm->setMoveCompleted(true);
}

double sign(double num){
    return num > 0 ? 1.0 : -1.0;
}

void GroupRobot::applyRobotPhysics()
{
    auto groupWM = (GroupRobotWorldModel*)_wm;
    Vector2<double> translation = {.x = 0, .y = 0};
    for(auto it = groupWM->getGroup()->begin(); it!= groupWM->getGroup()->end(); it++){
        auto robotWM = (*it).second;
        translation += robotWM->getTranslation();
    }
    _wm->_agentAbsoluteLinearSpeed = translation.length()/(groupWM->getGroup()->size());
    _wm->_agentAbsoluteOrientation = (180/M_PI)*atan2(translation.y, translation.x);//_wm->_agentAbsoluteOrientation + _wm->_actualRotationalVelocity;
    // * recalibrate orientation within ]-180°,+180°]
    while ( _wm->_agentAbsoluteOrientation <= -180.0 || _wm->_agentAbsoluteOrientation > 180.0 ) // assume that it is highly unlikely that this while should loop. (depends from maximal angular velocity)
    {
        if ( _wm->_agentAbsoluteOrientation <= -180.0 )
        {
            _wm->_agentAbsoluteOrientation = _wm->_agentAbsoluteOrientation + 360.0;
        }
        else
        {
            if ( _wm->_agentAbsoluteOrientation > 180.0 )
            {
                _wm->_agentAbsoluteOrientation = _wm->_agentAbsoluteOrientation - 360.0;
            }
        }
    }

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

    if(!wm->isAlive())
        return;

    for(auto& port: wm->getConnectionMechanism().getPorts()){
        drawConnectionPoint(*(port.get()));
    }
    Robot::show();
}
void GroupRobot::reset()
{
    Robot::reset();
    wm->reset();
}
void GroupRobot::registerRobot()
{
    if(!wm->isAlive())
        return;

    Robot::registerRobot();
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