//
// Created by Dylon on 12/1/2023.
//

#ifndef FINAL_PROJECT_NODE_H
#define FINAL_PROJECT_NODE_H
#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string value;
    long video;
    long subscriber;
    string date;

    Node(string name, long vid, long sub, string time);
};


#endif //FINAL_PROJECT_NODE_H
