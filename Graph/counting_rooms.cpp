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
 
void dfs(int i,int j,vector<vector<int>>&vis,vector<string>&graph)
{
  if(valid(i,j,graph.size(),graph[i].size()) == false || vis[i][j]==1 || graph[i][j]=='#')
    return;
 
  vis[i][j]=1;
  for(int k=0;k<4;k++)
  {
    int row = i + dx[k];
    int col = j + dy[k];
 
    dfs(row,col,vis,graph);
  }
}
void solve()
{
  ll n,m;
  cin>>n>>m;
 
  vector<string>graph;
  for(int i=0;i<n;i++)
  {
    string s;
    cin>>s;
    graph.pb(s);
  }
 
  vector<vector<int>>vis(n,vector<int>(m,0));
  int count=0;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      if(graph[i][j]=='.' && vis[i][j]==0)
      {
        dfs(i,j,vis,graph);
        count++;
      }
    }
  }
  cout<<count<<nline;
 
  // for(auto i:graph)
  //   cout<<i<<nline;
 
 
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