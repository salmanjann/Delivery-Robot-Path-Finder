#pragma once
#ifndef DOUBLYLINKEDLIST
#define DOUBLYLINKEDLIST

#include <iostream>
using namespace std;

class DLL
{
    struct dNode
    {
        string VName;
        int EdgeWeight;
        dNode *next;
        dNode *prev;
        dNode(string _VName, int _EdgeWeight)
        {
            VName = _VName;
            next = NULL;
            prev = NULL;
            EdgeWeight = _EdgeWeight;
        }
    };
    dNode *head;
    // PRIVATE HELPER FUNCTIONS
    bool searchVName(string _VName)
    {
        dNode *current = head; // Initialize current
        while (current != NULL)
        {
            if (current->VName == _VName)
                return true;
            current = current->next;
        }
        return false;
    }

public:
    DLL()
    {
        head = NULL;
    }
    bool isEmpty()
    {
        if (head == NULL)
            return true;
        return false;
    }
    void insert(string _VName, int _EdgeWeight)
    {
        if (searchVName(_VName))
        {
            cout << "An Edge Already Exist :( " << endl;
            return;
        }
        else
        {
            dNode *newbie = new dNode(_VName, _EdgeWeight);

            if (isEmpty())
            {
                head = newbie;
                return;
            }
            dNode *ptr;
            for (ptr = head; ptr->next != NULL; ptr = ptr->next)
                ;
            newbie->prev = ptr;
            ptr->next = newbie;
        }
    }
    void deleteEdge(string vertex)
    {
        if (isEmpty())
        {
            return;
        }
        dNode *temp;
        int index = 1;
        if (head->VName == vertex)
        {
            temp = head;
            if (head->next != NULL)
            {
                head->next->prev = NULL;
                head = head->next;
            }
            else
                head = NULL;

            delete temp;
            return;
        }
        dNode *ptr = head;
        while (ptr && ptr->VName != vertex)
        {
            ptr = ptr->next;
        }
        if (!ptr)
        {
            return;
        }
        // tail node
        else if (ptr->next == NULL)
        {
            temp = ptr;
            ptr->prev->next = NULL;
            delete temp;
            return;
        }
        else if (ptr)
        {
            temp = ptr;
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            delete temp;
            return;
        }
    }
    int EdgeWeight(string V)
    {
        int EW =0;
        dNode* ptr = head;
        while(ptr != NULL)
        {
            if(ptr->VName == V)
            {
                EW = ptr->EdgeWeight;
                break;
            }
            else
                ptr = ptr->next;
        }
        return EW;
    }
    bool isEdgeExist(string V)
    {
        dNode* ptr = head;
        while(ptr != NULL)
        {
            if(ptr->VName == V)
                return true;
            else
                ptr = ptr->next;
        }
        return false;
    }
    void display()
    {
        if (isEmpty())
            return;
        else
        {
            for (dNode *ptr = head; ptr != NULL; ptr = ptr->next)
                cout<<ptr->VName <<","<<ptr->EdgeWeight<< " -> ";
            cout << "NULL";
        }
    }
};
#endif