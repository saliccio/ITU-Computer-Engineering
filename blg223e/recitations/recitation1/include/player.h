/* @Author 
Student Name:  Furkan Salık
Student ID :  150200056
Date: 12/10/2021 */


# pragma once
#include <iostream>
#include <string>

class Player
    {
    private:
        int number;
        int age;
        std::string name;
        int goal_number;
        int assist_number;
        int match_number;
    public:
        Player(std::string name, int number, int age, int goal_number, int assist_number, int match_number);
        Player();
        std::string getName();
        int getNumber();
        int getGoalNumber();
        int getAssistNumber();
        int getMatchNumber();
        int getAge();
        void setName(std::string name);
        void setNumber(int number);
        void setAge(int new_age);
        void setGoalNumber(int goal_number);
        void setAssistNumber(int assist_number);
        void setMatchNumber(int match_number);
        float score();
    };

