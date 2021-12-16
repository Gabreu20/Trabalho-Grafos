#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <iterator>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}


Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::imprimir()
{
    cout << endl;
    if (this->first_node!=nullptr)
    {
        Node *next_node = this->first_node;

        while (next_node != nullptr)
        {
            cout << "(";
            cout << next_node->getInDegree();
            cout << ") ";
            cout << next_node->getId();
            cout << " (";
            cout << next_node->getOutDegree();
            cout << ")";
            Edge *next_edge = next_node->getFirstEdge();

            while(next_edge != nullptr)
            {
                cout << " -> " << next_edge->getTargetId();
                next_edge = next_edge->getNextEdge();
            }
            cout << endl;

            next_node = next_node->getNextNode();
        }
    }
}
void Graph::addNode(Node *Id)
{
    Node *pecado = new Node(Id->getId());

    pecado->last_edge=Id->last_edge;
    pecado->first_edge=Id->first_edge;
    pecado->in_degree=Id->in_degree;
    pecado->out_degree=Id->out_degree;
    pecado->weight=Id->weight;
    pecado->next_node=nullptr;

    if (this->first_node==nullptr)
    {
        this->first_node= pecado;
        this->last_node= pecado;
    }
    else
    {

        Node *aux=last_node;
        aux->setNextNode(pecado);
        last_node=pecado;
    }
}


void Graph::insertNode(int id)
{
    if (this->first_node==nullptr)
    {
        Node *p = new Node(id);
        this->first_node= p;
        this->last_node=p;
    }
    else
    {
        Node *aux=this->last_node;
        Node *p = new Node(id);
        aux->setNextNode(p);
        this->last_node=p;
    }
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    if (this->first_node!=nullptr)
    {
        int achado=0;   // variavel que verifica se o indice ja foi achado

        Node *next_node = this->first_node;
        while (next_node != nullptr && achado==0 )
        {
            if(next_node->getId()==id)
            {
                //addciona edge
                next_node->insertEdge(target_id,weight);
                next_node->incrementOutDegree();
                Node* target = getNode(target_id);
                target->incrementInDegree();
                achado=1;
            }
            next_node = next_node->getNextNode();
        }
    }

}

void Graph::removeNode(int id)
{
    if (this->first_node!=nullptr)
    {

        Node *aux1;
        Node *aux2;
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if(next_node->getId()==id)
            {
                if(next_node==this->first_node)
                {
                    aux2=next_node->getNextNode();
                    first_node=aux2;
                    delete next_node;
                }
                else if (next_node==this->last_node)
                {
                    last_node=aux1;
                    delete next_node;
                }
                else
                {
                    aux2=next_node->getNextNode();
                    aux1->setNextNode(aux2);
                    delete next_node;
                }

            }
            aux1=next_node;
            next_node = next_node->getNextNode();
        }
    }
}

bool Graph::searchNode(int id)
{
    if (this->first_node!=nullptr)
    {
        int achado=0;   // variavel que verifica se o indice ja foi achado
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if(next_node->getId()==id)
                return 1;
            next_node = next_node->getNextNode();
        }
        return 0;
    }
}

Node *Graph::getNode(int id)
{
    if (this->first_node!=nullptr)
    {
        int achado=0;   // variavel que verifica se o indice ja foi achado
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if(next_node->getId()==id)
                return next_node;
            next_node = next_node->getNextNode();
        }
        return nullptr;
    }

}


//Function that prints a set of edges belongs breadth tree
Graph* Graph::questaoA(int id)
{
    Graph *graphAnswer = new Graph(order,directed,weighted_edge,weighted_node);
    questaoAaux(id,graphAnswer);
    graphAnswer->imprimir();
    imprimir();
}
Graph* Graph::questaoAaux(int id,Graph *graphAnswer)
{

    /*
        Node *adicionar=getNode(id);
        Edge *proximo=adicionar->getFirstEdge();
        graphAnswer->addNode(adicionar);

    */if(!graphAnswer->searchNode(id))
    {

        Node *adicionar=getNode(id);
        Edge *proximo=adicionar->getFirstEdge();
        graphAnswer->addNode(adicionar);
        while(proximo!=nullptr)
        {
            questaoAaux(proximo->getTargetId(),graphAnswer);
            proximo=proximo->getNextEdge();
        }
    }

}


void Graph::breadthFirstSearch(ofstream &output_file)
{
    Node *n = this->first_node;
    list<int> fila;
    fila.push_front(n->getId());
    while(fila.size()>0){

        n = this->getNode(fila.front());
        fila.pop_front();
        if(n->visitado == 0){
            cout << n->getId();
            output_file << n->getId();
            n->visitado = 1;
            Edge *e = n->getFirstEdge();
            while(e != nullptr){
                Node* target = getNode(e->getTargetId());
                if(target->visitado == 0){
                    fila.push_front(target->getId());
                }
                e = e->getNextEdge();
            }
        }
    }
}



float Graph::floydMarshall(int idSource, int idTarget)
{

}



float Graph::dijkstra(int idSource, int idTarget)
{

}

//function that prints a topological sorting
void Graph::topologicalSorting()
{
    cout << endl;
    cout << "S = {";
    for(int i = 0; i < this->getOrder(); i++){
        Node *next_node = this->first_node;
        while(next_node != nullptr){
            if(next_node->getInDegree() == 0){
                cout << next_node->getId();
                next_node->decrementInDegree();
                Edge *next_edge = next_node->getFirstEdge();
                while(next_edge != nullptr){
                    Node* target = getNode(next_edge->getTargetId());
                    target->decrementInDegree();
                    next_edge = next_edge->getNextEdge();
                }
            }

            next_node = next_node->next_node;
        }
    }
    cout << "}";
}
void breadthFirstSearch(ofstream& output_file)
{

}
Graph* getVertexInduced(int* listIdNodes)
{

}

Graph* agmKuskal()
{

}
Graph* agmPrim()
{

}
