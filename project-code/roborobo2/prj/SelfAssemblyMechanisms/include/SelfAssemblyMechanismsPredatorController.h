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
        std::vector<std::pair<Robot*, double >> findPrey();
        void eat(Robot* prey);

};


#endif //ROBOROBO2_SELFASSEMBLYMECHANISMSPREDATORCONTROLLER_H
