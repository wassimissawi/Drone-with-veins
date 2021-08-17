
package org.car2x.veins.modules.mobility;

import org.car2x.veins.base.modules.BaseMobility;


simple LinearMobility extends BaseMobility
{
    parameters:
        @class(Veins::LinearMobility);
        double speed @unit(mps);
        double angle @unit(deg); 
        double acceleration @unit(mpss); 
        double updateInterval @unit(s); 
        double yaw @unit(deg);
        double pitch @unit(deg);
        double climbAngle @unit(deg);
        
        
}

