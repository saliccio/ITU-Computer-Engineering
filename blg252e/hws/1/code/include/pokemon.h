//--- 2021-2022 Summer Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

#ifndef _H
#define _H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//-------------Do Not Add Any New Class(es)-------------//

class pokemon{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        int hpValue;
        int atkValue;
    public:
       pokemon();
       pokemon(const string& inName, const int& inAtkValue);
       pokemon(const pokemon& other);

       inline const string& getName() const { return name; }
       inline const int& getHP() const { return hpValue; }
       inline const int& getAttackValue() const { return atkValue; }

       inline void setHP(const int& inHP) { hpValue = inHP; }

       inline bool operator==(const pokemon& inOther) const { return name == inOther.getName(); }
};

class pokedex{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        pokemon pokedexArray[100];
        int value;
    public:
       pokedex();

       bool updatePokedex(const pokemon& inNewPokemon);  // Returns whether the addition to the array was successful.
       void printPokedex() const;
};

class player{
    private:
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
        string name;
        int pokemonNumber;
        int pokeballNumber;
        int badgeNumber;
        pokemon playerPokemon;
    public:
        pokedex playerPokedex;

        player();
        player(const string& inName, const pokemon& inPokemon);

        inline const int& showPokemonNumber() const { return pokemonNumber; }
        inline const int& showPokeballNumber() const { return pokeballNumber; }
        inline const int& showBadgeNumber() const { return badgeNumber; }
        inline pokemon& getPokemon() { return playerPokemon; }

        void battleWon();
        void catchPokemon();
};

class enemy{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        pokemon enemyPokemon;
    public:
        enemy();
        enemy(const string& inName, const pokemon& inPokemon);

        inline const string& getName() const { return name; }
        inline pokemon& getPokemon() { return enemyPokemon; }
};

#endif