#include <fstream>
#include <iostream>

#include "StudentsTrie.h"

using namespace std;

TrieNode::TrieNode(const char &digit)
{
   this->digit = digit;
   for (int i = 0; i < MAX_CHILDREN; children[i++] = NULL)
      ;
};

void TrieNode::print(std::string previousString)
{
   static int printIndex = 0; // Range: [0, 10]

   if (digit != 'r')
   {
      previousString += digit;
   }

   bool isLeafNode = true;
   for (int i = 0; i < MAX_CHILDREN; i++)
   {
      if (children[i] != NULL)
      {
         isLeafNode = false;

         children[i]->print(previousString);
      }
   }
   if (isLeafNode)
   {
      std::cout << previousString << " ";

      printIndex++;
      if (printIndex >= 10)
      {
         std::cout << std::endl;
         printIndex = 0;
      }
   }
}

// Construct a StudentsTrie using the records in 'file_name'
StudentsTrie::StudentsTrie(const string &file_name)
{
   ifstream student_ids_file(file_name); // ifstream object for input file
   string current_student_id;

   root = new TrieNode('r');

   if (student_ids_file.is_open())
   {
      for (int i = 1; student_ids_file >> current_student_id; i++)
      {
         insert_id(current_student_id); // YOU HAVE TO IMPLEMENT insert_id() METHOD
      }
      student_ids_file.close();
   }
   else
   {
      cout << "File: " << file_name << " could NOT be opened!!";
      exit(1);
   }

   student_ids_file.close();
};

// Insert a student ID into the StudentsTrie
void StudentsTrie::insert_id(const string &student_id)
{
   TrieNode *iteratedTrieNodePtr = root;
   for (int i = 0; i < student_id.size(); i++)
   {
      int intValue = stoi(std::string(1, student_id[i]));
      TrieNode *searchedChildPtr = iteratedTrieNodePtr->children[intValue];
      if (searchedChildPtr == NULL)
      {
         iteratedTrieNodePtr->children[intValue] = new TrieNode(student_id[i]);
      }
      iteratedTrieNodePtr = iteratedTrieNodePtr->children[intValue];
   }
};

// Print Student IDs in Trie in ascending order
void StudentsTrie::print_trie()
{
   root->print();
}

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie()
{
   for (int i = 0; i < MAX_CHILDREN; i++)
   {
      if (root->children[i])
         delete root->children[i];
   };
};
