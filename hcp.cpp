#include "DOUBLYLINKEDLIST.h"
#include "GRAPH.H"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ProcessVertex(string v, string DTimes, Graph *&G)
{
    if (v == "h")
    {
        G->addVertex(v, 0);
        return;
    }
    int j = 0, index = 0;
    bool found = false;
    string vm = "", w = "";
    while (DTimes[j] != '\0')
    {
        if (DTimes[j] == v[index])
            vm += v[index++];
        if (vm == v)
            found = true;
        if (found)
        {
            if (DTimes[j] >= 47 && DTimes[j] <= 57)
                w += DTimes[j];
            if (DTimes[j] == ',')
                break;
        }
        j++;
    }
    G->addVertex(v, stoi(w));
}
void ProcessEdges(string EdgeList, string weights, Graph *&G)
{
    int start_pos = EdgeList.find("(");
    string from = "", to = "", weight = "";
    bool flag = false;
    int index = 0;
    while (start_pos != string::npos)
    {
        int end_pos = EdgeList.find(")", start_pos);
        if (end_pos != string::npos)
        {
            string substring = EdgeList.substr(start_pos, end_pos - start_pos + 1);
            // cout << substring << std::endl;
            int j = 0;
            flag = false;
            from = "", to = "", weight = "";
            while (substring[j] != '\0')
            {
                if (substring[j] == '(' || substring[j] == ')')
                {
                    j++;
                    continue;
                }
                else
                {
                    if (substring[j] == ',')
                    {
                        flag = true;
                        j++;
                        continue;
                    }
                    if (!flag)
                        from += substring[j];
                    else
                        to += substring[j];
                }
                j++;
            }
            while (weights[index] != '\0')
            {
                if (weights[index] == ',')
                {
                    index++;
                    break;
                }
                else
                    weight += weights[index];
                index++;
            }
            G->addEdge(from, to, stoi(weight));
        }
        start_pos = EdgeList.find("(", end_pos);
    }
}
void MakeGraphFromFile(string fileName, Graph *&G, int &V, string *&Vs, int &Time)
{
    bool startReading = false;
    string Vertices = "";
    string Edges = "";
    string edgeWeights = "";
    string DTimes = "";
    string TTime = "";
    int count = 0;
    fstream file(fileName);
    char c;
    if (!file)
        cout << "file not found" << endl;
    else
    {
        while (!file.eof())
        {
            file >> c;

            if (c == '{')
            {
                startReading = true;
                continue;
            }

            if (c == '}')
            {
                startReading = false;
                count++;
                continue;
            }
            if (startReading)
            {
                if (count == 0)
                    Vertices += c;
                else if (count == 1)
                    Edges += c;
                else if (count == 2)
                    edgeWeights += c;
                continue;
            }
            if (count == 3)
            {
                if (c == 'T' && DTimes[DTimes.length() - 1] != '(')
                {
                    count++;
                    TTime += c;
                    continue;
                }
                DTimes += c;
            }
            if (count == 4)
                TTime += c;
        }
    }
    string tt = "";
    TTime.pop_back();
    for (int i = 0; TTime[i] != '\0'; i++)
        if (TTime[i] >= 48 && TTime[i] <= 57)
            tt += TTime[i];

    Time = stoi(tt);

    for (int i = 0; Vertices[i] != '\0'; i++)
        if (Vertices[i] == ',')
            V++;
    V++;
    Vs = new string[V];
    int ind = 0;
    string v = "";
    for (int i = 0; Vertices[i] != '\0'; i++)
    {
        if (Vertices[i] == ',')
        {
            ProcessVertex(v, DTimes, G);
            if (v != "h")
                Vs[ind++] = v;
            v = "";
            continue;
        }
        else
        {
            v += Vertices[i];
        }
    }
    ProcessVertex(v, DTimes, G);
    Vs[ind++] = v;
    Vs[ind] = "#";
    
    ProcessEdges(Edges, edgeWeights, G);
    cout << endl;
    // G->printAdjacencyList();
}
string getNextVertex(string *&VertexList, string CurrentVertex, int &nVertices)
{
    if (CurrentVertex == "#")
        return VertexList[0];
    for (int i = 0; i < nVertices; i++)
    {
        if (VertexList[i] == CurrentVertex)
            return VertexList[i + 1];
    }
}
bool isExist(string *&Circuit, int &ptr)
{
    for (int i = 0; i < ptr; i++)
    {
        if (Circuit[ptr] == Circuit[i])
            return true;
    }
    return false;
}
int getCircuitTime(string *&Circuit, int &ptr, int &nVertices, Graph *&G)
{
    int CTime = 0;
    for (int i = 1; i <= ptr; i++)
    {
        if(Circuit[i] == "#")
            continue;
        CTime += G->getDeliveryTime(Circuit[i]);
        CTime += G->EdgeWeight(Circuit[i - 1], Circuit[i]);
    }
    return CTime;
}
void findHamiltonianCircuit(Graph *&G, int &nVertices, string *&VertexList, int &GivenTime)
{
    int CircuitTime = 0;
    bool isCircuitExist = false;
    int minTime = 99999;
    string *Circuit = new string[nVertices];
    Circuit[0] = "h";
    for (int i = 1; i < nVertices; i++)
        Circuit[i] = "#";
    int ptr = 1;
    while (true)
    {
        Circuit[ptr] = getNextVertex(VertexList, Circuit[ptr], nVertices);
        if ((ptr == 1) && Circuit[ptr] == "#")
            break;
        if (ptr == 1)
            CircuitTime = 0;
        if (Circuit[ptr] == "#")
        {
            ptr--;
            continue;
        }
        // checks if vertex already exist in Circuit, if yes, then get next vertex
        if (isExist(Circuit, ptr))
            continue;
        // else check if there is edge b/w currentVertex and previous vertex
        else
        {
            // if edge exist, then this is correct vertex and we can add vertex to new index
            if (G->isEdgeExist(Circuit[ptr - 1], Circuit[ptr]))
            {
                CircuitTime = getCircuitTime(Circuit, ptr, nVertices, G);
                if (CircuitTime > GivenTime)
                    continue;
                if (ptr + 1 < nVertices)
                    ptr++;
                // if it is last vertex, check if it has edge with first vertex of circuit
                if (ptr == nVertices - 1)
                {
                    if (G->isEdgeExist(Circuit[0], Circuit[ptr]))
                    {
                        CircuitTime += G->EdgeWeight(Circuit[0],Circuit[ptr]);
                        if (CircuitTime > GivenTime)
                            continue;
                        if(CircuitTime < minTime)
                            minTime = CircuitTime;
                        isCircuitExist = true;
                        for (int i = 0; i < nVertices; i++)
                            cout << Circuit[i] << "->";
                        cout <<"h"<< endl;
                    }
                }
            }
        }
    }
    if (!isCircuitExist)
        cout << "No Circuit Exist :(" << endl;
    else
        cout<<"Min Time is "<<minTime<<endl;
}
int main()
{
    const int NFILES = 4;
    const string FILENAME = "P2_test";
    const string FILEEXT = ".txt";
    // No of Vertices for each Graph
    int NVertex[NFILES];
    // Given Time for each graph
    int TIMES[NFILES];
    // Graphs
    Graph *Gs[NFILES];
    for (int i = 0; i < NFILES; i++)
    {
        Gs[i] = new Graph();
        NVertex[i] = 0;
    }
    // String array containing Vertices of each Graph
    string **Vertex = new string *[NFILES];
    for (int i = 0; i < NFILES; i++)
    {
        cout << "\nProcessing File No " << i + 1 << endl;
        MakeGraphFromFile(FILENAME + to_string(i+1) + FILEEXT, Gs[i], NVertex[i], Vertex[i], TIMES[i]);
        findHamiltonianCircuit(Gs[i], NVertex[i], Vertex[i], TIMES[i]);
    }

    return 0;
}