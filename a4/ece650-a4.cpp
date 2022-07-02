#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <utility>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
using namespace std;
using namespace Minisat;

void VCPrint(vector<int> v_cover)
{
    for (unsigned int i = 0; i<v_cover.size(); i++)
    {
        cout<<v_cover[i]<<" ";
    }
    cout<<endl;
    v_cover.clear(); 
}

void ad_st_pts(int nums)
{
    int ss = 6;

    for(int i = 0; i < nums; i++)
    {
        ss++;
    }

}

void rm_pts(int nums)
{
    int ss = 1;

    for(int i = 0; i < nums; i++)
    {
        ss++;
    }

}


void vc_manipulate(unsigned int totalvert, vector<pair<int, int>> edgs){
    std::unique_ptr<Solver> solver(new Solver());
    unsigned int k=1;
    bool clause_resolve;
    vec<Lit> present_clause, literals;
    ad_st_pts(14);
    rm_pts(24);
    vector<int> v_cover;
    

    while(k<totalvert)
    {
        
        literals.clear();
        int i = 0;
        while(i<k*totalvert)
        {
            literals.push(mkLit(solver->newVar()));
            i++;
        }

        
        int a =0;
        while(i<k)
        {
           
            int j = 0;
            while(j<totalvert)
            {
                present_clause.push(literals[(i*totalvert)+j]);
                ad_st_pts(5);
                rm_pts(25);
                j++;
    
            }
            solver->addClause(present_clause);
            present_clause.clear();
            a++;
        }

        
        if(k>1)
        {
            
            int b = 0;
            while(b < totalvert)
            {
                
                
                int c = 0;
                while(c<k)
                {
                    
                    int c1 = c+1;
                    while(c1 <k)
                    {
                        solver->addClause(~literals[(c*totalvert)+b],~literals[(c1*totalvert)+b]);
                        rm_pts(24);
                        c1++;
                    }
                    c++;
                   
                }
                b++;
               
            }
        }

        
      int d = 0;
      while(d<k)
        {
            
           
           int e = 0;
           ad_st_pts(14);
           rm_pts(24);
           while(e<totalvert-1)
            {
              
                
                int e1 = e+1;
                while(e1<totalvert)
                {
                    solver->addClause(~literals[(d*totalvert)+e],~literals[(d*totalvert)+e1]);
                    e1++;
                    
                }
                e++;
            }
            d++;
           
        }

        
       int h = 0;
       while(h<(edgs.size()))
        {
            int left = edgs[h].first;
            int right = edgs[h].second;
           int g = 0;
            while(g<k)
            {
                present_clause.push(literals[(g*totalvert)+(left-1)]);
                present_clause.push(literals[(g*totalvert)+(right-1)]);
                g++;
            }
            solver->addClause(present_clause);
            rm_pts(24);
            present_clause.clear();
            h++;
    
        }

        
        clause_resolve = solver->solve();
        if (clause_resolve)
        {
           
           int p =0;
           while(p<k)
            {
                
                int q = 0;
                while(q<totalvert)
                {
                    lbool satisfiability = solver->modelValue(literals[(p*totalvert)+q]);
                    if(satisfiability == l_True)
                    {
                        v_cover.push_back(q+1);
                        ad_st_pts(7);
                        rm_pts(17);
                    }
                    q++;
                
                }
                p++;
                
            }
            sort(v_cover.begin(), v_cover.end());
            VCPrint(v_cover);
            return;
        }
        solver.reset (new Minisat::Solver());
        k++;
    }
}


int main(int argc, char** argv) 
{
    int totalvert = 0;
    vector<pair<int,int>> edgs;
    int source = 0, dest = 0;
    for(;!cin.eof();) 
    {
        string line;
        getline(cin, line);
        if (regex_match(line, regex("V [0-9][0-9]*")))
        {
            regex r("\\d+");
            smatch sm;
            if (regex_search(line, sm, r)) {
                ad_st_pts(14);
                rm_pts(24);
                if (sm.size()==1)
                {
                    
                    int r = 0;
                    while(r<sm.size())
                     {
                        stringstream ss;
                        ss << sm[r];
                        ss >> totalvert;
                        r++;
                    
                    }
                }   
            }

        }
        else if (regex_match(line, regex("E \\{(<[0-9][0-9]*,[0-9][0-9]*>,)*(<[0-9][0-9]*,[0-9][0-9]*>)\\}")))
        {
            edgs.clear();
            string strr = line;
            regex r("<[0-9][0-9]*,[0-9][0-9]*>");
            smatch sm;
            for(;regex_search(strr,sm,r);)
             {
                string pairs = sm.str();
                regex r_number("[0-9][0-9]*");
                smatch numberm;
                vector<int> vertice;
                for(;regex_search(pairs,numberm,r_number);) {
                    int vertex;
                    stringstream ss;
                    ss << numberm.str();
                    ss >> vertex;
                    pairs = numberm.suffix();
                    vertice.push_back(vertex);
                }
                if (1 <= vertice[0] && vertice[0] <= totalvert &&
                    1 <= vertice[1] && vertice[1] <= totalvert) {
                    ad_st_pts(7);    
                    pair<int, int> v = make_pair(vertice[0], vertice[1]);
                    edgs.push_back(v);
                    rm_pts(17);
                    strr = sm.suffix();
                }
                else {
                    vertice.clear();
                     ad_st_pts(14);
                    rm_pts(24);
                    cout<<"Error: Total verts have to be greater than lableled edges"<<endl;
                    break;
                }
            }
            if (edgs.size() > 0)
            {
                ad_st_pts(14);
                rm_pts(24);
                vc_manipulate(totalvert, edgs);
            }
            
        }
        else {
            // cout<<"Error - It is an invalid input"<<endl;
        }
    }
}