//
// Created by christopher on 05.02.16.
//

#include "SelfAssembly/PortPosition.h"
#include "Utilities/Vector2.h"
#include <stdlib.h>

int _collisionPositionOffset = 5;
int _collisionOrientationOffset = 1;
const int PERFECT_ORIENTATIONAL_FIT = 180;

PortPosition::PortPosition(GroupRobotWorldModel *sourceRobotModel) {
    _wm = sourceRobotModel;
}

PortPosition* PortPosition::getPortPosition(int orientation){
    updatePosition(orientation);
    return this;
}

void PortPosition::updatePosition(int orientation){
    _posX = (_wm->_xReal + cos((orientation) * M_PI / 180)*20);
    _posY = (_wm->_yReal + sin((orientation) * M_PI / 180)*20);
}

bool PortPosition::isGeometricValidConnection(int sourceOrientation, PortPosition* target, int targetOrientation){
    updatePosition(sourceOrientation);
    target->updatePosition(targetOrientation);

    return isOrientationalSound(sourceOrientation, targetOrientation) && isSpatiallySound(target);
}

bool PortPosition::isOrientationalSound(int sourceOrientation, int targetOrientation){
    return abs(sourceOrientation - targetOrientation) < PERFECT_ORIENTATIONAL_FIT + _collisionOrientationOffset && abs(sourceOrientation - targetOrientation) > PERFECT_ORIENTATIONAL_FIT - _collisionOrientationOffset;
}

bool PortPosition::isSpatiallySound(PortPosition* target){
    return sqrt(_posX * target->getPosX() + _posY * target->getPosY()) < _collisionPositionOffset;
}


