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
        void insertNode(int id);//insere um vértice
        void insertEdge(int id, int target_id, float weight, int id_edge);//insere uma aresta
        void removeNode(int id);//remove um vértice
        bool searchNode(int id);//procura um vértice
        Node* getNode(int id);//retorna um vértice(id)
        Edge* getEdge(int Source, int target);//retorna uma aresta(id)
        void setFirstEdge(Edge *e);//define o primeiro Edge
        bool contemVetor(int vetor[],int tamanho,int valor);    // confere se um id esta num vetor

        //methods phase1
        void topologicalSorting(bool dir);//faz a ordenação topológica de um determinado grafo
        void breadthFirstSearch(ofstream& output_file, int id);//faz a busca em largura em um grafo
        Graph* getVertexInduced(int* listIdNodes);//função n foi utilizada
        Graph* questaoA(int id);//o subgrafo vértice-induzido pelo fecho transitivo direto deste vértice.
        Graph* questaoB(int id);//o subgrafo vértice-induzido pelo fecho transitivo indireto deste vértice.
        void questaoBaux(int id,int vertices[],int *unidades);
        Graph* agmKuskal(int id);//encontra a Agm usando Kruskal
        Graph* agmPrim(int id);//encontra a Agm usando Prim
        float floydMarshall(int idSource, int idTarget);//encontra o caminho mínimo entre 2 vértices
        float dijkstra(int idSource, int idTarget);//encontra o caminho mínimo entre 2 vértices

        //methods phase1
        float greed();
        float greedRandom();
        float greedRactiveRandom();
        void imprimir();//imprime um grafo
        string Saida();

    private:
        void dijkstraAux(int nos[],int tamanho,int remocao);
        Graph* questaoAaux(int id,Graph *graphAnswer);
        void addNode(Node *Id);
        //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED
