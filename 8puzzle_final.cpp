#include<bits/stdc++.h>
using namespace std;

string goal= "*12345678";

vector<int>moven[10],moven_cross[10];

map<string,bool>vis;
map<string,string>parent;
map<string,int>dist;

struct node
{
    string nodeindex;
    int cost;
    int f;//cost+huristic
    node(string n,int c,int _f)
    {
        nodeindex=n;
        cost=c;
        f=_f;
    }
};

priority_queue<node>PQ;
int n;

int huristic_mismatch(string position)
{
    int Count;
    for(int i=0; i<=8; i++)
    {
        if(goal[i]!= position[i])
        {
            Count++;
        }
    }
    return Count;
}

void printstep(string position)
{
    cout<<position[0]<<" "<<position[1]<<" "<<position[2]<<endl;
    cout<<position[3]<<" "<<position[4]<<" "<<position[5]<<endl;
    cout<<position[6]<<" "<<position[7]<<" "<<position[8]<<endl;
}

bool operator<(node A, node B)
{
    if(A.f> B.f)
        return true;
    else
        return false;
}

int index_zero(string s)
{
    for(int i=0; i<=8; i++)
    {
        if(s[i]=='*')  //'*'
            return i;
    }
}

int huristic_cross(string source)
{
    map<string,bool>vis_cross;
    map<string,string>parent_cross;
    map<string,int>dist_cross;

    priority_queue<node>PQ_cross;

    node s= node(source,0,0+huristic_mismatch(source));
    PQ_cross.push(s);
    parent_cross[source]="";
    vis_cross[source]= 1;
    dist_cross[source]= 0;
    while(!PQ_cross.empty())
    {
        node a= PQ_cross.top();
        string u= a.nodeindex;
        PQ_cross.pop();
        int zero_index= index_zero(u);
        for(int i=0; i<moven_cross[zero_index].size(); i++)
        {

            string temp= u;
            int nextmove= moven_cross[zero_index][i];
            swap(temp[zero_index], temp[nextmove]);
            if(temp==goal)
            {
                vis_cross[temp]= 1;
                dist_cross[temp]= dist_cross[u]+1;
                parent_cross[temp]= u;
                return dist_cross[temp];
            }
            if(vis_cross.find(temp)== vis_cross.end())
            {
                dist_cross[temp]= dist_cross[u]+1;
                parent_cross[temp]= u;
                vis_cross[temp]= 1;
                node b= node(temp, dist_cross[temp], dist_cross[temp]+huristic_mismatch(temp));
                PQ_cross.push(b);
                return dist_cross[temp];
            }
            if(dist_cross[temp]>dist_cross[u]+1)
            {
                dist_cross[temp]= dist_cross[u]+1;
                parent_cross[temp]= u;
                node b= node(temp, dist_cross[temp], dist_cross[temp]+huristic_mismatch(temp));
                PQ_cross.push(b);
                return dist_cross[temp];
            }

        }
    }
    //return 10000000;
}

void puzzle_with_h1(string source)
{
    node s= node(source,0,0+huristic_mismatch(source));
    PQ.push(s);
    parent[source]="";
    vis[source]= 1;
    dist[source]= 0;
    while(!PQ.empty())
    {
        node a= PQ.top();
        string u= a.nodeindex;
        PQ.pop();
        int zero_index= index_zero(u);
        for(int i=0; i<moven[zero_index].size(); i++)
        {
            string temp= u;
            int nextmove= moven[zero_index][i];
            swap(temp[zero_index], temp[nextmove]);
            if(temp==goal)
            {
                vis[temp]= 1;
                dist[temp]= dist[u]+1;
                parent[temp]= u;
                return;
            }
            if(vis.find(temp)== vis.end())
            {
                dist[temp]= dist[u]+1;
                parent[temp]= u;
                vis[temp]= 1;
                node b= node(temp, dist[temp], dist[temp]+huristic_mismatch(temp));
                PQ.push(b);
            }
            if(dist[temp]>dist[u]+1)
            {
                dist[temp]= dist[u]+1;
                parent[temp]= u;
                node b= node(temp, dist[temp], dist[temp]+huristic_mismatch(temp));
                PQ.push(b);
            }
        }
    }
}

void puzzle_with_h2(string source)
{
    node s= node(source,0,0+huristic_cross(source));
    PQ.push(s);
    parent[source]="";
    vis[source]= 1;
    dist[source]= 0;
    while(!PQ.empty())
    {
        node a= PQ.top();
        string u= a.nodeindex;
        PQ.pop();
        int zero_index= index_zero(u);
        for(int i=0; i<moven[zero_index].size(); i++)
        {
            string temp= u;
            int nextmove= moven[zero_index][i];
            swap(temp[zero_index], temp[nextmove]);
            if(temp==goal)
            {
                vis[temp]= 1;
                dist[temp]= dist[u]+1;
                parent[temp]= u;
                return;
            }
            if(vis.find(temp)== vis.end())
            {
                dist[temp]= dist[u]+1;
                parent[temp]= u;
                vis[temp]= 1;
                node b= node(temp, dist[temp], dist[temp]+huristic_cross(temp));
                PQ.push(b);
            }
            if(dist[temp]>dist[u]+1)
            {
                dist[temp]= dist[u]+1;
                parent[temp]= u;
                node b= node(temp, dist[temp], dist[temp]+huristic_cross(temp));
                PQ.push(b);
            }
        }
    }
}

int pathprint(string node)
{
    vector<string>path;
    while(node!="")
    {
        path.push_back(node);
        node= parent[node];
    }
    reverse(path.begin(),path.end());
    for(int i=0; i<path.size(); i++)
    {
        printstep(path[i]);
        cout<<"------"<<endl;
    }
    cout<<endl;
}

void init()
{
    moven[0].push_back(1);
    moven[0].push_back(3);
    moven[1].push_back(0);
    moven[1].push_back(2);
    moven[1].push_back(4);
    moven[2].push_back(1);
    moven[2].push_back(5);
    moven[3].push_back(0);
    moven[3].push_back(4);
    moven[3].push_back(6);
    moven[4].push_back(1);
    moven[4].push_back(3);
    moven[4].push_back(5);
    moven[4].push_back(7);
    moven[5].push_back(2);
    moven[5].push_back(4);
    moven[5].push_back(8);
    moven[6].push_back(3);
    moven[6].push_back(7);
    moven[7].push_back(4);
    moven[7].push_back(6);
    moven[7].push_back(8);
    moven[8].push_back(5);
    moven[8].push_back(7);
}
void init_for_cross_movement()
{
    moven_cross[0].push_back(1);
    moven_cross[0].push_back(3);
    moven_cross[0].push_back(4);
    moven_cross[1].push_back(0);
    moven_cross[1].push_back(2);
    moven_cross[1].push_back(3);
    moven_cross[1].push_back(4);
    moven_cross[1].push_back(5);
    moven_cross[2].push_back(1);
    moven_cross[2].push_back(4);
    moven_cross[2].push_back(5);
    moven_cross[3].push_back(0);
    moven_cross[3].push_back(1);
    moven_cross[3].push_back(4);
    moven_cross[3].push_back(6);
    moven_cross[3].push_back(7);
    moven_cross[4].push_back(0);
    moven_cross[4].push_back(1);
    moven_cross[4].push_back(2);
    moven_cross[4].push_back(3);
    moven_cross[4].push_back(5);
    moven_cross[4].push_back(6);
    moven_cross[4].push_back(7);
    moven_cross[4].push_back(8);
    moven_cross[5].push_back(1);
    moven_cross[5].push_back(2);
    moven_cross[5].push_back(4);
    moven_cross[5].push_back(7);
    moven_cross[5].push_back(8);
    moven_cross[6].push_back(3);
    moven_cross[6].push_back(4);
    moven_cross[6].push_back(7);
    moven_cross[7].push_back(3);
    moven_cross[7].push_back(4);
    moven_cross[7].push_back(5);
    moven_cross[7].push_back(6);
    moven_cross[7].push_back(8);
    moven_cross[8].push_back(4);
    moven_cross[8].push_back(5);
    moven_cross[8].push_back(7);
}

void clear_()
{
    vis.clear();
    parent.clear();
    dist.clear();
    PQ = priority_queue <node>();
}

int main()
{
    string source="7245*6831";
    freopen("8puzzleoutput.txt","w",stdout);
    init();
    cout<<"Solution for heuristic function 1:"<<endl;
    //string source="7245*6831";
    puzzle_with_h1(source);
    if(vis.find("*12345678")== vis.end())
    {
        cout<<"Solution not possible."<<endl;
    }

    else
    {
        pathprint("*12345678");
    }
    cout<<"Total number of steps is: "<<dist[goal]<<endl;
    cout<<"As the number of steps represent the cost in this case, so the cost is: "<<dist[goal]<<endl;
    cout<<"__________________________________________________________"<<endl;
    cout<<endl;
    cout<<"Solution for heuristic function 2:"<<endl;
    clear_();
    init_for_cross_movement();
    //string source="7245*6831";
    puzzle_with_h2(source);
    if(vis.find("*12345678")== vis.end())
    {
        cout<<"Solution not possible."<<endl;
    }

    else
    {
        pathprint("*12345678");
    }
    cout<<"Total number of steps is: "<<dist[goal]<<endl;
    cout<<"As the number of steps represent the cost in this case, so the cost is: "<<dist[goal]<<endl;
    return 0;
}
