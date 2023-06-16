/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 9/11/2021 */

#include <iostream> 
#include <stdlib.h>
#include <fstream>


#include "linkedList.h"

using namespace std;

void menu();


int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows

    menu();

    return EXIT_SUCCESS;
}


void menu(){

    Train newTrain;
    newTrain.create();

    int entry;
    char cargo;
    int weight;

    while(true){
        cout<<"Welcome to train station!"<<endl;
        cout<<"What would you like to do?"<<endl;
        cout<<"1 - Load Weight"<<endl<<"2 - Unload Weight"<<endl<<"3 - Print train info"<<endl<<"4 - Exit"<<endl;
        cin>>entry;

        if(entry == 1){
            cout<<"Which material you would like to load?"<<endl;
            cout<<"A - Glass"<<endl<<"B - Oak"<<endl<<"C - Coal"<<endl<<"D - Iron"<<endl;
            cin>>cargo;
            cout<<"Enter desired weight to be loaded"<<endl;
            cin>>weight;
            newTrain.addMaterial(toupper(cargo),weight);
            cout<<"Train cargo info"<<endl;
            newTrain.printWagon();
        }
        else if(entry == 2){
            cout<<"Which material you would like to unload?"<<endl;
            cout<<"A - Glass"<<endl<<"B - Oak"<<endl<<"C - Coal"<<endl<<"D - Iron"<<endl;
            cin>>cargo;
            cout<<"Enter desired weight to be unloaded"<<endl;
            cin>>weight;
            newTrain.deleteFromWagon(toupper(cargo),weight);
            cout<<"Train cargo info"<<endl;
            newTrain.printWagon();
        }
        else if(entry == 3){
            cout<<"Train cargo info"<<endl;
            newTrain.printWagon();
        }
        else if(entry == 4){
            break;
        }
        else{
            cout<<"Please enter one of the numbers stated above"<<endl;
        }
    }
};