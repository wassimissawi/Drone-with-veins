
#include "veins/modules/mobility/LinearMobility.h"

#include "veins/veins.h"


using namespace Veins;

Define_Module(Veins::LinearMobility);

LinearMobility *LinearMobility::instance = nullptr;

void LinearMobility::initialize(int stage)
{
    BaseMobility::initialize(stage);

    EV_TRACE << "initializing LinearMobility stage " << stage << endl;

    if (stage == 0) {
        move.setSpeed(par("speed").doubleValue());
        acceleration = par("acceleration");
        angle = par("angle");
        angle = fmod(angle, 360);
    }
    else if (stage == 1) {
        stepTarget = move.getStartPos();
    }
}

void LinearMobility::setZ(double value)
{
    this->z = value;
}
void LinearMobility::fixIfHostGetsOutside()
{
    Coord dummy = Coord::ZERO;
    handleIfOutside(WRAP, stepTarget, dummy, dummy, angle);
}

void LinearMobility::makeMove()
{
    EV_TRACE << "start makeMove " << move.info() << endl;

    move.setStart(stepTarget, simTime());

    stepTarget.x = (move.getStartPos().x + move.getSpeed() * cos(M_PI * angle / 180) * SIMTIME_DBL(updateInterval));
    stepTarget.y = (move.getStartPos().y + move.getSpeed() * sin(M_PI * angle / 180) * SIMTIME_DBL(updateInterval));

    move.setDirectionByTarget(stepTarget);

    EV_TRACE << "new stepTarget: " << stepTarget.info() << endl;

    move.setSpeed(move.getSpeed() + acceleration * SIMTIME_DBL(updateInterval));

    yaw = atan2(move.getStartPos().y, move.getStartPos().x) / M_PI * 180;
       if (yaw < 0) yaw += 360;
       climbAngle = atan2(move.getStartPos().z, sqrt(move.getStartPos().x * move.getStartPos().x + move.getStartPos().y * move.getStartPos().y)) / M_PI * 180;
       pitch = (-1) * climbAngle;


    fixIfHostGetsOutside();
}
 void LinearMobility:: setAltitude(double value){
     setZ(value);
 }

 void LinearMobility:: TakeOff(){
     pitch = 0;
       climbAngle = 90;

 }

 void LinearMobility::setNodeParameters(){
     node->pitch = pitch;
         node->climbAngle = climbAngle;

 }
 void LinearMobility::setStatus(NodeStatus status){


 if (this->status != status) {
        switch (this->status) {
            case NodeStatus::DEAD:

               EV_WARN << "No status change from DEAD possible!!!";


                break;
            case NodeStatus::IDLE:
                if (NodeStatus::RESERVED == status) {
                    EV_INFO << "Changing node shadow " << getNode()->getFullName() << " from status " << this->getStatusString() << " to "
                            << getStatusString(status) << endl;
                    this->status = status;
                }

                else {
                    EV_WARN << "No status change from " << this->getStatusString() << " to " << getStatusString(status) << " possible!!!" << endl;
                }
                break;
            case NodeStatus::RESERVED:
                if (NodeStatus::PROVISIONING == status) {
                    EV_INFO << "Changing node shadow " << getNode()->getFullName() << " from status " << this->getStatusString() << " to "
                            << getStatusString(status) << endl;
                    this->status = status;
                }

                else {
                    EV_ERROR << "No status change from " << this->getStatusString() << " to " << getStatusString(status) << " possible!!!" << endl;
                }
                break;
            case NodeStatus::PROVISIONING:
                if (NodeStatus::MISSION == status) {
                    EV_INFO << "Changing node shadow " << getNode()->getFullName() << " from status " << this->getStatusString() << " to "
                            << getStatusString(status) << endl;
                    this->status = status;
                }

                else {
                    EV_ERROR << "No status change from " << this->getStatusString() << " to " << getStatusString(status) << " possible!!!" << endl;
                }
                break;
            case NodeStatus::MISSION:
                if (NodeStatus::MAINTENANCE == status) {
                    EV_INFO << "Changing node shadow " << getNode()->getFullName() << " from status " << this->getStatusString() << " to "
                            << getStatusString(status) << endl;
                    this->status = status;
                }

                else {
                    EV_ERROR << "No status change from " << this->getStatusString() << " to " << getStatusString(status) << " possible!!!" << endl;
                }
                break;
            case NodeStatus::MAINTENANCE:

                if(NodeStatus::MAINTENANCE == status) {
                    EV_ERROR << "No status change from " << this->getStatusString() << " to " << getStatusString(status) << " possible!!!" << endl;
                }
                break;

            default:
                throw cRuntimeError("Unknown node status");
        }
    }
 }
