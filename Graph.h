/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include "Edge.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;

class Graph{

    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;
        Edge* first_edge;

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        Node* getFirstNode();
        Node* getLastNode();
        Edge* getFirstEdge();
        //Other methods
        void insertNode(int id);
        void insertEdge(int id, int target_id, float weight, int id_edge);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        Edge* getEdge(int Source, int target);
        void setFirstEdge(Edge *e);

        //methods phase1
        void topologicalSorting();
        void breadthFirstSearch(ofstream& output_file);
        Graph* getVertexInduced(int* listIdNodes);
        Graph* questaoA(int id);
        Graph* agmKuskal();
        Graph* agmPrim();
        float floydMarshall(int idSource, int idTarget);
        float dijkstra(int idSource, int idTarget);

        //methods phase1
        float greed();
        float greedRandom();
        float greedRactiveRandom();
        void imprimir();

    private:
        void dijkstraAux(int nos[],int tamanho,int remocao);
        Graph* questaoAaux(int id,Graph *graphAnswer);
        void addNode(Node *Id);
        //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED
