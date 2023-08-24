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
  // int count=0;
  pair<int,int>start;
  pair<int,int>end;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      if(graph[i][j]=='A')
      {
        start.first = i;
        start.second = j;
      }
      else if(graph[i][j]=='B')
      {
        end.first=i;
        end.second=j;
      }
    }
  }
  vis[start.first][start.second]=1;
  queue<pair<int,int>>q;
  q.push(start);
 
  vector<vector<int>>prev(n,vector<int>(m,0));
  string steps= "RLDU";
  string movemt="";
  while(!q.empty())
  {
    auto it = q.front();
    q.pop();
 
    int i = it.first;
    int j = it.second;
    // string moves = it.second;
 
    // if(make_pair(i,j)==end)
    // {
    //   movemt = moves;
    //   break;
    // }
 
    for(int k=0;k<4;k++)
    { 
      int row = i+dx[k];
      int col = j+dy[k];
 
      if(valid(row,col,n,m) && vis[row][col]==0 && (graph[row][col]=='.' || graph[row][col]=='B'))
      {
        vis[row][col]=1;
        prev[row][col] = k;
        q.push({row,col});
      }
    }
  }
  if(vis[end.first][end.second])
  {
    cout<<"YES"<<nline;
 
    string movemt="";
    while(end!=start)
    {
      int ind = prev[end.first][end.second];
      movemt+=steps[ind];
 
      end = {end.first - dx[ind],end.second - dy[ind]};
    }
    reverse(movemt.begin(),movemt.end());
    cout<<movemt.size()<<nline;
 
    for(auto i:movemt)
      cout<<i;
    
  }
  else cout<<"NO"<<nline;
 
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