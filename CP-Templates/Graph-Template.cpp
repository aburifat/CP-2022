#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MX 200010

ll node,edge;
vector<ll>adj[MX];
bool visited[MX];
bool idxOne=false;
ll timeIn[MX],timeLow[MX];
ll timer;
bitset<MX>AP;
map<pair<ll,ll>,ll>bridge;
vector<ll>apList;
vector<pair<ll,ll> >bridgeList;

//Initiate Basic Graph Containers OK
void initGraph(){
    for(ll i=0;i<MX;i++){
		adj[i].clear();
		visited[i]=false;
	}
}

//Initiate Cutpoint & Bridge Containers OK
void initAPBridge(){
    AP.reset();
    apList.clear();
    bridge.clear();
    bridgeList.clear();
    for(ll i=0;i<MX;i++){
        timeIn[i]=-1;
        timeLow[i]=-1;
    }
}

//Initiate OK
void init()
{
    initGraph();
    initAPBridge();
}

//Undirected Edges OK
void unDirEdge(ll u, ll v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

//Directed Edges
void dirEdge(ll u, ll v)
{
    adj[u].push_back(v);
}

//DFS to find single CC OK
vector<ll>compList[MX];
void compDFS(ll s,ll idx) {
    visited[s]=true ;
    compList[idx].push_back(s);
    for (auto u:adj[s]) {
        if (!visited[u]){
        	visited[u]=true ;
            compDFS(u,idx);
        }
    }
}

//Get all CC and number of CC OK
ll conComp(){
	for(ll i=0;i<MX;i++)compList[i].clear();
	ll ctComp=0;
    ll idx_st=0,idx_end=node;
    if(idxOne)idx_st++,idx_end++;
    for(ll i=idx_st;i<idx_end;i++){
        if(!visited[i]){
            compDFS(i,ctComp);
            ctComp++;
        }
    }
    return ctComp;
}

//Add Cutpoint
void addAP(ll v){
    if(!AP[v]){
        AP[v]=1;
        apList.push_back(v);
    }
}

//Add Bridge OK
void addBridge(ll v, ll to){
    if(!bridge[{v,to}]&&!bridge[{to,v}])bridgeList.push_back({v,to});
    bridge[{v,to}]=1;
    bridge[{to,v}]=1;
}

//DFS to Find Cutpoints & Bridges in a CC OK
void apBridgeDFS(ll v, ll p=-1){
    visited[v]=true;
    timeIn[v]=timeLow[v]=timer++;
    ll children=0;
    for(ll to:adj[v]){
        if(to==p)continue;
        if(visited[to]){
            timeLow[v]=min(timeLow[v],timeIn[to]);
        }else{
            apBridgeDFS(to,v);
            timeLow[v]=min(timeLow[v],timeLow[to]);
            if(timeLow[to]>=timeIn[v]&&p!=-1)addAP(v);
            if(timeLow[to]>timeIn[v])addBridge(v,to);
            ++children;
        }
    }
    if(p==-1&&children>1)addAP(v);
}

//find All Cutpoints & Bridges
void apBridge(){
    timer=0;
    ll idx_st=0,idx_end=node;
    if(idxOne)idx_st++,idx_end++;
    for(ll i=idx_st;i<idx_end;i++){
        if(!visited[i]){
            apBridgeDFS(i);
        }
    }
}