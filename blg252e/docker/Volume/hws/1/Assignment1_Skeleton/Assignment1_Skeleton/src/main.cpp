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
#include <fstream>

#include "pokemon.h"

using namespace std;

//-------------Do Not Change These Global Variables-------------//
int NAME_COUNTER = 0;   //Use this to keep track of the enemy names
int POK_COUNTER = 0;    //Use this to keep track of the pokemon names
int PLAYER_POKEMON_ATTACK = 20; //You don't have to use this variable but its here if you need it
int ENEMY_POKEMON_ATTACK = 10;  //You don't have to use this variable but its here if you need it
//--------------------------------------------------------------//

//---If Necessary Add Your Global Variables Here---// 
int ENEMY_COUNT = 0;
int POK_COUNT = 0;
//
//
//-------------------------------------------------//

//-------------Do Not Change These Function Definitions-------------//
string* readEnemyNames(const char*);
string* readPokemonNames(const char*);
player characterCreate(string, int);
void mainMenu();
void fightEnemy(player*, string*, string*);
void catchPokemon(player*, string*);
//------------------------------------------------------------------//

//---If Necessary Add Your Function Definitions Here---// 
string getPokemonNameByID(const int& index);  // Returns the name of the pokemon specified by the index.
//
//
//-----------------------------------------------------//

//-------------Do Not Change This Function-------------//
int main(int argc, char* argv[]){
	system("clear");

    //---Creating Enemy and Pokemon Name Arrays---//
    string* enemyNames = readEnemyNames(argv[1]);         
    string* pokemonNames = readPokemonNames(argv[2]);
    

    string playerName;
    int pokemonChoice;

    cout << "Welcome to the Pokemon Game! \n" << endl;
    cout << "Please enter your name: "; 
    cin >> playerName;
    cout << "Please choose one of these pokemons as your pokemon: \n1- Bulbasaur \n2- Charmender \n3- Squirtle \nChoice: ";
    cin >> pokemonChoice;

    //---Character Creation--//
    player newPlayer = characterCreate(playerName, pokemonChoice);
    
    int menuChoice;

    while(true){
        mainMenu(); 
        cin>>menuChoice;

        switch (menuChoice){
        case 1:
            fightEnemy(&newPlayer, enemyNames, pokemonNames);
            break;
        case 2:
            catchPokemon(&newPlayer, pokemonNames);
            break;
        case 3:
            cout<<newPlayer.showPokemonNumber()<<endl;
            break;
        case 4:
            cout<<newPlayer.showPokeballNumber()<<endl;
            break;
        case 5:
            cout<<newPlayer.showBadgeNumber()<<endl;
            break;
        case 6:
            cout << endl;
            cout << "------- Pokedex -------" <<endl;
            newPlayer.playerPokedex.printPokedex();
            break;
        case 7:
            //---Deletes Dynamic Arrays From Memory and Exits---//
            delete[] enemyNames;
            delete[] pokemonNames;
            return EXIT_SUCCESS;
            break;
  
        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readEnemyNames(const char* argv){
    ifstream enemyNamesStream;
    enemyNamesStream.open(argv, std::ios_base::openmode::_S_out);
    string line;  // Read data will be inside this, line-by-line.
    getline(enemyNamesStream, line);
    ENEMY_COUNT = stoi(line);  // First line is the length.

    string* enemiesArray = new string[ENEMY_COUNT];
    unsigned int arrayIndex = 0U;  // This tracks the indexes of the array, to insert the data into.

    while(getline(enemyNamesStream, line)){
        enemiesArray[arrayIndex] = line;
        arrayIndex += 1U;
    }

    enemyNamesStream.close();

    return enemiesArray;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readPokemonNames(const char* argv){
    ifstream pokemonNamesStream;
    pokemonNamesStream.open(argv, std::ios_base::openmode::_S_out);
    string line;  // Read data will be inside this, line-by-line.
    getline(pokemonNamesStream, line);
    POK_COUNT = stoi(line);  // First line is the length.
    string* pokemonsArray = new string[POK_COUNT];
    unsigned int arrayIndex = 0U;  // This tracks the indexes of the array, to insert the data into.

    while(getline(pokemonNamesStream, line)){
        pokemonsArray[arrayIndex] = line;
        arrayIndex += 1U;
    }

    pokemonNamesStream.close();

    return pokemonsArray;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
player characterCreate(string playerName, int pokemonChoice){
    string pokemonName = getPokemonNameByID(pokemonChoice);

    return player(playerName, pokemon(pokemonName, PLAYER_POKEMON_ATTACK));
};
//--------------------------------------------//

//-------------Do Not Change This Function-------------//
void mainMenu(){
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Fight for a badge" << endl;
    cout << "2. Catch a Pokemon" << endl;
    cout << "3. Number of Pokemons" << endl;
    cout << "4. Number of Pokeballs " << endl;
    cout << "5. Number of Badges" << endl;
    cout << "6. Pokedex" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
void fightEnemy(player* newPlayer, string* enemyNames, string* pokemonNames){
    pokemon pokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK);

    enemy enemy(enemyNames[NAME_COUNTER], pokemon);

    newPlayer->playerPokedex.updatePokedex(pokemon);

    NAME_COUNTER += 1;
    if (NAME_COUNTER >= ENEMY_COUNT){
        NAME_COUNTER = 0;
    }
    POK_COUNTER += 1;
    if (POK_COUNTER >= POK_COUNT){
        POK_COUNTER = 0;
    }

    newPlayer->getPokemon().setHP(100);
    enemy.getPokemon().setHP(100);

    cout << "You encounter with " << enemy.getName() << " and his/hers pokemon " << enemy.getPokemon().getName() << endl 
         << enemy.getPokemon().getName() << " Health: " << enemy.getPokemon().getHP() << " Attack: " << enemy.getPokemon().getAttackValue() << endl;

    bool fightContinues = true;
    while(fightContinues) {
        cout << "1- Fight" << endl
             << "2- Runaway" << endl
             << "Choice: ";
        int choice;
        cin >> choice;
        switch(choice){
            case 1:
            {
                newPlayer->getPokemon().setHP(newPlayer->getPokemon().getHP() - enemy.getPokemon().getAttackValue());
                enemy.getPokemon().setHP(enemy.getPokemon().getHP() - newPlayer->getPokemon().getAttackValue());

                int playerHP = newPlayer->getPokemon().getHP();
                int enemyHP = enemy.getPokemon().getHP();

                cout << "Your Pokemons Health: " << playerHP << endl 
                     << enemy.getName() << " Pokemons Health: " << enemyHP << endl;

                if(playerHP <= 0){
                    fightContinues = false;
                    break;
                }
                if(enemyHP <= 0){
                    cout << "You Won!" << endl;
                    newPlayer->battleWon();
                    fightContinues = false;
                    break;
                }
                break;
            }
            case 2:
            {
                fightContinues = false;
                break;
            }
        }
    }
};
//--------------------------------------------//

//-------------Code This Function-------------//
void catchPokemon(player* newPlayer, string* pokemonNames){
    string pokemonName = pokemonNames[POK_COUNTER];
    newPlayer->playerPokedex.updatePokedex(pokemon(pokemonName, ENEMY_POKEMON_ATTACK));

    POK_COUNTER += 1;
    if (POK_COUNTER >= POK_COUNT){
        POK_COUNTER = 0;
    }

    cout << "You encounter with " << pokemonName << " Health: 100 Attack: 10" << endl 
         << "1- Catch" << endl
         << "2- Runaway" << endl
         << "Choice: ";
    
    int choice;
    cin >> choice;
    if(choice == 1){
        cout << "You catch " << pokemonName << endl;
        newPlayer->catchPokemon();
    }
};
//--------------------------------------------//

string getPokemonNameByID(const int& index){
    switch(index){
        case 1:
            return "Bulbasaur";
            break;
        case 2:
            return "Charmender";
            break;
        case 3:
            return "Squirtle";
            break;
    }
    return "";
}