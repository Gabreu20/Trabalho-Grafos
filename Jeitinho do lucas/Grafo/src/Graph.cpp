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
#include <limits>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset

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
    this->first_edge = nullptr;
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

Edge *Graph::getFirstEdge()
{
    return this->first_edge;
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

void Graph::setFirstEdge(Edge *e)
{
    this->first_edge = e;
}

void Graph::addNode(Node *Id)//adiciona a um grafo a copia de um no, com todoas as suas arestas incluidas
{

    //a copia é declarada
    Node *novoNo = new Node(Id->getId());

    //copia recebe os atributos copiados
    novoNo->last_edge=Id->last_edge;
    novoNo->first_edge=Id->first_edge;
    novoNo->in_degree=Id->in_degree;
    novoNo->out_degree=Id->out_degree;
    novoNo->weight=Id->weight;
    novoNo->next_node=nullptr;

    //adicionada ao grafo
    if (this->first_node==nullptr)
    {
        this->first_node= novoNo;
        this->last_node= novoNo;
    }
    else
    {

        Node *aux=last_node;
        aux->setNextNode(novoNo);
        last_node=novoNo;
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

void Graph::insertEdge(int id, int target_id, float weight, int id_edge)
{
    if(directed == 0)
    {
        if (this->first_node!=nullptr)
        {
            int achado=0;   // variavel que verifica se o indice ja foi achado

            Node *next_node = this->first_node;
            while (next_node != nullptr && achado==0 )
            {
                if(next_node->getId()==id)
                {
                    Node *aux = getNode(target_id);
                    aux->insertEdge(target_id,id,weight,id_edge);
                    //addciona edge
                    this->number_edges++;
                    next_node->insertEdge(id,target_id,weight, id_edge);
                    next_node->incrementOutDegree();
                    Node* target = getNode(target_id);
                    target->incrementInDegree();
                    achado=1;
                }
                next_node = next_node->getNextNode();
            }
        }
    }
    else if(directed == 1)
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
                    this->number_edges++;
                    next_node->insertEdge(id,target_id,weight, id_edge);
                    next_node->incrementOutDegree();
                    Node* target = getNode(target_id);
                    target->incrementInDegree();
                    achado=1;
                }
                next_node = next_node->getNextNode();
            }
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
Edge *Graph::getEdge(int Source, int target)
{
    Node *n = this->getFirstNode();
    while(n != nullptr)
    {
        Edge *e = n->getFirstEdge();
        while(e != nullptr)
        {
            if(e->getSource() == Source && e->getTargetId() == target)
                return e;
            e = e->getNextEdge();
        }
        n = n->next_node;
    }
    return nullptr;
}


///QUESTAO A----------------------------------------------------------------------------------------------------------------------------------------------------------------------
Graph* Graph::questaoA(int id)
{
    //a questao A foi feita de forma recursiva utilizando da busca em profundidade,todos os nos que podem ser acessados a partir do no de entrada
    //são adicionados ao grafo de retorno
    Graph *graphAnswer = new Graph(order,directed,weighted_edge,weighted_node);
    questaoAaux(id,graphAnswer);
    return graphAnswer;
}

//função auxiliar para realizar a busca em profundidade
Graph* Graph::questaoAaux(int id,Graph *graphAnswer)
{
    if(!graphAnswer->searchNode(id))
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
///QUESTAO B-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//O fechoo transitivo indireto é armazenado em um vetor essa função existe para que n seja inserido o mesmo no duas vezes no feixo
bool Graph::contemVetor(int vetor[],int tamanho,int valor)
{
    for(int i=0; i<tamanho; i++)
    {
        if(valor==vetor[i])
            return false;
    }
    return true;
}
Graph* Graph::questaoB(int id)
{
    int vertices[order];    //vetor que armazena o fecho
    int unidades = 1;       // quantidade de elemento no fecho ele inia com pois é o proprio valor alvo
    vertices[0]=id;

    //loop principal busca na lista de fechos nos que apontam pros pertecentes da lista quando o valor de i alcança o numero de unidades o fecho esta completo
    for(int i=0; i<unidades; i++)
    {
        questaoBaux(vertices[i],vertices,&unidades);
    }

    //grafo de retorno
    Graph *retorno=new Graph(order,directed,weighted_edge,weighted_node);

    //insere os nos no novo grafo
    for(int i=0; i<unidades; i++)
        retorno->insertNode(vertices[i]);


    //loop que garante que somente as arestas apontando pra menbros do fecho são adicionados
    for(int i=0; i<unidades; i++)
    {
        Node *next_node=getNode(vertices[i]);



        Edge *next_edge=next_node->getFirstEdge();


        while(next_edge!=nullptr)
        {

            for(int j=0; j<unidades; j++)
            {

                if(vertices[j]==next_edge->getTargetId())
                {

                    retorno->insertEdge(vertices[i],next_edge->getTargetId(),next_edge->getWeight(),0);
                }
            }

            next_edge=next_edge->getNextEdge();
        }
    }
    return retorno;
}

//função aux quefaz verificações para decidir se o no entra ou nao no fecho
void Graph::questaoBaux(int id,int vertices[],int *unidades)
{
    Node *next_node=first_node;
    Edge *next_edge=next_node->getFirstEdge();


    for(int i=0; i<order; i++)
    {
        while(next_edge!=nullptr)
        {
            if(next_edge->getTargetId()==id && contemVetor(vertices,*unidades,next_node->getId()))
            {

                vertices[*unidades]=next_node->getId();

                *unidades=*unidades+1;
            }
            next_edge=next_edge->getNextEdge();
        }
        if(i!=order-1)
        {
            next_node=next_node->getNextNode();
            next_edge=next_node->getFirstEdge();
        }
    }
}

///FIM QUESTAO A E B-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Graph::breadthFirstSearch(ofstream &output_file, int id)
{
    Node *n = this->getNode(id);
    list<int> fila;
    fila.push_back(n->getId());
    cout << "Caminhamento em Largura: {";
    while(!fila.empty())
    {

        n = this->getNode(fila.front());
        fila.pop_front();
        if(n->visitado == 0)
        {
            cout << n->getId() << " ";
            output_file << n->getId();
            n->visitado = 1;
            Edge *e = n->getFirstEdge();
            while(e != nullptr)
            {
                Node* target = getNode(e->getTargetId());
                if(target->visitado == 0)
                {
                    fila.push_back(target->getId());
                }
                e = e->getNextEdge();
            }
        }
    }
    cout << "}";
    cout << endl;
}
///QUESTAO C-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//função apenas remove um valor de um aray
void Graph::dijkstraAux(int nos[],int tamanho,int remocao)
{
    for(int i=remocao; i<tamanho; i++)
    {
        nos[i]=nos[i+1];
    }
}


float Graph::dijkstra(int idSource, int idTarget)
{
    int tamanho=order;
    int nos[order]; //lista dos nos n untilizados da onde um no é removido por itereação
    float menorCaminho[order];  //vetor que guarda a informação dos menores caminhos

    for(int i=0; i<order; i++)
    {
        menorCaminho[i]=numeric_limits<float>::infinity();  //inicia todos os valores do vetor como infinito
    }

    for(int i=0; i<tamanho; i++)
    {
        nos[i]=i;   //adiciona todos os nos na lista de remoções
    }

    menorCaminho[idSource]=0;   //a distancia de um no até ele mesmo é sempre 0
    dijkstraAux(nos,tamanho,idSource);
    tamanho--;
    Node *next_node=getNode(idSource);
    Edge *next_edge=next_node->getFirstEdge();

    //inicia os valores com a distancia acecivel do no inicial
    while(next_edge!=nullptr)
    {
        menorCaminho[next_edge->getTargetId()]=next_edge->getWeight();
        next_edge=next_edge->getNextEdge();
    }

    int Existe=0;
    //loop principal executa até que todos os nos da lista de nos tenham cido removido
    while(tamanho!=0)
    {
        int j=0;
        for(int i=0; i<tamanho; i++)
        {
            //certifica-se de que ta pegando a menor distancia detre as disponiveis
            if(menorCaminho[j]>menorCaminho[i])
            {
                for(int p=0; p<tamanho; p++)
                {
                    if(nos[p]==i+1)
                    {
                        Existe = 1;
                        break;
                    }

                }
                if(Existe==1)
                    j=i;
                Existe = 0;
            }
            dijkstraAux(nos,tamanho,j);
            tamanho--;

            Node *next_node=getNode(nos[j]);
            Edge *next_edge=next_node->getFirstEdge();

            //compara distancia entre os caminhos pra decidir qual opção de caminho é melhor
            while(next_edge!=nullptr)
            {
                if(menorCaminho[next_edge->getTargetId()]>next_edge->getWeight()+menorCaminho[nos[j]])
                {
                    menorCaminho[next_edge->getTargetId()]=next_edge->getWeight()+menorCaminho[nos[j]];
                }

                next_edge=next_edge->getNextEdge();
            }

        }
        if(tamanho==1)
        {
            return menorCaminho[idTarget];  //retorna o resultado pra no pedido
        }
    }
    return -1;  // retorna -1 em caso de algum erro no loop
}
///FIM QUESTAO C-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

///QUESTAO D-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float Graph::floydMarshall(int idSource, int idTarget)
{

    float distancias[order][order]; //matris com a distancia pra todos os nos
    for(int i=0; i<order; i++)
    {
        for(int j=0; j<order; j++)
        {
            distancias[i][j]=numeric_limits<float>::infinity(); //inicia todos os valores como infinito
        }
    }
    for(int i=0; i<order; i++)
    {
        distancias[i][i]=0;     //inicia a diagonal principal como 0
    }

    Node *next_node=first_node;
    Edge *next_edge=next_node->getFirstEdge();

    //inicia os valores inicias pro loop principal
    for(int i=0; i<order; i++)
    {
        for(int j=0; next_edge!=nullptr; j++)
        {
            distancias[next_node->getId()][next_edge->getTargetId()]=next_edge->getWeight();
            next_edge=next_edge->getNextEdge();
        }
        if(i!=order-1)
        {
            next_node=next_node->getNextNode();
            next_edge=next_node->getFirstEdge();
        }
    }

    //verifica todas as pocibilidades de caminho e acha a menor distancia de cada um dos nos até qualquer outro no
    for(int k=0; k<order; k++)
    {
        for(int i=0; i<order; i++)
        {

            for(int j=0; j<order; j++)
            {
                if(distancias[i][j]>distancias[i][k]+distancias[k][j])
                {
                    distancias[i][j]=distancias[i][k]+distancias[k][j];

                }

            }
        }
    }

    //retorna a distancia pedida
    return distancias[idSource][idTarget];

}
///FIM QUESTAO D-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//function that prints a topological sorting
void Graph::topologicalSorting(bool dir)
{
    if(dir)
    {
        cout << endl;
        cout << "S = {";
        for(int i = 0; i < this->getOrder(); i++)
        {
            Node *next_node = this->first_node;
            while(next_node != nullptr)
            {
                if(next_node->getInDegree() == 0)
                {
                    cout << next_node->getId();
                    next_node->decrementInDegree();
                    Edge *next_edge = next_node->getFirstEdge();
                    while(next_edge != nullptr)
                    {
                        Node* target = getNode(next_edge->getTargetId());
                        target->decrementInDegree();
                        next_edge = next_edge->getNextEdge();
                    }
                }

                next_node = next_node->next_node;
            }
        }
        cout << "}" << endl;
    }
    else{
        cout << "O grafo nao e direcionado!" << endl;
    }

}

Graph* getVertexInduced(int* listIdNodes)
{

}

Graph* Graph::agmKuskal(int id)
{
    vector<int> arestas;
    vector<int> nodes;

    Edge *edges[this->getNumberEdges()];

    Node *n = this->getFirstNode();
    int i = 0;
    while(n != nullptr)
    {
        Edge *e = n->getFirstEdge();
        while(e != nullptr)
        {
            arestas.push_back(e->getWeight());
            edges[i] = e;
            e = e->getNextEdge();
            i++;
        }
        n = n->next_node;
    }
    sort(arestas.begin(), arestas.end());

    for(int i = 0; i < number_edges; i++)
    {
        for(int j = 0; j < number_edges; j++)
        {
            if(edges[j]->getWeight() == arestas.at(0))
            {
                nodes.push_back(edges[j]->getSource());
                nodes.push_back(edges[j]->getTargetId());
                arestas.erase(arestas.begin());
                if(arestas.size() == 0)
                    arestas.push_back(0);
            }
        }
    }

    Graph *g = new Graph(order,directed,weighted_edge,weighted_node); //cria um grafo para ser a arvore

    for(int i=0; i<order; i++) //insere todos os nós no novo grafo
    {
        g->insertNode(i);
    }

    //Verifica Ciclo -INICIO
    g->getNode(id)->pai = id; //define o pai do primeiro vértice como ele mesmo

    int j = 1;
    cout << endl;
    for(int i = 0; i < nodes.size(); i = i + 2)
    {
        Node *pai = g->getNode(nodes.at(i));
        Node *filho = g->getNode(nodes.at(i+1));
        if(filho->pai == -1) //verifica se o filho ainda nao foi apadrinhado
        {
            filho->pai = pai->pai;
            g->insertEdge(pai->getId(),filho->getId(),0,j);
            cout << "ADD: |" << nodes.at(i) << "-" << nodes.at(i+1) << endl;
        }
        else
        {
            if(filho->pai != pai->pai) //verifica se são apadrinhados por diferentes vértices
            {
                filho->pai = pai->pai;
                g->insertEdge(pai->getId(),filho->getId(),0,j);
                cout << "ADD: |" << nodes.at(i) << "-" << nodes.at(i+1) << endl;
            }
        }
        j++;
    }
    //Verifica Ciclo -FINAL
    return g;
}

Graph* Graph::agmPrim(int id)
{
    vector<int> arestas;
    vector<int> nodes;

    Edge *edges[this->getNumberEdges()];

    Node *n = this->getNode(id);
    int i = 0;
    while(n != nullptr)
    {
        Edge *e = n->getFirstEdge();
        while(e != nullptr)
        {
            arestas.push_back(e->getWeight());
            edges[i] = e;
            e = e->getNextEdge();
            i++;
        }
        n = n->next_node;
    }
    sort(arestas.begin(), arestas.end());

    for(int i = 0; i < number_edges; i++)
    {
        for(int j = 0; j < number_edges; j++)
        {
            if(edges[j]->getWeight() == arestas.at(0))
            {
                nodes.push_back(edges[j]->getSource());
                nodes.push_back(edges[j]->getTargetId());
                arestas.erase(arestas.begin());
                if(arestas.size() == 0)
                    arestas.push_back(0);
            }
        }
    }

    Graph *g = new Graph(order,directed,weighted_edge,weighted_node);

    for(int i=0; i<order; i++)
    {
        g->insertNode(i);
    }

    //Verifica Ciclo -INICIO
    g->getFirstNode()->pai = g->getFirstNode()->getId();
    g->getFirstNode()->agmVisit = 1;

    cout << endl;
    for(int j = 0; j < this->getNumberEdges(); j++)
    {
        for(int i = 0; i < nodes.size(); i = i + 2)
        {
            if(g->getNode(nodes.at(i))->agmVisit == 1)
            {
                Node *pai = g->getNode(nodes.at(i));
                Node *filho = g->getNode(nodes.at(i+1));
                if(filho->pai == -1)
                {
                    filho->pai = pai->pai;
                    g->getNode(nodes.at(i+1))->agmVisit = 1;
                    g->insertEdge(nodes.at(i), nodes.at(i+1), 0,0);
                    cout << "ADD: |" << nodes.at(i) << "-" << nodes.at(i+1) << endl;
                    break;
                }
                else
                {
                    if(filho->pai != pai->pai)
                    {
                        filho->pai = pai->pai;
                        g->getNode(nodes.at(i+1))->agmVisit = 1;
                        g->insertEdge(nodes.at(i), nodes.at(i+1), 0,0);
                        cout << "ADD: |" << nodes.at(i) << "-" << nodes.at(i+1) << endl;
                        break;
                    }
                }
            }
        }
    }
    //Verifica Ciclo -FINAL
    return g;
}

string Graph::Saida()
{
    string GraphTxt;
    if(directed==0)
    {
        GraphTxt=GraphTxt+"strict graph {"+'\n';


        Node *next_node=first_node;
        while(next_node!=nullptr)
        {
            Edge *next_edge=next_node->getFirstEdge();
            while(next_edge!=nullptr)
            {
                GraphTxt=GraphTxt + to_string(next_node->getId()) + "--" + to_string(next_edge->getTargetId()) + ";" +'\n';
                next_edge=next_edge->getNextEdge();
            }
            next_node=next_node->getNextNode();
        }

        GraphTxt=GraphTxt+'}';

        return GraphTxt;
    }

    if(directed==1)
    {
        GraphTxt=GraphTxt+"Digraph saida {"+'\n';


        Node *next_node=first_node;
        while(next_node!=nullptr)
        {
            Edge *next_edge=next_node->getFirstEdge();
            while(next_edge!=nullptr)
            {
                GraphTxt=GraphTxt + to_string(next_node->getId()) + "->" + to_string(next_edge->getTargetId()) + ";" +'\n';
                next_edge=next_edge->getNextEdge();
            }
            next_node=next_node->getNextNode();
        }

        GraphTxt=GraphTxt+'}';

         return  GraphTxt;
    }
}
