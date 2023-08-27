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
  int n,m;
  cin>>n>>m;
  vector<string>graph;
  for(int i=0;i<n;i++)
  {
    string s;
    cin>>s;
    graph.pb(s);
  }

  queue<pair<pair<int,int>,int>>q;//{{i,j},dist};
  vector<vector<int>>vis(n,vector<int>(m));
  pair<int,int>start;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      if(graph[i][j]=='A')
      {
        start={i,j};
        // vis[i][j]=1;
      }
      if(graph[i][j]=='M')
      {
        q.push({{i,j},0});
        vis[i][j]=1;
      }
    }
  }

  //multi source bfs from all monsters... to find shortest distance 
  vector<vector<int>>dist(n,vector<int>(m));
  

  while(!q.empty())
  {
    auto it = q.front();
    q.pop();

    int i = it.first.first;
    int j = it.first.second;
    int d = it.second;

    dist[i][j] = d;

    for(int k=0;k<4;k++)
    {
      int row = i+dx[k];
      int col = j+dy[k];

      if(valid(row,col,n,m) && vis[row][col]==0 && graph[row][col]!='#')
      {
        q.push({{row,col},d+1});
        vis[row][col]=1;
      }
    }

  }

  //dist vector has shortest distance to every cell from monster
  //to-do
  // for(int i=0;i<n;i++)
  // {
  //   for(int j=0;j<m;j++)
  //   {
  //     cout<<dist[i][j];
  //   }
  //   cout<<nline;
  // }


  q.push({{start.first,start.second},0});

  vis = vector<vector<int>>(n,vector<int>(m,0));

  bool flag=false;
  vector<vector<int>>movemt(n,vector<int>(m,0));
  pair<int,int>endd;
  while(!q.empty())
  {

    auto it = q.front();
    q.pop();

    int i  = it.first.first;
    int j = it.first.second;
    int d = it.second;
    // cout<<i<<j<<d;

    if(i==0 || i==n-1 || j==0 || j==m-1)
    {

      flag=true;
      endd={i,j};
      vis[i][j]=1;
      break;
    }

    for(int k=0;k<4;k++)
    {
      int row = i+dx[k];
      int col = j+dy[k];

      if(valid(row,col,n,m) && vis[row][col]==0 && graph[row][col]=='.' && (d+1 < dist[row][col] || dist[row][col]==0))
      {
        // cout<<d+1<<" ";
        q.push({{row,col},d+1});
        movemt[row][col]=k;
        vis[row][col]=1;
      }
    }
  }
  // cout<<vis[endd.first][endd.second];
  if(flag==false)
  {
    cout<<"NO";
    return;
  }

  else
  {
    string dir = "RLDU";
    string ans="";

    while(endd!=start)
    {
      int ind = movemt[endd.first][endd.second];
      ans+=dir[ind];
      endd={endd.first - dx[ind],endd.second - dy[ind]};
    }
    reverse(ans.begin(),ans.end());
    cout<<"YES"<<nline;
    cout<<ans.size()<<nline;
    cout<<ans;
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
