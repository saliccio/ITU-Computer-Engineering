//--- 2021-2022 Summer Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Furkan Salık
//---Student Number: 150200056
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "pokemon.h"

using namespace std;

//-------------You Can Add Your Functions Down Below-------------//
pokemon::pokemon() 
    : name(""), hpValue(100), atkValue(0)
{

}

pokemon::pokemon(const string& inName, const int& inAtkValue)
    : name(inName), hpValue(100), atkValue(inAtkValue)
{

}

pokemon::pokemon(const pokemon& other)
    : name(other.getName()), hpValue(other.getHP()), atkValue(other.getAttackValue())
{

}

pokedex::pokedex()
    : value(0)
{

}

bool pokedex::updatePokedex(const pokemon& inNewPokemon)
{
    for(int i = 0; i < value; i++){
        if(pokedexArray[i] == inNewPokemon){
            return false;
        }
    }

    if(value == 100){
        return false;  // If the array is full, do not add.
    }

    pokedexArray[value] = inNewPokemon;
    value++;

    return true;
}

void pokedex::printPokedex() const 
{
    for(int i = 0; i < value; i++){
        cout << pokedexArray[i].getName() << endl;
    }
}

player::player()
    : name(""), pokemonNumber(0), pokeballNumber(0), badgeNumber(0)
{

}

player::player(const string& inName, const pokemon& inPokemon)
    : name(inName), pokemonNumber(0), pokeballNumber(10), badgeNumber(0), playerPokemon(inPokemon)
{

}

void player::battleWon()
{
    badgeNumber += 1;
    pokeballNumber += 3;
}

void player::catchPokemon()
{
    pokemonNumber += 1;
    pokeballNumber -= 1;
}

enemy::enemy()
    : name("")
{

}

enemy::enemy(const string& inName, const pokemon& inPokemon)
    : name(inName), enemyPokemon(inPokemon)
{
    
}