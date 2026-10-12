#include "forgearm/hardware/arm_group.hpp"
#include "forgearm/hardware/mock_driver.hpp"
#include <iostream>
#include <memory>
#include <vector>
int main(){using namespace forgearm;using namespace forgearm::hardware;
 SafetyGate gate({{{-1.0,1.0},{-1.0,1.0}},0.2,1.0,true});
 auto driver=std::make_shared<MockDriver>();ArmGroup group(8);
 if(!group.add_arm("arm_01",driver,&gate).ok)return 1;
 if(!group.connect_all({{"arm_01",{"j1","j2"},0.2}}).ok)return 2;
 if(!group.enable_all().ok)return 3;
 if(!group.command("arm_01",{0.1,-0.1}).ok)return 4;
 if(group.command("arm_01",{0.8,0.0}).ok)return 5;
 if(group.command("arm_01",{0.0,0.0}).ok)return 6;
 if(group.command("unknown",{0.0,0.0}).ok)return 7;
 if(!group.stop_all().ok)return 8;
 if(!group.disconnect_all().ok)return 9;
 std::cout<<"Hardware abstraction tests passed (mock only).\n";return 0;
}
