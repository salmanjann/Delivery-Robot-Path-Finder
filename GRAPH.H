#pragma once
#ifndef GRAPH
#define GRAPH
#include <iostream>
#include "DOUBLYLINKEDLIST.h"
using namespace std;

class Graph
{
    struct adjList {
        string VertexName;
        int  DeliveryTime;
        DLL* EdgeList;
        adjList* next;
        adjList* prev;
        adjList(string _VertexName,int _DeliveryTime) {
            VertexName = _VertexName;
            EdgeList = new DLL();
            next = NULL;
            prev = NULL;
            DeliveryTime =_DeliveryTime;
        }
    };
    adjList* start;

    //PRIVATE HELPER FUNCTIONS
    bool searchVertex(string vertex) {
        if (isEmpty())
            return false;
        adjList* current = start; // Initialize current
        while (current != NULL) {
            if (current->VertexName == vertex)
                return true;
            current = current->next;
        }
        return false;
    
    }
    void insertNewVertex(string _VertexName,int _DeliveryTime) {
        adjList* newVertex = new adjList(_VertexName,_DeliveryTime);

        if (isEmpty())
        {
            start = newVertex;
            return;
        }
        adjList* ptr;
        for (ptr = start; ptr->next != NULL; ptr = ptr->next)
            ;
        newVertex->prev = ptr;
        ptr->next = newVertex;
    }

    void pointToRequiredVertex(adjList*& ptr, string vertex) {
        if (isEmpty())
        {
            ptr = NULL;
            return;
        }
        else
        {
            ptr = start;
            while (ptr != NULL) {
                if (ptr->VertexName == vertex)
                    return;
                else
                    ptr = ptr->next;
            }
            ptr = NULL;
            return;
        }
    }

public:
    Graph()
    {
        start = NULL;
    }
    bool isEmpty() {
        if (start == NULL)
            return true;
        else
            return false;
    }
    void addVertex(string vertex,int _DeliveryTime) {
        if (searchVertex(vertex)) {
            cout << "Vertex Already Exist :( " << endl;
        }
        else {
            insertNewVertex(vertex,_DeliveryTime);
        }

        return;
    }
    void addEdge(string vertex1, string vertex2, int weight) {
        if (!searchVertex(vertex1))
            cout << vertex1 << " doesn't exist in the graph " << endl;
        else if (!searchVertex(vertex2))
            cout << vertex2 << " doesn't exist in the graph " << endl;
        else
        {
            adjList* ptr;
            pointToRequiredVertex(ptr,vertex1);
            if (ptr)
                ptr->EdgeList->insert(vertex2, weight);
            pointToRequiredVertex(ptr,vertex2);
            if(ptr)
                ptr->EdgeList->insert(vertex1, weight);


        }

        return;
    }
    // void deleteNode(string vertex) {
    //     if (isEmpty())
    //     {
    //         return ;
    //     }
    //     // first we'll delete any edge if that node is connected to
    //     adjList* ptrr = start;
    //     while (ptrr->next != NULL) {
    //         ptrr->EdgeList->deleteEdge(vertex);
    //         ptrr = ptrr->next;
    //     }

    //     adjList* temp;
    //     DLL* temp1;
    //     int index = 1;
    //     if (start->VertexName == vertex)
    //     {
    //         temp1 = start->EdgeList;
    //         temp = start;
    //         start->next->prev = NULL;
    //         start = start->next;
    //         delete temp;
    //         delete temp1;
    //         return ; 
    //     }
    //     adjList* ptr = start;
    //     while (ptr && ptr->VertexName != vertex)
    //     {
    //         ptr = ptr->next;
    //     }
    //     if (!ptr)
    //     {
    //         cout << "Value Not found" << endl;
    //         return;
    //     }
    //     // tail node
    //     else if (ptr->next == NULL)
    //     {
    //         temp1 = ptr->EdgeList;
    //         temp = ptr;
    //         ptr->prev->next = NULL;
    //         delete temp;
    //         delete temp1;
    //         return ;
    //     }
    //     else if (ptr)
    //     {
    //         temp1 = ptr->EdgeList;
    //         temp = ptr;
    //         ptr->prev->next = ptr->next;
    //         ptr->next->prev = ptr->prev;
    //         delete temp;
    //         delete temp1;
    //         return ;
    //     }
    // }
    // void deleteEdge(string from, string to) {
    //     adjList* ptr = start;
    //     while (ptr->next != NULL) {
    //         if (ptr->VertexName == from) {
    //             ptr->EdgeList->deleteEdge(to);
    //             return;
    //         }
    //         ptr = ptr->next;
    //     }
    // }

    // string printsingleLink(string city) {
    //     string result = "";
    //     if (!searchVertex(city)) {
    //         result = result + city + " doesn't exist in the Graph :( ";
    //         //cout << result<< endl;
    //         return result;
    //     }
    //     else {
    //         adjList* ptr;
    //         pointToRequiredVertex(ptr, city);
    //         result = result + city + ":";A
    //         cout << result
    //         string result2 = ptr->EdgeList->display();
    //         result = result + result2;
    //         return result;
    //     }

    // }
    int getDeliveryTime(string &Vertex)
    {
        int DTime = 0;
        adjList* ptr = start;
        while(ptr!= NULL)
        {
            if(ptr->VertexName == Vertex)
            {
                DTime = ptr->DeliveryTime;
                break;
            }
            else
                ptr = ptr->next;
        }
        return DTime;
    }
    int EdgeWeight(string& V1,string& V2)
    {
        adjList* ptr = start;
        while(ptr!= NULL)
        {
            if(ptr->VertexName == V1)
                break;
            else
                ptr = ptr->next;
        }
        return ptr->EdgeList->EdgeWeight(V2);
    }
    bool isEdgeExist(string& V1,string& V2)
    {
        adjList* ptr = start;
        while(ptr!= NULL)
        {
            if(ptr->VertexName == V1)
                break;
            else
                ptr = ptr->next;
        }
        return ptr->EdgeList->isEdgeExist(V2);
    }
    void printAdjacencyList()
    {
        if (isEmpty())
        {
            cout << "Empty graph " << endl;
            return;
        }
        else {
            adjList* ptr = start;
            while (ptr != NULL) {
                cout << ptr->VertexName << " : "<<
                ptr->DeliveryTime<<" ==> ";
                ptr->EdgeList->display();
                cout<<endl;
                ptr = ptr->next;
            }
            cout << "NULL\n";
        }
    }
};
#endif
