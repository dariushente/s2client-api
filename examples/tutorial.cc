#include <sc2api/sc2_api.h>

#include <iostream>

using namespace sc2;

class Bot : public Agent {
public:
    virtual void OnGameStart() final {
        std::cout << "Hello, World!" << std::endl;
        std::cout << "I have " << Observation() -> GetMinerals() << " minerals!" << std::endl;
        
        int v = Observation() -> GetVespene();
        std::cout << "I have " << v << " vespene!" << std::endl;
    }
    
    // Print tag when SCV is created
    //virtual void OnUnitCreated (const Unit *unit) final {
    	//std::cout << unit->tag << std::endl;
    //}
    
    // Create SCV
    virtual void OnUnitIdle (const Unit *unit) final {
    	switch(unit -> unit_type.ToType()){
    		case UNIT_TYPEID::TERRAN_COMMANDCENTER: {
    			std::cout << "Building SCV!" << std::endl;
    			Actions() -> UnitCommand(unit, ABILITY_ID::TRAIN_SCV);
    			break;
    		}
    		default: {
    			break;
    		}
    	}
    }
};

int main(int argc, char* argv[]) {
    Coordinator coordinator;
    coordinator.LoadSettings(argc, argv);

    Bot bot;
    coordinator.SetParticipants({
        CreateParticipant(Race::Terran, &bot),
        CreateComputer(Race::Zerg)
    });

    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapBelShirVestigeLE);

    while (coordinator.Update()) {
    }

    return 0;
}