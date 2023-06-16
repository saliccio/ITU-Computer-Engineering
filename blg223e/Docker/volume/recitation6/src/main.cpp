/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 10/01/2022 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>

using namespace std;

string file_path;

bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();

unordered_map<string, double> revenues;        // <Product Type, Total Revenue>
map<pair<string, string>, double> dayRevenues; // <<Day, Product Type>, Total Revenue>

string days[] = {"Monday", "Sunday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int main(int argc, char *argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;

    file_path = argv[1];

    inFile.open(file_path, ios::in);
    if (!inFile.is_open())
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    string line;
    getline(inFile, line); // Skip head row
    while (getline(inFile, line))
    {
        string splitted[4];
        int splitIndex = 0;
        for (auto it = line.begin(); it != line.end(); it++)
        {
            if (*it == ' ')
            {
                splitIndex++;
                continue;
            }
            splitted[splitIndex] += *it;
        }
        double totalRevenue = stof(splitted[1]) * stoi(splitted[2]);
        revenues[splitted[0]] += totalRevenue;
        dayRevenues[make_pair(splitted[3], splitted[0])] += totalRevenue;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }

    inFile.close();
    return EXIT_SUCCESS;
}

void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "D: List 5 products with the highest revenue for each day" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, D, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'D':
    case 'd':
        listDay();
        break;
    case 'E':
    case 'e':
        terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{
    multimap<double, string> reverseRevenues;
    for (auto it = revenues.begin(); it != revenues.end(); it++)
    {
        reverseRevenues.insert(make_pair(it->second, it->first));
    }

    cout << "5 products with the highest revenue for total are:" << endl;
    int count = 0;
    for (auto it = reverseRevenues.rbegin(); count < 5; it++, count++)
    {
        cout << it->second << " " << fixed << setprecision(2) << it->first << endl;
    }
}

void listDay()
{
    multimap<double, string> reverseDayRevenues[7];
    for (int i = 0; i < 7; i++)
    {
        for (auto it = dayRevenues.begin(); it != dayRevenues.end(); it++)
        {
            if (it->first.first == days[i])
            {
                reverseDayRevenues[i].insert(make_pair(it->second, it->first.second));
            }
        }

        cout << "5 products with the highest revenue for " << days[i] << " are:" << endl;
        int count = 0;
        for (auto it = reverseDayRevenues[i].rbegin(); count < 5; it++, count++)
        {
            cout << it->second << " " << fixed << setprecision(2) << it->first << endl;
        }
    }
}