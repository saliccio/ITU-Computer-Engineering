//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

#include <iostream>
#include "Robot.h"
using namespace std;
class Crew{
	private:
		friend class CommandCenter;

		int maxExplorers;
		int maxMiners;
		int crewManufactureCost;
		float crewMaintenanceCost;
		int explorerCrewSize;
		int minerCrewSize;
		Explorer **ExplorerCrew;
		Miner **MinerCrew;

	public:
		Crew(int, int, int, int);

		void initMovement();
		void updateDurability();

		Robot* manufactureRobot(string = "") const;
		void showInfo() const;

		Crew& operator+=(Robot*);
		Crew& operator-=(const string&);

		inline int getCrewManufactureCost() const { return crewManufactureCost; }

		inline float getCrewMaintenanceCost() const { return crewMaintenanceCost; }
		inline void setCrewMaintenanceCost(float inMaintenanceCost) { crewMaintenanceCost = inMaintenanceCost; }

		inline Explorer** getExplorers() const { return ExplorerCrew; }
		inline int getExplorerCrewSize() const { return explorerCrewSize; }

		inline Miner** getMiners() const { return MinerCrew; }
		inline int getMinerCrewSize() const { return minerCrewSize; }

		~Crew();
};

class CommandCenter {
	private:
		const int neededSelenium;
		const float searchArea;
		const int seleniumWorth;
		int turnCount;
		float totalCrewMaintenanceCost;
		float profit;
	public:
		CommandCenter(const int, const int, const int);

		bool isGameEnded() const;
		void calculateProfit(const Crew&);
		void showInfo() const;

		void operator++();

};



