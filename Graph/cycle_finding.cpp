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
  vector<vector<ll>>edges;


  for(int i=0;i<m;i++)
  {
    ll u,v,d;
    cin>>u>>v>>d;
    edges.pb({u,v,d});
  }
  vector<ll>dist(n+1);//setting dist array to 0, bcoz if we relax negative edges then
  //relaxation would be of negative weights i.e. 0(dist[u]) + (-ve value) < 0(dist[v])
  //we dont have a source node, so in this way the algo will also work in case of disconnected graph


  
  vector<ll>relaxant(n+1);
  ll x;
  for(int i=0;i<n;i++)
  {
    x=-1;
    for(auto j:edges)
    {
      ll u,v,d;
      u = j[0];
      v = j[1];
      d = j[2];

      if(dist[u]+d<dist[v])
      {
        dist[v]=dist[u]+d;
        // cout<<u<<" "<<v<<" "<<d<<" ";
        // cout<<u<<" "<<dist[u]<<" "<<v<<" "<<dist[v]<<nline;
        relaxant[v]=u;
        x=v;
       
      }
      
    }
    //cout<<endl;
  }
  if(x==-1)
  {
    cout<<"NO";
    return;
  }
  else
  {
    // cout<<x;
    cout<<"YES"<<nline;
    for(int i=0;i<n-1;i++)
    {
      x=relaxant[x];
    }

    ll start = x;
    start=relaxant[x];

    vector<ll>cycle;
    cycle.pb(x);
    while(start!=x)
    {
      cycle.pb(start);
      start=relaxant[start];
    }
    cycle.pb(x);
    reverse(all(cycle));
    for(auto i:cycle)
      cout<<i<<" ";

    return;
  }
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
