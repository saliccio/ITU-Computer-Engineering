//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//
#include <iostream>
#ifndef _H
#define _H
using namespace std;
class Robot {
	private:
		friend class Crew;
	
		static int unqID;

		string RobotName;
		const string RobotType;
		float speed; 
		int durability; 
		const int manufactureCost; 
		float maintenanceCost;
		bool canMove;
	
	public:
		Robot(const string&, const float, const int, const int, const float);

		void operator=(const Robot&);

		virtual void showInfo() const;

		inline bool getCanMove() const { return canMove; }
		inline void setCanMove(bool inCanMove) { canMove = inCanMove; }

		inline float getMaintenanceCost() const { return maintenanceCost; }
		inline const string& getName() const { return RobotName; }


		virtual ~Robot();
}; 

class Explorer : public Robot {
	private:
		friend class Miner;
		friend class CommandCenter;

		static float totalExploredArea;
		static int totalNumberOfSeleniumArea;

		float exploredArea;
		bool detectedSelenium;
		
		
	public:
		Explorer(const string&, const float, const int);

		bool move();
		void explore();
		virtual void showInfo() const;

		void operator=(const Explorer&);

		inline static int getTotalNumberOfSeleniumArea() { return totalNumberOfSeleniumArea; }

		virtual ~Explorer();
};

class Miner : public Robot {
	private:
		friend class CommandCenter;

		static int totalGatheredSelenium;

		int gatheredSelenium;
		
	public:
		Miner(const string&, const float, const int);

		void mine();
		bool move();
		virtual void showInfo() const;

		void operator=(const Miner&);

		virtual ~Miner();
};


#endif