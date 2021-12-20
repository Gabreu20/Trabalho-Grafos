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
            graph->insertEdge(idNodeSource, idNodeTarget, 1, edge_id);
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

            graph->insertEdge(idNodeSource, idNodeTarget, 1, edge_id);
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

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Subgrafo vertice-induzido pelo fecho transitivo direto deste vertice." << endl;
    cout << "[2] Subgrafo vertice-induzido pelo fecho transitivo indireto deste vertice." << endl;
    cout << "[3] Caminho Minimo entre dois vertices - Dijkstra" << endl;
    cout << "[4] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[5] Arvore Geradora Minima de Prim" << endl;
    cout << "[6] Arvore Geradora Minima de Kruskal" << endl;
    cout << "[7] Imprimir caminhamento em largura" << endl;
    cout << "[8] Imprimir ordenacao topologica" << endl;
    cout << "[9] Imprimir Grafo"<< endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

int selecionar(int selecao, Graph* graph, string output)
{
    ofstream output_file;
    output_file.open(output, ios::out | ios::trunc);
    switch (selecao)
    {
    //sai do programa
    case 0:
    {
        output_file.close();
        return 0;
    }
    //o subgrafo vértice-induzido pelo fecho transitivo direto deste vértice.
    case 1:
    {
        int no;
        cout << "insira o valor para o subgrafo vertice-induzido pelo fecho transitivo direto deste vertice: ";
        cin >> no;
        Graph *saida;
        saida=graph->questaoA(no);
        output_file << saida->Saida();

        cout << endl<< "O grafo vertice induzido desejado esta no local: " << output << endl<< endl;

        break;
    }
    //o subgrafo vértice-induzido pelo fecho transitivo indireto deste vértice.
    case 2:
    {
        int no;
        cout << "insira o valor para o subgrafo vertice-induzido pelo fecho transitivo indireto direto deste vertice: ";
        cin >> no;
        Graph *saida;
        saida=graph->questaoB(no);

        output_file << saida->Saida();
        cout << endl<< "O grafo vertice induzido desejado esta no local: " << output << endl << endl;
        break;
    }

    //Caminho mínimo entre dois vértices usando Dijkstra.
    case 3:
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
    //Caminho mínimo entre dois vértices usando Floyd.
    case 4:
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
    //AGM Prim;
    case 5:
    {
        Graph* g;
        g = graph->agmPrim(0);
        //g->imprimir();
        g->Saida();
        break;
    }
    //AGM - Kruscal;
    case 6:
    {
        Graph* g;
        g = graph->agmKuskal(0);
        //g->imprimir();
        g->Saida();
        break;
    }


    //Busca em largura;
    case 7:
    {
        cout << "Insira o Id do Vertice inicial" << endl;
        int ID;
        cin >> ID;
        graph->breadthFirstSearch(output_file, ID);
        break;
    }
    //Ordenação Topologica;
    case 8:
    {
        Graph* aux = graph;
        aux->topologicalSorting(graph->getDirected());
        break;
    }
    case 9:
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

int mainMenu(string output_file, Graph* graph)
{

    int selecao = 1;

    while(selecao != 0)
    {

        selecao = menu();

        system("clear");
        system("cls");
        selecionar(selecao, graph, output_file);


    }

    return 0;
}



int main()
{
    //int argc, char const *argv[]
    int argc=6;
    char *argv[]= {"Bom","grafo_10.txt","output.txt","1","1","0"};

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

    input_file.open(argv[1], ios::in);

    Graph* graph;

    if(input_file.is_open())
    {

        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(argv[2], graph);



    //Fechando arquivo de entrada
    input_file.close();

    return 0;
}
