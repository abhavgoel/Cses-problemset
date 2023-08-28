#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define all(a) a.begin(),a.end()
#define flash ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define test int t;cin>>t;while(t--)
#define loop(n) for(int i=0;i<n;i++)
#define input(arr,n) for(int i=0;i<n;i++)cin>>arr[i];
#define nline "\n"
#define P pair<ll,pair<ll,ll>>
using namespace std;
using namespace chrono;
int MOD=1000000007; 
bool valid(int x,int y,int n,int m){return x>=0 && x<n && y>=0 && y<m;}
int powMod(int a,int n){ ll ans=1;for(int i=1;i<=n;i++){ ans=(ans*a)%MOD;}return ans%MOD; }
vector<int>dx={0,0,1,-1};
vector<int>dy={1,-1,0,0};
class DSU{
  public:
    vector<int>rank,parent,size;
    
    DSU(int n)
    {
        rank.resize(n+1,0);
        size.resize(n+1,1);
        parent.resize(n+1);
        for(int i=0;i<=n;i++)
        parent[i]=i;
    }
    int findParent(int node)
    {
        if(node==parent[node])
        return node;
 
        return parent[node] = findParent(parent[node]);
    }
    void unionByRank(int u,int v)
    {
        int ultParent_u = findParent(u);
        int ultParent_v = findParent(v);
 
        if(ultParent_u==ultParent_v)return;
 
        else if(rank[ultParent_u]<rank[ultParent_v])
        {
            parent[ultParent_u]=ultParent_v;
        }
        else if(rank[ultParent_v]<rank[ultParent_u])
        {
            parent[ultParent_v]=ultParent_u;
        }
        else 
        {
            parent[ultParent_v]=ultParent_u;
            rank[ultParent_u]++;
        }
 
    }
    void unionBySize(int u,int v)
    {
        int ultParent_u = findParent(u);
        int ultParent_v = findParent(v);
 
        if(ultParent_u==ultParent_v)return;
 
        else if(size[ultParent_u]<size[ultParent_v])
        {
            parent[ultParent_u]=ultParent_v;
            size[ultParent_v]+=size[ultParent_u];
        }
        else if(size[ultParent_v]<size[ultParent_u])
        {
            parent[ultParent_v]=ultParent_u;
            size[ultParent_u]+=size[ultParent_v];
        }
        else 
        {
            parent[ultParent_v]=ultParent_u;
            size[ultParent_u]+=size[ultParent_v];
        }
    }
};
 
void solve()
{
  ll n,m;
  cin>>n>>m;
 
  vector<vector<pair<ll,ll>>>graph(n+1);
  // vector<int>dist(n+1);
 
  loop(m)
  {
    int u,v,d;
    cin>>u>>v>>d;
    graph[u].pb({v,d});
 
  }
 
  vector<ll>dist(n+1,LONG_MAX);
  priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
  pq.push({0,1});
    dist[1]=0;
    vector<ll>vis(n+1);
    // vis[1]=1;
 
    
  while(pq.empty()==false)
  {
    auto it = pq.top();
    pq.pop();
 
    ll node = it.second;
    ll d = it.first;
    if(vis[node]==1)
      continue;
    vis[node]=1;
 
    for(auto i:graph[node])
    {
      ll wt = i.second;
      ll adjNode = i.first;
 
      if(wt + dist[node] < dist[adjNode])
      {
        dist[adjNode] = wt+d;
        pq.push({dist[adjNode],adjNode});
      }
     }
  }
  for(int i =1;i<=n;i++)
    cout<<dist[i]<<" ";
 
}
 
int main()
{
  flash
  
  auto start1 = high_resolution_clock::now();
    // test
    solve();
  auto stop1 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop1 - start1);
  cerr << "Time in miliseconds: " << duration.count() / 1000 << endl;
  return 0;
}