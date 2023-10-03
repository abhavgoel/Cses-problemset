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

vector<ll>toposort(vector<vector<ll>>&graph,vector<ll>&indegree)
{
  queue<ll>q;
  for(int i=1;i<indegree.size();i++)
    if(indegree[i]==0)
      q.push(i);

  vector<ll>topo;
  while(!q.empty())
  {
    ll node = q.front();
    q.pop();
    topo.pb(node);

    for(auto it:graph[node])
    {
      indegree[it]--;
      if(indegree[it]==0)
        q.push(it);
    }

  }
  return topo;

}
void solve()
{
  ll n,m;
  cin>>n>>m;

  vector<vector<ll>>graph(n+1);
  vector<ll>indegree(n+1);
  for(int i=0;i<m;i++)
  {
    ll u,v;
    cin>>u>>v;
    graph[u].pb(v);//u-->v
    indegree[v]++;
  }
  queue<ll>q;
  q.push(1);
  vector<ll>ways(n+1);
  ways[1]=1;

  vector<ll>dist(n+1,1e9);
  dist[1]=0;

  vector<ll>topo = toposort(graph,indegree);

  // for(auto i:topo)
  //   cout<<i<<" ";

  for(int i=0;i<topo.size();i++)
  {
    ll u = topo[i];
    for(auto v:graph[u])
    {
      ways[v]+=ways[u]%MOD;
      ways[v]=ways[v]%MOD;
    }
  }
  cout<<ways[n];

 

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
