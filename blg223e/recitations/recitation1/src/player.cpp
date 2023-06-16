/* @Author 
Student Name:  Furkan Salık
Student ID :  150200056
Date: 12/10/2021 */



#include "player.h"
using namespace std;

Player::Player(string name, int number, int age, int goal_number, int assist_number, int match_number){
    setName(name);
    setNumber(number);
    setAge(age);
    setGoalNumber(goal_number);
    setAssistNumber(assist_number);
    setMatchNumber(match_number);
};
Player::Player(){};
string Player::getName(){
    return name;
};
int Player::getNumber(){
    return number;
};
int Player::getGoalNumber(){
    return goal_number;
};
int Player::getAge(){
    return age;
};
int Player::getAssistNumber(){
    return assist_number;
};
int Player::getMatchNumber(){
    return match_number;
};
void Player::setName(string new_name){name=new_name;};
void Player::setNumber(int new_number){number=new_number;};
void Player::setAge(int new_age){age=new_age;};
void Player::setGoalNumber(int new_goal_number){goal_number=new_goal_number;};
void Player::setAssistNumber(int new_assist_number){assist_number=new_assist_number;};
void Player::setMatchNumber(int new_match_number){match_number=new_match_number;};
float Player::score(){
    return (goal_number/match_number)*3+(assist_number/match_number)*1+(45-age);
};