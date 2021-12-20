#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"
#include <limits>
using namespace std;

Graph* leitura(ifstream& input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    int edge_id = 1;
    if(!graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }
        while(input_file >> idNodeSource >> idNodeTarget)
        {
            graph->insertEdge(idNodeSource, idNodeTarget, 0, edge_id);
            edge_id++;
        }

    }
    else if(graph->getWeightedEdge() && !graph->getWeightedNode() )
    {

        float edgeWeight;
        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }

        while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight, edge_id);
            edge_id++;
        }

    }
    else if(graph->getWeightedNode() && !graph->getWeightedEdge())
    {

        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }
        float nodeSourceWeight, nodeTargetWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 0, edge_id);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
            edge_id++;
        }

    }
    else if(graph->getWeightedNode() && graph->getWeightedEdge())
    {
        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight, edge_id);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
            edge_id++;
        }

    }

    graph->setFirstEdge(graph->getFirstNode()->getFirstEdge());

    return graph;
}

Graph* leituraInstancia(ifstream& input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;

    //Pegando a ordem do grafo
    input_file >> order >> numEdges;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //adciona todos os indicies
    for(int i=0; i<order; i++)
    {
        graph->insertNode(i);
    }


    //Leitura de arquivo
    while(input_file >> idNodeSource >> idNodeTarget)
    {

        graph->insertEdge(idNodeSource, idNodeTarget, 0, graph->getNumberEdges());

    }

    graph->setFirstEdge(graph->getFirstNode()->getFirstEdge());

    return graph;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Subgrafo vertice-induzido pelo fecho transitivo direto deste vértice." << endl;
    cout << "[2] Caminho Mínimo entre dois vértices - Dijkstra" << endl;
    cout << "[3] Caminho Mínimo entre dois vértices - Floyd" << endl;
    cout << "[4] Arvore Geradora Mínima de Prim" << endl;
    cout << "[5] Arvore Geradora Mínima de Kruskal" << endl;
    cout << "[6] Imprimir caminhamento em largura" << endl;
    cout << "[7] Imprimir ordenacao topológica" << endl;
    cout << "[8] questao b" << endl;
    cout << "[9] Algoritmo Guloso Randomizado " << endl;
    cout << "[10] Imprimir Grafo"<< endl;
    cout << "[11] Algoritmo Guloso" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Graph* graph, ofstream& output_file)
{

    switch (selecao)
    {

    //Subgrafo induzido por um conjunto de vértices X;
    case 1:
    {
        int no;
        cout << "insira o valor para o subgrafo vértice-induzido pelo fecho transitivo direto deste vértice: ";
        cin >> no;
        graph->questaoA(no);
        break;
    }
    //Caminho mínimo entre dois vértices usando Dijkstra;
    case 2:
    {
        int noSaida,noChegada;
        cout << "insira o id de saida: ";
        cin >> noSaida;
        cout << "insira o id de chegada: ";
        cin >> noChegada;
        cout << endl << endl;
        cout << "tamanho do caminho usando o algoritimo de Dijkstra: "<< graph->dijkstra(noSaida,noChegada) << endl;
        break;
    }

    //Caminho mínimo entre dois vértices usando Floyd;
    case 3:
    {
        int noSaida,noChegada;
        cout << "insira o id de saida: ";
        cin >> noSaida;
        cout << "insira o id de chegada: ";
        cin >> noChegada;
        cout << endl << endl;
        cout << "tamanho do caminho usando o algoritimo de Floyd Marshall: "<< graph->floydMarshall(noSaida,noChegada) << endl;
        break;
    }

    //AGM - Kruscal;
    case 5:
    {
        cout << "Insira o Id do Vertice inicial" << endl;
        int ID;
        cin >> ID;
        Graph* g;
        g = graph->agmKuskal(ID);
        g->imprimir();
        break;
    }

    //AGM Prim;
    case 4:
    {
        cout << "Insira o Id do Vertice inicial" << endl;
        int ID;
        cin >> ID;
        Graph* g;
        g = graph->agmPrim(ID);
        g->imprimir();
        break;
    }

    //Busca em largura;
    case 6:
    {
        cout << "Insira o Id do Vertice inicial" << endl;
        int ID;
        cin >> ID;
        graph->breadthFirstSearch(output_file, ID);
        break;
    }
    //Ordenação Topologica;
    case 7:
    {
        Graph* aux = graph;
        aux->topologicalSorting();
        break;
    }
    case 8:{
            graph->questaoB(4);
            graph->imprimir();
        break;
    }
    case 10:
    {
        graph->imprimir();
        break;
    }
    default:
    {
        cout << " Error!!! invalid option!!" << endl;
    }

    }
}

int mainMenu(ofstream& output_file, Graph* graph)
{

    int selecao = 1;

    while(selecao != 0)
    {
        system("clear");
        selecao = menu();

        if(output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;

    }

    return 0;
}



int main()
{
    //int argc, char const *argv[]
    int argc=6;
    char *argv[]= {"Bom","grafo_10.txt","output","1","1","0"};

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;

    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if(input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);



    Graph* graph;

    if(input_file.is_open())
    {

        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(output_file, graph);



    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}
