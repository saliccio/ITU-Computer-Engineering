/* @Author 
Student Name:  Furkan Salık
Student ID :  150200056
Date: 12/10/2021 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "team.h"
using namespace std;

bool perform_operation(char choice);
void print_menu();
void listTeams();
void listTeamsAndPlayers();
void bestPlayer();
void addPlayer(int team_no);
void addTeam(string name);

int current_size = 4;
Team *tarr = new Team[current_size];

int main()
{
    tarr[0].setName("Liverpool F.C.");
    tarr[0].setId(0);
    tarr[1].setName("S.S. Lazio");
    tarr[1].setId(1);
    tarr[2].setName("A.C. Milan");
    tarr[2].setId(2);
    tarr[3].setName("Barcelona");
    tarr[3].setId(3);
    tarr[0].addPlayer(8, "Steven George Gerrard", 32, 14, 12, 10);
    tarr[0].addPlayer(9, "Fernando Torres", 37, 13, 11, 10);
    tarr[0].addPlayer(7, "Luis Suares", 33, 12, 12, 12);
    tarr[1].addPlayer(9, "Hernan Crespo", 23, 13, 14, 13);
    tarr[1].addPlayer(11, "Miroslav Klose", 27, 11, 15, 13);
    tarr[1].addPlayer(7, "Simone Inzaghi", 22, 10, 16, 15);
    tarr[2].addPlayer(11, "Filippo Inzaghi", 37, 12, 11, 15);
    tarr[2].addPlayer(21, "Pablo Maldini", 37, 13, 9, 9);
    tarr[2].addPlayer(33, "Ricardo Kaka", 29, 13, 8, 8);
    tarr[3].addPlayer(10, "Lionel Messi", 30, 16, 18, 14);
    tarr[3].addPlayer(9, "Samuel Etoo", 19, 14, 12, 13);
    tarr[3].addPlayer(7, "Andres Iniesta", 24, 13, 12, 11);
    bool end = false;
    char choice;
    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    delete[] tarr;
    return EXIT_SUCCESS;
}

void addTeam(string team_name)
{
    current_size++;

    // extending the array
    Team* newArray = new Team[current_size];


    // copying values from the old array
    for(int i = 0; i < current_size - 1; i++){
        newArray[i] = tarr[i];
    }

    // setting the data for the new team
    newArray[current_size - 1].setId(current_size - 1);
    newArray[current_size - 1].setName(team_name);
    

    // deleting the old array and making the pointer point to the new array
    delete[] tarr;
    tarr = newArray;

    return;
};


void print_menu()
{
    cout << endl
         << endl;
    cout << "Who is the best player?" << endl;
    bestPlayer();
    cout << "Choose an operation" << endl;
    cout << "A: Add player" << endl;
    cout << "S: Show players" << endl;
    cout << "L: List teams" << endl;
    cout << "T: Add a new team" << endl;
    cout << "E: Exit" << endl;
    cout << endl;
    cout << "Enter a choice {A, S, L, T, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    int team_id;
    string team_name;
    switch (choice)
    {
    case 'A':
    case 'a':
        listTeams();
        cout << "To which team?(0, 1, 2...):";
        cin >> team_id;
        addPlayer(team_id);
        break;
    case 'S':
    case 's':
        listTeamsAndPlayers();
        break;
    case 'L':
    case 'l':
        listTeams();
        break;
    case 'T':
    case 't':
        cout << "Enter the team name:";
        cin >> team_name;
        addTeam(team_name);
        break;
    case 'E':
    case 'e':
        cout << "Are you sure you want to exit the program? (Y/N):";
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
            terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cout << "Please try again {A, S, L, T, E}  :";
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}
void listTeams()
{
    for (int i = 0; i < current_size; i++)
    {
        cout << "Team " << tarr[i].getId() << ": ";
        cout << tarr[i].getName() << endl;
    }
};

void listTeamsAndPlayers()
{
    for (int i = 0; i < current_size; i++)
    {
        cout << "Team " << tarr[i].getId() << ": " << tarr[i].getName() << endl;
        tarr[i].listPlayers();
    }
};
void addPlayer(int team_id)
{
    string name;
    int number;
    int age;
    int goals;
    int assists;
    int matches;
    cout << "Enter the player name:";
    cin.ignore(1000, '\n');
    getline(cin, name);
    cout << "Enter the player's jersey number:";
    cin >> number;
    while (tarr[team_id].checkNumber(number))
    {
        cout << "The Jersey number " << number << " is owned by another player in the team! Try another number or enter -1 to cancel adding player:" << endl;
        cin >> number;
        if (number == -1)
            return;
    }
    cout << "Enter the player age:";
    cin >> age;
    cout << "Enter the total number of goals that player scored:";
    cin >> goals;
    cout << "Enter the total number of assists that player recorded:";
    cin >> assists;
    cout << "Enter the total number of matches that player played:";
    cin >> matches;
    tarr[team_id].addPlayer(number, name, age, goals, assists, matches);
};

void bestPlayer()
{
    float best_score = 0;
    int team = 0;
    int player = 0;
    for (int i = 0; i < current_size; i++)
    {
        for (int j = 0; j < tarr[i].getCurrentSize(); j++)
        {
            if (tarr[i].getPlayerList()[j].score() > best_score)
            {
                best_score = tarr[i].getPlayerList()[j].score();
                team = i;
                player = j;
            }
        }
    }
    cout << tarr[team].getPlayerList()[player].getName() << ", Number: " << tarr[team].getPlayerList()[player].getNumber() << " Team: " << tarr[team].getName() << endl;
}
