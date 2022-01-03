/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED



using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int Source;
        int target_id;
        Edge* next_edge;
        float weight;

    public:
        int id;
        // Constructor
        Edge(int target_id, int Id);
        // Destructor
        ~Edge();
        // Getters
        int getTargetId();
        Edge* getNextEdge();
        float getWeight();
        int getSource();
        // Setters
        void setNextEdge(Edge* edge);
        void setWeight(float weight);
        void setSource(int source);
        void setId(int id);
};

#endif // EDGE_H_INCLUDED
