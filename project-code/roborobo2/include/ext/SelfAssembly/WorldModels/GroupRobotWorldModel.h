
#ifndef ROBOROBO2_GROUPROBOTWORLDMODEL_H
#define ROBOROBO2_GROUPROBOTWORLDMODEL_H

#include "WorldModels/RobotWorldModel.h"
#include <vector>
#include "Agents/Robot.h"
#include "Utilities/Vector2.h"
#include <memory>

#include "SelfAssembly/ConnectionMechanisms.h"
#include "SelfAssembly/RobotGroup.h"
#include "SelfAssembly/Communication/CommunicationModule.h"
class GroupRobotWorldModel: public RobotWorldModel
{

    private:
        std::shared_ptr<RobotGroup> group;
        Vector2<double> translation;
        Vector2<double> backUpPosition;
        ConnectionMechanisms connectionMechanism;
        CommunicationModule communicationModule;
        std::vector<std::shared_ptr<ConnectionPort>> makePorts();
        bool moveCompleted;
    public:
        GroupRobotWorldModel();
        void connectTo(GroupRobotWorldModel* other);
        void disconnectFrom(GroupRobotWorldModel* other);
        void addRobotToGroup(GroupRobotWorldModel* robot);
        void updateTranslationVector();
        void setGroup(std::shared_ptr<RobotGroup> group);
        Vector2<double> getTranslation();
        Vector2<double>& getBackupPosition();
        std::shared_ptr<RobotGroup> getGroup();
        ConnectionMechanisms& getConnectionMechanism();
        CommunicationModule& getCommunicationModule();
        void setId(int id);
        bool hasPendingMove();
        void setMoveCompleted(bool moveCompleted);

};

/*;*/
#endif //ROBOROBO2_GROUPROBOTWORLDMODEL_H