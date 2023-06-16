//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------/

#include <iostream>
using namespace std;
#include "Robot.h"



/*
****************
BEGIN: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/
int Robot::unqID = 0;

Robot::Robot(const string& inType, const float inSpeed, const int inDurability, const int inManufactureCost, const float inMaintenanceCost)
    : RobotType(inType), speed(inSpeed), durability(inDurability), manufactureCost(inManufactureCost), maintenanceCost(inMaintenanceCost), canMove(false)
{
    unqID++;

    string robotNameCode;
    if (inType == "explorer") {
        robotNameCode = "exp";
    } else {
        robotNameCode = "mnr";
    }

    char robotIDStr[100];
    sprintf(robotIDStr, "%d", unqID);

    RobotName = robotNameCode + "-" + robotIDStr;
}

void Robot::operator=(const Robot& other) {
    RobotName = other.RobotName;
    speed = other.speed;
    durability = other.durability;
    maintenanceCost = other.maintenanceCost;
    canMove = other.canMove;
}

void Robot::showInfo() const {
    cout << "Name: " << RobotName << endl;
    cout << "Type: " << RobotType << endl;
    cout << "Speed: " << speed << endl;
    cout << "Durability: " << durability << endl;
    cout << "ManufactureCost: " << manufactureCost << endl;
    cout << "MaintenanceCost: " << maintenanceCost << endl;
    cout << "Can Move: " << (canMove ? 1 : 0) << endl;
}

Robot::~Robot() {

}
/*
****************
END: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/
float Explorer::totalExploredArea = 0;
int Explorer::totalNumberOfSeleniumArea = 0;

Explorer::Explorer(const string& inType, const float inSpeed, const int inDurability) 
    : Robot(inType, inSpeed, inDurability, 3000, 450.0f / inSpeed), exploredArea(0), detectedSelenium(false)
{
    
}

bool Explorer::move() {
    if (getCanMove()) {
        setCanMove(false);
        return true;
    }
    return false;
}

void Explorer::explore() {
    int value = rand() % 101;
    if(value >= 40) {
        detectedSelenium = true;
        totalNumberOfSeleniumArea += 1;
    } else {
        detectedSelenium = false;
    }
    totalExploredArea += 1500;
    exploredArea = 1500;
}

void Explorer::showInfo() const {
    Robot::showInfo();
    cout << "explored area: " << exploredArea << endl;
}

void Explorer::operator=(const Explorer& other) {
    Robot::operator=(other);

    exploredArea = other.exploredArea;
    detectedSelenium = other.detectedSelenium;
}

Explorer::~Explorer() {

}
/*
****************
END: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: MINER CLASS FUNCTION DECLARATIONS 
****************
*/
int Miner::totalGatheredSelenium = 0;
Miner::Miner(const string& inType, const float inSpeed, const int inDurability)
    : Robot(inType, inSpeed, inDurability, 5000, 750.0f / inSpeed), gatheredSelenium(0)
{

}

void Miner::mine() {
    int value = (10 + (rand() % 91)) * 5;
    totalGatheredSelenium += value;
    gatheredSelenium += value;
    Explorer::totalNumberOfSeleniumArea = max(0, Explorer::totalNumberOfSeleniumArea - 1);
}

bool Miner::move() {
    if (getCanMove() && Explorer::getTotalNumberOfSeleniumArea() > 0) {
        setCanMove(false);
        return true;
    }
    return false;
}

void Miner::showInfo() const {
    Robot::showInfo();
    cout << "# of gathered selenium: " << gatheredSelenium << endl;
}

void Miner::operator=(const Miner& other) {
    Robot::operator=(other);

    gatheredSelenium = other.gatheredSelenium;
}

Miner::~Miner() {

}
/*
****************
END: MINER CLASS FUNCTION DECLARATIONS 
****************
*/

