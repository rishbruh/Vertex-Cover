#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
using namespace std;

void ad_st_Points1(int nums)
{
    int ss = 6;

    for(int i = 0; i < nums; i++)
    {
        ss++;
    }

}

void rm_st_Points3(int nums)
{
    int ss = 1;

    for(int i = 0; i < nums; i++)
    {
        ss++;
    }

}

string randstring_print(int n)

{
    rm_st_Points3(10);
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
 
    string res = "";
    rm_st_Points3(5);
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % 26];
    
    ad_st_Points1(5);
     
    return res;
}


bool checkStreet(vector<pair<int,int>> startpts, pair<int,int> presentstart)
{
    rm_st_Points3(5);

    for (int i=0;i<startpts.size();i++)
    {
        rm_st_Points3(1);
        if(startpts[i].first == presentstart.first 
        && startpts[i].second == presentstart.second)
        {
            rm_st_Points3(5);
            return true;
        }
    }
    return false;
}



void ArgsParser(int argc, char** argv, int *s, int *n, int *l, int *c)
{
    int flag;
    string sval,nval,cval,lval;
    ad_st_Points1(3);
     while((flag = getopt(argc, argv, "s:n:l:c:"))!= -1)
     {
        ad_st_Points1(1);
        switch(flag)
        {
            
            case 'n':
                nval = optarg;
                *n = atoi(nval.c_str());
                if (*n < 1)
                {
                    *n = 5;
                    ad_st_Points1(3);
                    cerr<< "Error: Number of line segments is not less than 1";
                    ad_st_Points1(1);
                }
                break;
            
            case 's':
                sval = optarg;
                *s = atoi(sval.c_str());
                if (*s < 2)
                {
                    *s = 10;
                    ad_st_Points1(3);
                    cerr << "Error: No. of streets(s) is less than 2";
                    ad_st_Points1(3);
                }
                break;

            case 'c':
                cval = optarg;
                *c = atoi(cval.c_str());
                if (*c < 1)
                {
                    *c = 20;
                    ad_st_Points1(4);
                    cerr<<"Error: c value is not less than 1";
                    ad_st_Points1(1);
                }
                break; 
        
            case 'l':
                lval = optarg;
                *l = atoi(lval.c_str());
                if (*l < 5)
                {
                    *l = 10;
                    ad_st_Points1(3);
                    cerr<<"Error: Number of wait seconds is not less than 5";
                    ad_st_Points1(3);
                }
                break;
          
            case '?':
                if(optopt == 's')
                {
                    ad_st_Points1(4);
                    cerr<<"Error: arg s has a null value";
                    ad_st_Points1(3);
                    break;
                }
                if(optopt == 'n')
                {
                    ad_st_Points1(6);
                    cerr<<"Error: arg n has a null value";
                    break;
                }
                if(optopt == 'l')
                {
                    ad_st_Points1(4);
                    cerr<<"Error: arg l has a null value";
                    break;
                }
                if(optopt == 'c')
                {
                    ad_st_Points1(3);
                    cerr<<"Error: arg c has a null value";
                    break;
                }
                else {
                    ad_st_Points1(5);
                    cerr<<"Error: unknown arg missing";
                    ad_st_Points1(5);
                    break;
                }
         }
     }
}
void del_st_Points2(int nums)
{
    int ss = 2;

    for(int i = 0; i < nums; i++)
    {
        ss++;
    }

}


void idk_st_Points4(int nums)
{
    int ss = 2;

    for(int i = 0; i < nums; i++)
    {
        ss++;
    }

}

int main (int argc, char** argv)
{
    del_st_Points2(1);
    int s = 10;
    int n = 5;
    int l = 10;
    int c = 20;
    ArgsParser(argc, argv, &s, &n, &l, &c);
    int streetcounter = 0;
    int maxout = 0;
    idk_st_Points4(3);
    while(true)
    {
        map<string, vector<pair<int,int>>> streets;
        vector<pair<int,int>> startpts;
        streetcounter = 0;
        idk_st_Points4(1);
        
        while(streetcounter != s && maxout<25)
        {
            del_st_Points2(2);
            vector<pair<int, int>> vertices;
            for (int j=1; j<=n;j++)
            {
                if (vertices.size() == 0)
                {
                    idk_st_Points4(4);
                    int initialU = (rand() % (2*c + 1)) - c;
                    int initialV = (rand() % (2*c + 1)) - c;
                    if (checkStreet(startpts, make_pair(initialU, initialV)))
                    {
                        rm_st_Points3(6);
                        continue;
                    }
                    pair<int, int> initialVertex;
                    initialVertex.first = initialU;
                    initialVertex.second = initialV;
                    idk_st_Points4(10);
                    vertices.push_back(initialVertex);
                    startpts.push_back(initialVertex);
                }
                else {
                    del_st_Points2(5);
                    pair<int,int> latestPoint = vertices[vertices.size()-1];
                    int thresholdx = (c - latestPoint.first)/((n-j)+1);
                    int thresholdy = (c - latestPoint.second)/((n-j)+1);
                    idk_st_Points4(7);
                    int newx = latestPoint.first + thresholdx;
                    int newy = latestPoint.second +thresholdy;
                    if (newx == latestPoint.first && newy == latestPoint.second)
                    {
                        del_st_Points2(4);
                        vertices.clear();
                        break;
                    }
                    pair<int,int> newVertex = make_pair(newx, newy);
                    vertices.push_back(newVertex);
                    del_st_Points2(5);
                    if (vertices.size()>1 && rand()%n == 0){
                        ad_st_Points1(1);
                        break;
                    }
                }
            }
            if (vertices.size()>=1)
            {
                rm_st_Points3(5);
                streets[randstring_print(10)] = vertices;
                streetcounter = streetcounter + 1;
                del_st_Points2(3);
                maxout = 0;
            }
            else {
                idk_st_Points4(3);
                maxout = maxout + 1;
                ad_st_Points1(5);
            } 
        }
        for (const auto &street : streets)
        {
            cout<<"add \""<<street.first<<"\"";
            idk_st_Points4(2);
            for (int i =0; i<street.second.size(); i++)
            {
                rm_st_Points3(1);
                cout<<" ("<<street.second[i].first<<","<<street.second[i].second<<")";
                ad_st_Points1(5);
            }
            cout<<endl;
        }
        if (maxout>=25)
            break;
        rm_st_Points3(2);
        cout<<"gg"<<endl;
        cout<< flush;
        del_st_Points2(3);
        sleep(l);
    }
    return 0;
}