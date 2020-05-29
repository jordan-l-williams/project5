// Digraph.hpp
//
// ICS 46 Spring 2020
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <string>







// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    
    bool  mytest(int numberOfVertexs,std::vector<int> array ,int iterator ) const;
    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;

    struct vertexArray{
        int vertex;
        bool visited;
    };
    bool DFT()const;

    bool DFTr(int x ,std::map<int , bool> myArray )const;

    

private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.

    std::map< int, DigraphVertex<VertexInfo, EdgeInfo> > list;    
    



    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};


// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    list = d.list;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    list.swap(d.list);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    list = d.list;
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    this->list.swap(d.list);
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> temp;

    for(auto iterator = list.begin(); iterator != list.end(); iterator++){
        temp.push_back(iterator->first);
    }
    return temp;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> temp;

    for(auto iteratorList = list.begin(); iteratorList != list.end(); iteratorList++ ){
         for(auto iteratorEdge = iteratorList->second.edges.begin(); iteratorEdge != iteratorList->second.edges.end() ; iteratorEdge++){
            std::pair<int , int> myPair;
            myPair.first = iteratorEdge->fromVertex;
            myPair.second = iteratorEdge->toVertex;
            temp.push_back(myPair);
         }
    }
    return temp;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    if(list.find(vertex) == list.end()){
        //did not find key
        throw DigraphException("A key already exists");
    }
    else{
        std::vector<std::pair<int, int>> temp;
        for(auto iterater = list.at(vertex).edges.begin(); iterater != list.at(vertex).edges.end(); iterater++  ){
            std::pair<int , int> myPair;
            myPair.first = iterater->fromVertex;
            myPair.second = iterater->toVertex;
            temp.push_back(myPair);
        }
        return temp;
    }
   
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    if(list.find(vertex) == list.end()){
        //did not find key
        throw DigraphException("A key already exists");
    }
    else{
        return list.at(vertex).vinfo;
    }
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    if(list.find(fromVertex) == list.end()){
        //did not find key
        throw DigraphException("A key already exists");
    }
    else{

        for(auto interater = list.at(fromVertex).edges.begin(); interater != list.at(fromVertex).edges.end(); interater++){
            if(interater->fromVertex == fromVertex && interater->toVertex == toVertex){
                return interater->einfo;
            }
        }

        throw DigraphException("A key already exists");
    }    
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    if(list.find(vertex) == list.end()){
        //did not find key
        list[vertex].vinfo = vinfo;
    }
    else{
        throw DigraphException("A key already exists") ;
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    if(list.find(fromVertex) == list.end()){
        //Did not find key
        throw DigraphException("did not find the key");
    }   
    else{

        for(auto interate = list[fromVertex].edges.begin(); interate != list[fromVertex].edges.end(); interate++){
            if(interate->fromVertex == fromVertex && interate->toVertex == toVertex){
                throw DigraphException("the Edge info was already inserted into the graph");
                return;
            }
        }
        DigraphEdge<EdgeInfo>  temp; //= new DigraphEdge<EdgeInfo>();
        temp.einfo = einfo;
        temp.fromVertex = fromVertex;
        temp.toVertex = toVertex;

        list[fromVertex].edges.push_back(temp);
      
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    auto iter = list.find(vertex);
    if(iter == list.end()){
        //Did not find key
        throw DigraphException("did not find the key");
    }   
    else{
        list.erase(iter);     
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    auto iter = list.find(fromVertex);
    if(iter == list.end()){
        //Did not find key
        throw DigraphException("did not find the key");
    }   
    else{
        for(auto iterEdge = iter->second.edges.begin(); iterEdge != iter->second.edges.end(); iterEdge++){
            if(iterEdge->fromVertex == fromVertex && iterEdge->toVertex == toVertex){
                iter->second.edges.erase(iterEdge);
                return;
            }
        }
        throw DigraphException("did not find the key");        
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return list.size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    int count = 0;
    for(auto iteratorList = list.begin(); iteratorList != list.end(); iteratorList++ ){
        for(auto iteratorEdge = iteratorList->second.edges.begin(); iteratorEdge != iteratorList->second.edges.end() ; iteratorEdge++){
            count += 1;
        }
    }

    return count;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    int count = 0;
    if(list.find(vertex) == list.end()){
        //Did not find key
        throw DigraphException("did not find the key");
    }   
    else{
        
        for(auto iterate = list.begin(); iterate != list.end(); iterate++){
            count+= iterate->second.edges.size();
        }
      
    }
    return count;
    
}

// template <typename VertexInfo, typename EdgeInfo> 
// bool  Digraph<VertexInfo, EdgeInfo>::mytest(int numberOfVertexs,std::vector<int> array ,int iterator ) const{
//     if(array.size() == 0){
//         array.push_back(iterator)
//     }
    
//     for(int x = 0; x < array.size(); x++){
//         if(iterator == array.at(x)){
//             break;
//         }
//         if(x == array.size()-1){
//             array.push_back(iterator);
//         }
//     }

//     for(auto iterate2 = list.begin(); iterate2 != list.end(); iterate2++){
//         mytest(numberOfVertexs , array , iterate->second.ed)
//     }
    

//     return true;
// }
template <typename VertexInfo, typename EdgeInfo> 
bool Digraph<VertexInfo, EdgeInfo>::DFTr(int x ,std::map<int , bool> myArray )const{
    myArray.at(x) = true;

    bool result = false;
    int count = 0;
    for(auto i = myArray.begin(); i != myArray.end(); i++){
        if(i->second == true){
            count +=1;
        }
    }

    if(count == myArray.size()){
        return true;
    }

  //  auto temp = list.find(myArray.at(x).vertex);

    // for(auto i = temp.second.edges.begin(); i != temp.second.edges.end(); i++ ){

    auto iter = list.find(x);

        for(auto iterEdge = iter->second.edges.begin(); iterEdge != iter->second.edges.end(); iterEdge++){
            if(myArray.at(iterEdge->toVertex) == false){
               result = DFTr(iterEdge->toVertex , myArray);

               if(result == true)
                    break;
            }
        }

    // }
    return result;
}

template <typename VertexInfo, typename EdgeInfo> 
bool Digraph<VertexInfo, EdgeInfo>::DFT()const{
    //vertexArray
    bool result = false;
    std::map<int , bool> myArray;
    for(auto iter = list.begin() ;iter != list.end(); iter++ ){
        myArray[iter->first] = false;
    }

    for(auto i = myArray.begin(); i != myArray.end(); i++){
        if(i->second == false){
            result = DFTr(i->first , myArray);
            if(result == false){
                return false;
            }
        }

    }

    return result;
};

 



template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    if(list.size() < 1){
        return false;
    }
 
    bool isConnected =  Digraph<VertexInfo, EdgeInfo>::DFT ( );


     

    
    return isConnected;
}






template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    return std::map<int, int>{};
}



#endif // DIGRAPH_HPP

