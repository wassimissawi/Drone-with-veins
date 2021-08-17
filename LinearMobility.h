#pragma once

#include "veins/base/modules/BaseMobility.h"

namespace Veins {

enum class NodeStatus {
    IDLE, RESERVED, PROVISIONING, MISSION, MAINTENANCE,DEAD
};
class VEINS_API LinearMobility : public BaseMobility {
private:
    NodeStatus status = NodeStatus::IDLE;

protected:
    double angle;
    double acceleration;

    double z;
    double playgroundLat;
     double playgroundLon;
     double playgroundHeight;
     double playgroundWidth;
     static LinearMobility *instance;
     LinearMobility* node;

     double yaw = 0;

     double pitch = 0;

     double climbAngle = 0;

    Coord stepTarget;

public:

    void initialize(int) override;

protected:

    void makeMove() override;

    void fixIfHostGetsOutside() override;

    void setStatus(NodeStatus status);
    NodeStatus getStatus() const
       {
           return status;
       }

    const char* getStatusString(NodeStatus status) const
       {
           switch (status) {
               case NodeStatus::DEAD:
                   return "DEAD";
               case NodeStatus::IDLE:
                   return "IDLE";
               case NodeStatus::MAINTENANCE:
                   return "MAINTENANCE";
               case NodeStatus::MISSION:
                   return "MISSION";
               case NodeStatus::PROVISIONING:
                   return "PROVISIONING";
               case NodeStatus::RESERVED:
                   return "RESERVED";

               default:
                   return "UNKNOWN!!!";
           }
       }

    const char* getStatusString() const
      {
          return getStatusString(status);
      }
    bool isStatus(NodeStatus status) const
       {
           return this->status == status;
       }
       bool isStatusIdle() const
       {
           return isStatus(NodeStatus::IDLE);
       }

       bool isStatusReserved() const
       {
           return isStatus(NodeStatus::RESERVED);
       }
       bool isStatusMission() const
       {
           return isStatus(NodeStatus::MISSION);
       }
       bool isStatusProvisioning() const
       {
           return isStatus(NodeStatus::PROVISIONING);
       }

    void setZ(double);
       double getZ() const
       {
           return z;
       }
    void setAltitude(double);
    void TakeOff();
    void setNodeParameters();
    virtual double toLatitude(double y)
        {
            return playgroundLat - y / 111111;
        }

        virtual double toLongitude(double x)
        {
            return playgroundLon + x / 111111 / cos(fabs(playgroundLat / 180 * M_PI));
        }


        double getAltitude()
        {
            return getZ();
        }

        double getYaw()
        {
            return yaw;
        }
        double getPitch()
        {
            return pitch;
        }
        double getClimbAngle() const
        {
            return climbAngle;
        }


};

} // namespace Veins
