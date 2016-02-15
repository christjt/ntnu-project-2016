//
// Created by christopher on 03.02.16.
//

#ifndef ROBOROBO2_SELFASSEMBLYMECHANISMSPREDATORCONTROLLER_H
#define ROBOROBO2_SELFASSEMBLYMECHANISMSPREDATORCONTROLLER_H

#include "Controllers/Controller.h"
class Robot;
class SelfAssemblyMechanismsPredatorController : public Controller {

    public:
        SelfAssemblyMechanismsPredatorController( RobotWorldModel *__wm );

        void reset();
        void step();


    private:
        void exploreMovement();

        std::vector<std::pair<Robot*, double >> findPrey();
        void eat(Robot* prey);

        const double _orientationChange = 0.01;
        int _orientationDirection;
        const double _orientationThreshold = 0.01;
        const double _boundaryPoint = 0.5;


};


#endif //ROBOROBO2_SELFASSEMBLYMECHANISMSPREDATORCONTROLLER_H
