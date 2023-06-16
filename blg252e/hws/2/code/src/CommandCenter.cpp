//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------//
#include "CommandCenter.h"
#include "Robot.h"
#include <iostream>
using namespace std;
/*
****************
BEGIN: CREW CLASS FUNCTION DECLARATIONS 
****************
*/
void Crew::initMovement() {
    for (int i = 0; i < explorerCrewSize; i++) {
        ExplorerCrew[i]->canMove = true;
    }

    for (int i = 0; i < minerCrewSize; i++) {
        MinerCrew[i]->canMove = true;
    }
}

void Crew::updateDurability() {
    cout << "Explorer durability is being updated" << endl;
    for (int i = 0; i < explorerCrewSize; i++) {
        if (ExplorerCrew[i] == nullptr) {
            continue;
        }

        ExplorerCrew[i]->durability--;

        if (ExplorerCrew[i]->durability == 0) {
            cout << ExplorerCrew[i]->getName() << "'s durability=0" << endl;
            operator-=(ExplorerCrew[i]->RobotName);
        }
    }

    cout << "Miner durability is being updated" << endl;
    for (int i = 0; i < minerCrewSize; i++) {
        if (MinerCrew[i] == nullptr) {
            continue;
        }

        MinerCrew[i]->durability--;

        if (MinerCrew[i]->durability == 0) {
            cout << MinerCrew[i]->getName() << "'s durability=0" << endl;
            operator-=(MinerCrew[i]->RobotName);
        }
    }
}

Crew::Crew(int inMaxExplorers, int inMaxMiners, int inExplorerCrewSize, int inMinerCrewSize)
    : crewManufactureCost(0), crewMaintenanceCost(0), explorerCrewSize(0), minerCrewSize(0)
{
    int explorerCreationCount;
    int minerCreationCount;
    if(inMaxExplorers >= 1 && inMaxExplorers <= 5) {
        maxExplorers = inMaxExplorers;
    } else {
        maxExplorers = 2;
    }

    if(inMaxMiners >= 1 && inMaxMiners <= 5) {
        maxMiners = inMaxMiners;
    } else {
        maxMiners = 2;
    }

    if(inExplorerCrewSize < 0 || inExplorerCrewSize > inMaxExplorers) {
        explorerCreationCount = maxExplorers;
    } else {
        explorerCreationCount = inExplorerCrewSize;
    }

    if(inMinerCrewSize < 0 || inMinerCrewSize > inMaxMiners) {
        minerCreationCount = maxMiners;
    } else {
        minerCreationCount = inMinerCrewSize;
    }

    ExplorerCrew = new Explorer*[maxExplorers];
    for (int i = 0; i < explorerCreationCount; i++) {
        operator+=(manufactureRobot("explorer"));
    }

    MinerCrew = new Miner*[maxMiners];
    for (int i = 0; i < minerCreationCount; i++) {
        operator+=(manufactureRobot("miner"));
    }

    initMovement();
}

Robot* Crew::manufactureRobot(string inType) const {
    while (inType != "explorer" && inType != "miner") {
        cout << "Type:";
        string typeSelection;
        cin >> typeSelection;
        inType = typeSelection;
    }

    Robot* manufacturedRobotPtr;
    int robotDurability = 1 + (rand() % 5);
    if (inType == "explorer") {
        float explorerSpeed = 1.5f + ((float)rand() / RAND_MAX);

        manufacturedRobotPtr = new Explorer("explorer", explorerSpeed, robotDurability);
    } else if(inType == "miner") {
        float minerSpeed = 1.0f + (0.5f * ((float)rand() / RAND_MAX));

        manufacturedRobotPtr = new Miner("miner", minerSpeed, robotDurability);
    }

    return manufacturedRobotPtr;
}

void Crew::showInfo() const {
    cout << "explorerCrew Size:" << explorerCrewSize << endl;
    cout << "minerCrew Size:" << minerCrewSize << endl;
    
    for (int i = 0; i < explorerCrewSize; i++) {
        if (ExplorerCrew[i] == nullptr) {
            continue;
        }
        ExplorerCrew[i]->showInfo();
    }
    for (int i = 0; i < minerCrewSize; i++) {
        if (MinerCrew[i] == nullptr) {
            continue;
        }
        MinerCrew[i]->showInfo();
    }

    cout << "Total manufacture cost: " << crewManufactureCost << endl;
    cout << "Total maintenance cost: " << crewMaintenanceCost << endl;
}

Crew& Crew::operator+=(Robot* inOtherPtr) {
    bool isFull = false;
    if (inOtherPtr->RobotType == "explorer") {
        isFull = explorerCrewSize >= maxExplorers;
        if(!isFull) {
            Explorer* castedExplorerPtr = dynamic_cast<Explorer*>(inOtherPtr);
            ExplorerCrew[explorerCrewSize] = castedExplorerPtr;
            
            crewManufactureCost += 3000;
            explorerCrewSize++;
        }
    } else if (inOtherPtr->RobotType == "miner") {
        isFull = minerCrewSize >= maxMiners;
        if(!isFull) {
            Miner* castedMinerPtr = dynamic_cast<Miner*>(inOtherPtr);
            MinerCrew[minerCrewSize] = castedMinerPtr;
            
            crewManufactureCost += 5000;
            minerCrewSize++;
        }
    }

    if (isFull) {
        cout << "This robot cannot be added, check maximum size of the crew." << endl;
        delete inOtherPtr;
    }

    return *this;
}

Crew& Crew::operator-=(const string& inRobotName) {
    cout << inRobotName << ": Goodbye" << endl;
    
    if(inRobotName.find("exp") != string::npos) {
        if (explorerCrewSize <= 1) {
            return *this;
        }

        for (int i = 0; i < explorerCrewSize; i++) {
            if(ExplorerCrew[i]->RobotName == inRobotName) {
                delete ExplorerCrew[i];
                ExplorerCrew[i] = nullptr;

                for(int j = i; j < explorerCrewSize - 1; j++) {
                    ExplorerCrew[j] = ExplorerCrew[j + 1];
                }
                ExplorerCrew[explorerCrewSize - 1] = nullptr;
                
                explorerCrewSize--;
                
                break;
            }
        }
    } else if(inRobotName.find("mnr") != string::npos) {
        if (minerCrewSize <= 1) {
            return *this;
        }
        
        for (int i = 0; i < minerCrewSize; i++) {
            if(MinerCrew[i]->RobotName == inRobotName) {
                delete MinerCrew[i];
                MinerCrew[i] = nullptr;

                for(int j = i; j < minerCrewSize - 1; j++) {
                    MinerCrew[j] = MinerCrew[j + 1];
                }
                MinerCrew[minerCrewSize - 1] = nullptr;
                
                minerCrewSize--;

                break;
            }
        }
    }

    return *this;
}

Crew::~Crew() {
    for (int i = 0; i < maxExplorers; i++) {
        delete ExplorerCrew[i];
        ExplorerCrew[i] = nullptr;
    }
    delete[] ExplorerCrew;
    ExplorerCrew = nullptr;

    for (int i = 0; i < maxMiners; i++) {
        delete MinerCrew[i];
        MinerCrew[i] = nullptr;
    }
    delete[] MinerCrew;
    MinerCrew = nullptr;
}
/*
****************
END: CREW CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/
CommandCenter::CommandCenter(const int inSeleniumAim, const int inExploreArea, const int inSeleniumWorth) 
    : neededSelenium(inSeleniumAim), searchArea(inExploreArea), seleniumWorth(inSeleniumWorth), turnCount(1), profit(0)
{

}

bool CommandCenter::isGameEnded() const {
    bool gameEnded = Explorer::totalExploredArea >= searchArea;
    bool playerWon = profit > 0 && Miner::totalGatheredSelenium >= neededSelenium;
    if (gameEnded) {
        if (playerWon) {
            cout << "Congrats!" << endl;
        } else{
            cout << "Mission Failed!" << endl;
        }
    }

    return gameEnded;
}

void CommandCenter::calculateProfit(const Crew& crew) {
    float expenses = crew.getCrewMaintenanceCost() + crew.getCrewManufactureCost();
    int revenue = Miner::totalGatheredSelenium * seleniumWorth;
    profit = revenue - expenses;
    
    cout << "Profit:" << profit << endl;
    cout << "Expenses:" << expenses << endl;
    cout << "Selenium Revenue:" << revenue << endl;
}

void CommandCenter::showInfo() const {
    cout << "Current turn: " << turnCount << endl;
    cout << "Aim: " << neededSelenium << " selenium." << endl;
    cout << "Collected: " << Miner::totalGatheredSelenium << endl;
    cout << "Total Search Area: " << searchArea << endl;
    cout << "Explored Area: " << Explorer::totalExploredArea << endl;
    cout << "Currently, there are " << Explorer::totalNumberOfSeleniumArea << " area/s that include selenium." << endl;
    if (Explorer::totalNumberOfSeleniumArea > 0) {
        cout << "Mine these areas if miners have not finished their turn! If you cannot cope with mining, you can always add new miners!" << endl;
    }
}

void CommandCenter::operator++() {
    turnCount++;
}
/*
****************
END: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/