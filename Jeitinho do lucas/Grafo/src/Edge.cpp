#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Edge's methods
**************************************************************************************************/

// Constructor
Edge::Edge(int target_id, int Id){

    this->Source = 1;
    this->id = Id;
    this->target_id = target_id;
    this->next_edge = nullptr;
    this->weight = 0;

}

// Destructor
Edge::~Edge(){

    if (this->next_edge != nullptr){
        delete this->next_edge;
        this->next_edge = nullptr;
    }

}

// Getters
int Edge::getTargetId(){

    return this->target_id;

}

Edge* Edge::getNextEdge(){

    return this->next_edge;

}

float Edge::getWeight(){

    return this->weight;

}

int Edge::getSource(){
    return this->Source;
}

// Setters
void Edge::setNextEdge(Edge* edge){

    this->next_edge = edge;

}

void Edge::setWeight(float weight){

    this->weight = weight;

}

void Edge::setSource(int source){
    this->Source = source;
}


void Edge::setId(int id){
    this->id = id;
}
