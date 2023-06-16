/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 14/12/2021 */

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

int Huffman::findindex(Token *arr, string elem)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (arr[i].symbol == elem)
        {
            return i;
        }
    }
    return -1;
}

void Huffman::find_frequencies()
{
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt", ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open())
    {
        file_obj.open("input.txt", ifstream::in);
        if (!file_obj.is_open())
        {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol))
    {
        string s;
        s.push_back(symbol);
        index = findindex(token_array, s);
        if (index == -1)
        {
            token_array[token_count].symbol = s;
            token_array[token_count].count++;
            token_count++;
        }
        else
        {
            token_array[index].count++;
        }
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    tail = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)
{
    if (tail == NULL)
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        tail->next = newnode;
        tail = newnode;
    }
    token_count++;
}

Node *PriorityQueue::pop()
{
    int minFrequency = INT32_MAX;
    Node *minNode = NULL;
    Node *minNodePrevious = NULL;
    Node *currentNode = head;
    Node *previousNode = NULL;
    while (currentNode != NULL)
    {
        if (currentNode->token.count < minFrequency)
        {
            minFrequency = currentNode->token.count;
            minNodePrevious = previousNode;
            minNode = currentNode;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (minNode == tail)
    { // If tail is popped
        tail = minNodePrevious;
    }

    if (minNodePrevious == NULL)
    { // If head is popped
        head = head->next;
    }
    else
    {
        minNodePrevious->next = minNode->next;
    }
    token_count--;
    return minNode;
}

void Huffman::get_priority_queue()
{
    for (int i = 0; i < token_count; i++)
    {
        Node *node = new Node();
        node->left = NULL;
        node->right = NULL;
        node->token = token_array[i];
        priority_queue.push(node);
    }
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node *HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    Node *parentNode = new Node();
    parentNode->token.symbol = node1->token.symbol + node2->token.symbol;
    parentNode->token.count = node1->token.count + node2->token.count;
    parentNode->left = node1;
    parentNode->right = node2;
    return parentNode;
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if (traversal != NULL)
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout << "Code with no memory leak ;)" << endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    while (priority_queue.token_count > 1)
    {
        Node *node1 = priority_queue.pop();
        Node *node2 = priority_queue.pop();
        Node *parentNode = huffman_binary_tree.merge(node1, node2);
        priority_queue.push(parentNode);
    }
    huffman_binary_tree.root = priority_queue.pop();
}

void Huffman::get_codes(Node *traversal, string codepart)
{
    traversal->token.code = codepart;
    int index = findindex(token_array, traversal->token.symbol);
    if (index != -1)
    {
        token_array[index].code = codepart;
    }
    if (traversal->left != NULL)
    {
        get_codes(traversal->left, codepart + "0");
    }
    if (traversal->right != NULL)
    {
        get_codes(traversal->right, codepart + "1");
    }
}

string Huffman::return_code(string target)
{
    int index = findindex(token_array, target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for (int i = 0; i < token_count; i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for (int i = 0; i < token_count; i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
