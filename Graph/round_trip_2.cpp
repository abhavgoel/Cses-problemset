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

int start,endd;
vector<ll>cycle;
bool dfs(int node ,vector<int>&vis,vector<int>&pathvis,vector<vector<int>>&graph)
{
  vis[node]=1;
  pathvis[node]=1;
  cycle.pb(node);
  for(auto it:graph[node])
  {
    if(vis[it]==0)
    {
      if(dfs(it,vis,pathvis,graph)==true)
      {
        return true;
      }
    }
      else if(vis[it]==1 && pathvis[it]==1)
      {
        cycle.pb(it);
        return true;
      }
    
  }
  cycle.pop_back();
  pathvis[node]=0;
  return false;
}
void solve()
{
  ll n,m;
  cin>>n>>m;

  vector<vector<int>>graph(n+1);

  for(int i=0;i<m;i++)
  {
    ll u,v;
    cin>>u>>v;
    graph[u].pb(v);
  }
  vector<int>parent(n+1);
  vector<int>vis(n+1),pathvis(n+1);
  for(int i=1;i<=n;i++)
  {
    if(vis[i]==0 && dfs(i,vis,pathvis,graph)==true)
    {
      int temp = cycle.back();
      vector<int>ans;
      int ind=-1;
      for(int j=0;j<cycle.size();j++)
      {
        if(cycle[j]==temp)
        {
          ind=j;
          break;
        }
      }

      ans.assign(cycle.begin()+ind,cycle.end());
      cout<<ans.size()<<nline;
      for(auto j:ans)
        cout<<j<<" ";
      return ;
    }
  }

  cout<<"IMPOSSIBLE";
  return;
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
