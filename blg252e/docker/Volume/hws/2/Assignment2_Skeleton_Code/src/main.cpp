#include <iostream>
using namespace std;
#include "Robot.h"
#include "CommandCenter.h"

void commandMenu(){
	
	cout<<"1. Search for selenium"<<endl;
	cout<<"2. Dig out seleniums"<<endl;
	cout<<"3. Manufacture a Robot"<<endl;
	cout<<"4. Disassemble a Robot"<<endl;
	cout<<"5. Show team information"<<endl;
	cout<<"6. Show stats"<<endl;
	cout<<"7. End Turn"<<endl;
	cout<<"8. Exit Game"<<endl;
	cout<<"Choice:"<<endl;
}


int main(){
	srand(99);

	bool manualExit = false;
	bool endTurn = false;
	int crewMaxExplorers;
	int crewMaxMiners;
	int explorerCrewSize;
	int minerCrewSize;
	const int seleniumWorth = 30;
	const int seleniumAim = 800;
	const int exploreArea = 13500;
	cout<<"Welcome to the Command Station Chief!"<<endl;
	cout<<"Prepare your Robot Crew and start mining!"<<endl;
	cout<<"Throughout the game you can expand your crew."<<endl;
	cout<<"What should be your maximum explorer crew size (1-5)?"<<endl; 
	cin>>crewMaxExplorers;
	cout<<"What should be your maximum miner crew size (1-5)?"<<endl; 
	cin>>crewMaxMiners;
	cout<<"How many explorers will you manufacture now?"<<endl;
	cin>>explorerCrewSize;
	cout<<"How many miners will you manufacture now?"<<endl;
	cin>>minerCrewSize;
	Crew Crew(crewMaxExplorers,crewMaxMiners,explorerCrewSize,minerCrewSize);
	Crew.showInfo();
	
	CommandCenter commandCenter(seleniumAim,exploreArea,seleniumWorth); 
	
	while (true)
	{
		// each turn check if the game can be finished or not.
		if(endTurn){
			if (commandCenter.isGameEnded()){
				break;
			}
			endTurn=false;
		}
		if(manualExit){
			cout<<"Farewell Chief!";
			break;
		}
		int decision;
		commandMenu();
		cin>>decision;
		string robotToBeRemoved = "NaN";
		switch (decision)
		{
		case 1:
			for (int i = 0; i < Crew.getExplorerCrewSize(); i++)
			{ 
				bool isMoving = Crew.getExplorers()[i]->move();// can this robot move?
				if (isMoving){
					Crew.getExplorers()[i]->explore();
					Crew.getExplorers()[i]->setCanMove(false);
					Crew.setCrewMaintenanceCost(Crew.getCrewMaintenanceCost()+Crew.getExplorers()[i]->getMaintenanceCost());
				}
				else{
					cout<<Crew.getExplorers()[i]->getName()<<" can't take an action Chief!"<<endl;
				}
				
				
			}
			commandCenter.showInfo();
			break;
		case 2:
			for (int i = 0; i < Crew.getMinerCrewSize(); i++)
			{ 
				
				bool isMoving = Crew.getMiners()[i]->move();// can this robot move?
				if (isMoving){
					Crew.getMiners()[i]->mine();
					Crew.getMiners()[i]->setCanMove(false);
					Crew.setCrewMaintenanceCost(Crew.getCrewMaintenanceCost()+Crew.getMiners()[i]->getMaintenanceCost());
					
				}
				else{
					cout<<Crew.getMiners()[i]->getName()<<" can't take an action Chief!"<<endl;
				}
				
				
			}
			commandCenter.showInfo();
			break;
		case 3:
			Crew+=Crew.manufactureRobot();
			Crew.showInfo();
			break;
		case 4:
			
			cout<<"Enter the name of the robot that you want to disassemble"<<endl;
			cin>>robotToBeRemoved;
			Crew-=robotToBeRemoved;
			Crew.showInfo();
			break;
		case 5:
			Crew.showInfo();
			break;
		case 6:
			commandCenter.showInfo();
			break;
		case 7:
			cout<<"Turn ends..."<<endl;
			endTurn = true; // turn is ended.
			Crew.initMovement(); // set your robots' canMove to true
			Crew.updateDurability(); // update durabilities
			commandCenter.calculateProfit(Crew); // calculate profit
			++commandCenter; // increment turn count;
			cout<<"Your robots are ready!"<<endl;
			break;
		case 8:
			manualExit = true;
			break;
		default:
			break;
		}
	}
	
	
	return 0;

}