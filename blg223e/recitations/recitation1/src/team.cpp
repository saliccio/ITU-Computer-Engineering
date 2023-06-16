/* @Author 
Student Name:  Furkan Salık
Student ID :  150200056
Date: 12/10/2021 */


#include "team.h"

using namespace std;

Team::Team(){};
string Team::getName() { return name; };
int Team::getCurrentSize() { return current_size; };
int Team::getId() { return id; };
int Team::getCapacity() { return capacity; };
Player *Team::getPlayer(int number)
{
    for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return &player_list[i];
    }
    return nullptr;
};
Player *Team::getPlayerList()
{
    return player_list;
};
void Team::setName(string new_name) { name = new_name; };
void Team::setId(int newId) { id = newId; };
void Team::listPlayers()
{
    cout << "Number"
         << " Name"
         << " Age"
         << " #Goals"
         << " #Assists"
         << " #Matches" << endl;
    ;
    for (int i = 0; i < current_size; i++)
    {
        cout << player_list[i].getNumber() << " - ";
        cout << player_list[i].getName() << " - ";
        cout << player_list[i].getAge() << " - ";
        cout << player_list[i].getGoalNumber() << " - ";
        cout << player_list[i].getAssistNumber() << " - ";
        cout << player_list[i].getMatchNumber() << endl;
    }
};
void Team::addPlayer(int number, string name, int age, int goals, int assists, int matches)
{
    bool exists = checkNumber(number);

    if (!exists)
    {
        current_size++;


        // checking if capacity increase is needed
        bool alteredCapacity = false;
        if (capacity == 0)
        {
            capacity += 3;
            alteredCapacity = true;
        }
        else if (current_size > capacity)
        {
            capacity = capacity * 2;
            alteredCapacity = true;
        }


        // if capacity has been changed, extend the array
        if (alteredCapacity)
        {
            Player *newArray = new Player[capacity];


            // copying values from the old array
            for (int i = 0; i < current_size - 1; i++)
            {
                newArray[i] = player_list[i];
            }


            // deleting the old array and making the pointer point to the new array
            delete[] player_list;
            player_list = newArray;
        }


        // setting the data of the new element
        player_list[current_size - 1].setNumber(number);
        player_list[current_size - 1].setName(name);
        player_list[current_size - 1].setAge(age);
        player_list[current_size - 1].setGoalNumber(goals);
        player_list[current_size - 1].setAssistNumber(assists);
        player_list[current_size - 1].setMatchNumber(matches);
    }
    return;
};

bool Team::checkNumber(int number)
{
    for (int i = 0; i < current_size; i++)
    {
        if (player_list[i].getNumber() == number)
            return true;
    }
    return false;
}