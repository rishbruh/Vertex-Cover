// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <set>
#include <utility>
#include <map>
#include <queue>
using namespace std;

class GraphPaths{

 private: 
    vector<pair<int,int>> edges;
    int vert_num;
    int src;
    int des;
    bool has_vertices;
    bool has_edges;
    vector<int> pred;
    vector<int> distance; 
    vector<int> adj_list[50];

    public: 
    GraphPaths() {
        this->has_edges = false; 
        this->has_vertices = false;
        this->src = NULL;
        this->des = NULL; 
        this->vert_num = 0;
    }

    bool BFS()
    {
        vector<int> queue;
        vector<bool> visited;
    
        for (int i = 0; i < vert_num; i++) 
        {
            visited[i] = false;  
            distance[i] = INT8_MIN;  
            pred[i] = -1;   
        }
    
        visited[src] = true;  
        distance[des] = 0;        
        queue.push_back(src);   
        int i = 0; 
    
        while (!queue.empty()) 
        {
            int q = queue.front();

            i = 0;
            while(i < adj_list[q].size()) 
            {
                if (visited[adj_list[q][i]] == false) 
                {
                    pred[adj_list[q][i]] = q;  
                    distance[adj_list[q][i]] = distance[q] + 1; 
                    visited[adj_list[q][i]] = true;  
                    queue.push_back(adj_list[q][i]);
                    if (adj_list[q][i] == des)  
                    {
                        return true;

                    }       
                }
                i++;
            }
            queue.erase(queue.begin());  
        }
        return false;
    }  

    vector<int> returnPath()
    {
        vector<int> path;
        int crawl = des;

        path.clear();
    
        if (BFS() == false) 
        {
            cerr << "Error: No path from source to destination."<< endl;
            return path;
        }

        path.push_back(crawl);
        while (pred[crawl] != -1) 
        {
            path.push_back(pred[crawl]);
            crawl = pred[crawl];
        }
        return path;
    } 

    void adding_edges(int src, int des, vector<int> adj_list[]) 
    {

        // add edge vertices to each others adjacency list
        adj_list[src].push_back(des);
        adj_list[des].push_back(src);
    }



    void validInputGraph(string liner){
    if (regex_match(liner, regex("V [0-9][0-9]*")))
                {
                    regex r("\\d+");
                    smatch s;
                    if (regex_search(liner, s, r)) {
                        if (s.size()==1)
                        {
                            for (int i=0; i<s.size(); i++) {
                                stringstream ss; 
                                ss << s[i];
                                ss >> this->vert_num;
                            }
                        }   
                    }
                    cout<<"vert num id add V"<<vert_num<<endl;
                    if (vert_num > 0)
                    {
                        this->has_vertices = true; 
                        this->has_edges = false; 
                    }
                }
            else if (regex_match(liner, regex("E \\{(<[0-9][0-9]*,[0-9][0-9]*>,)*(<[0-9][0-9]*,[0-9][0-9]*>)\\}")))
                {
                    edges.clear();
                    string strr = liner;
                    regex r("<[0-9][0-9]*,[0-9][0-9]*>");
                    smatch s;
                    while(regex_search(strr,s,r)) {
                        string pairs = s.str();
                        regex r_number("[0-9][0-9]*");
                        smatch numberm;
                        vector<int> vertices;
                        while(regex_search(pairs,numberm,r_number)) {
                            int vertex;
                            stringstream ss; 
                            ss << numberm.str();
                            ss >> vertex;
                            pairs = numberm.suffix();
                            vertices.push_back(vertex);
                        }
                        // cout<<"vert num"<<vert_num<<endl;
                        if (1 <= vertices[0] <= vert_num && 1 <= vertices[1] <= vert_num) {
                            pair<int, int> v = make_pair(vertices[0], vertices[1]);
                            edges.push_back(v);
                            strr = s.suffix();
                        }
                        else {
                            cout<<"Error: edge vertex cannot be labeled greater than total vertices"<<endl;
                            break;
                        }

                    }
                    if(edges.size() == 0)
                    {
                        cout<<"Error:";
                    }
                    else {
                        this->has_edges = true;
                    }
            }
            else if (regex_match(liner, regex("s [0-9][0-9]* [0-9][0-9]*")))
                {
                    string source_dest = liner;
                    regex r_number("[0-9][0-9]*");
                    smatch numberm;
                    vector<int> vertices;
                    while(regex_search(source_dest,numberm,r_number)) {
                            int vertex;
                            stringstream ss; 
                            ss << numberm.str();
                            ss >> vertex;
                            source_dest = numberm.suffix();
                            vertices.push_back(vertex);
                        }
                    this->src = vertices[0];
                    this->des = vertices[1];
                    // cout<<"SRC"<<src<<endl;
                    // cout<<"dest"<<des<<endl;
                    // cout<<"vertnum"<<vert_num<<endl;
                    // cout<<edges.size()<<endl;
                    if (src==NULL || des==NULL || vert_num == 0 || edges.size()==0)
                    {
                        cout<<"Error: entries cannot be empty."<<endl;
                    }
                    if (this->src > this->vert_num && this->des > this->vert_num)
                    {
                        cout<<"Error: source or dest vertex index cannot be more than total vertices."<<endl;
                    }
                    if (has_edges && has_vertices &&  this->src != NULL && this->des != NULL)
                    {
                        this->returnPath();
                    }
                }
            else {
                cout<<"Error:invalid input"<<endl;
            } 
        }
};
 
int main(int argc, char** argv) {
    GraphPaths min_path = GraphPaths();
    vector<int> path;
    while (!cin.eof()) {
        // read a line of input until EOL and store in a string
        string line;
        getline(cin, line);
        min_path.validInputGraph(line);
        

        path = min_path.returnPath();
        cout <<"path"<<path.size()<<endl;
                if (!path.empty())
                {
                    for (int i = path.size() - 1; i >= 0; i--)
                    {
                        cout << path[i];
                        if (i != 0)
                        {
                            cout<<"-";
                        }
                    }
                    cout<<"\n";
                }
    }
}
