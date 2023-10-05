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
const int MAX=200001;
const int LOG = ceil(log2(1e9));
class TreeAncestor {
  public:
  // vector<vector<int>>up;
  int up[MAX][31];
  
  TreeAncestor(int n, vector<int>& parent) {
      // LOG = ceil(log2(1e9));
      // up.resize(n+1,vector<int>(LOG+1,-1));
      memset(up,-1,sizeof(up));
      for(int i=0;i<=n;i++)
      {
          up[i][0]=parent[i];
      }   

      for(int j=1;j<=LOG;j++)
      {
          for(int i=0;i<=n;i++)
          {
              if(up[i][j-1]!=-1)
              up[i][j] = up[up[i][j-1]][j-1];
              else 
              up[i][j]=-1;
              
          }
      }
  }

    
  int getKthAncestor(int node, int k) {
   
      if(k==1)
      return up[node][0];

     
      int ans=node;
      for(int j=0;j<=LOG;j++) //O(log(N))
      {
          if(k&(1<<j))
          {
             

              ans=up[ans][j];
              if(ans==-1)
              break;
              

              k-=(1<<j);
          }
      }

      return ans;
  }
};


void solve()
{
  int n,q;
  cin>>n>>q;
  vector<int>parent(n+1,-1);
  for(int i=1;i<=n;i++)
  {
    int u;
    cin>>u;
    parent[i]=u;
  }
  TreeAncestor ob(n,parent);

  for(int i=0;i<q;i++)
  {
    int node,k;
    cin>>node>>k;

    cout<<ob.getKthAncestor(node,k)<<nline;
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
