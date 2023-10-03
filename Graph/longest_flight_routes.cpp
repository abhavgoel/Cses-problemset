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

    //can also be done by normal bfs
  ll n,m;
  cin>>n>>m;
  vector<vector<int>>graph(n+1);
  vector<ll>indegree(n+1);

  for(int i=0;i<m;i++)
  {
    int u,v;
    cin>>u>>v;
    graph[u].pb(v);
    indegree[v]++;

  }

  vector<ll>dist(n+1,0);
  vector<ll>parent(n+1);


  queue<ll>q;
  for(int i=1;i<indegree.size();i++)
  {
    if(indegree[i]==0)
      q.push(i);
  }
  vector<ll>topo;
  while(!q.empty())
  {
    ll node = q.front();
    q.pop();
    topo.pb(node);

    for(auto i:graph[node])
    {
      indegree[i]--;
      if(indegree[i]==0)
      {
        q.push(i);
      }
    }
  }

  // for(int i=0;i<topo.size();i++)
  //   cout<<topo[i]<<" ";
  // cout<<nline;

  // ll src_ind;
  // for(int i=0;i<topo.size();i++)
  //   if(topo[i]==1)
  //   {
  //     src_ind=i;
  //     break;
  //   }

  vector<ll>dp(n+1,LONG_MIN);
  dp[1]=0;
  for(int i=0;i<topo.size();i++)
  {
    // if(i<src_ind)continue;
    ll u = topo[i];
    for(auto v:graph[u])
    {
      //u-->v
      if(1+dp[u]>dp[v])
      {
        dp[v]=1+dp[u];
        parent[v]=u;
      }
    }
  }
  

  // for(auto i:parent)
  //   cout<<i<<" ";
  // cout<<dist[n];
  if(dp[n]<=0)
  {
    cout<<"IMPOSSIBLE";
    return;
  }
  else
  {
    cout<<dp[n]+1<<nline;
    vector<ll>ans;
    ll k = n;
    while(k!=1)
    {
      ans.pb(k);
      k=parent[k];
    }
    ans.pb(1);
    reverse(begin(ans),end(ans));
    for(auto i:ans)
      cout<<i<<" ";

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
