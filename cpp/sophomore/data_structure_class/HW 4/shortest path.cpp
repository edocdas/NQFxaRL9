#include <iostream>

using namespace std;

enum Boolean {FALSE, TRUE};
const int nmax = 100;

class Graph
{
private:
     int length[nmax][nmax];
     int a[nmax][nmax];
     int dist[nmax];
     int predecessor[nmax];
     Boolean s[nmax];
     int newdist[nmax];
public:
     void ShortestPath(const int, const int);
     void BellmanFord(const int, const int);
     void BellmanFord2(const int, const int);
     void AllLengths(const int);
     int choose(const int);
     void Setup();
     void Setup2();
     void Setup3();
     void Setup4();
     void Out(int);
     void OutA(int);
};

void Graph::Out(int n)
{
   cout << endl;
   for (int i = 0; i < n; i++) cout << dist[i] << ", ";
   cout << endl;
}

void Graph::OutA(int n)
{
   cout << endl;
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++) cout << a[i][j] << "  ";
      cout << endl;
   }
}

void Graph::Setup()
{
    for (int i = 0; i < 8; i++)
	for (int j = 0; j < 8; j++)
	    if (i == j) length[i][j] = 0; else length[i][j] = 10000;
    length[1][0] = 300;

    length[2][0] = 1000;
    length[2][1] = 800;

    length[3][2] = 1200;

    length[4][3] = 1500;
    length[4][5] = 250;

    length[5][3] = 1000;
    length[5][6] = 900;
    length[5][7] = 1400;

    length[6][7] = 1000;

    length[7][0] = 1700;
}

void Graph::Setup2()
{
    for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	    if (i == j) length[i][j] = 0; else length[i][j] = 10000;
    length[0][1] = 7;

    length[1][2] = -5;
    length[0][2] = 5;
}

void Graph::Setup3()
{
    for (int i = 0; i < 7; i++)
	for (int j = 0; j < 7; j++)
	    if (i == j) length[i][j] = 0; else length[i][j] = 10000;
    length[0][1] = 6;
    length[0][2] = 5;
    length[0][3] = 5;

    length[1][4] = -1;

    length[2][1] = -2;
    length[2][4] = 1;

    length[3][2] = -2;
    length[3][5] = -1;

    length[4][6] = 3;

    length[5][6] = 3;
}

void Graph::Setup4()
{
    for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	    if (i == j) length[i][j] = 0; else length[i][j] = 10000;
    length[0][1] = 4;
    length[0][2] = 11;

    length[1][0] = 6;
    length[1][2] = 2;

    length[2][0] = 3;
}

void Graph::ShortestPath(const int n, const int v)

{
    for (int i = 0; i < n; i++) {s[i] = FALSE; dist[i] = length[v][i];} // initialize
    s[v] = TRUE;
    dist[v] = 0;

    Out(n);
    for (int i = 0; i < n-2; i++) { // determine @n-1@ paths from vertex @v@
	int u = choose(n);  // @choose@ returns a value @u@:
			    // @dist[u]@ = minimum @dist[w]@, where @s[w]@ = FALSE
	s[u] = TRUE;
	for (int w = 0; w < n; w++)
	    if (! s[w])
	       if (dist[u] + length[u][w] < dist[w])
		  dist[w] = dist[u] + length[u][w];
	Out(n);
    } // end of \fBfor\fR (@i@ = 0; ...)
}

int Graph::choose(const int n)
{
    int prevmax = -1; int index = -1;
    for (int i = 0; i < n; i++)
	if ( (!s[i]) && ((prevmax == -1) || (dist[i] < prevmax)) )
	    {prevmax = dist[i]; index = i;}
    return index;
}

void Graph::BellmanFord(const int n, const int v)
{
  for (int i = 0; i < n; i++) dist[i] = length[v][i];
  Out(n);
  for (int k = 2 ; k <= n-1; k++)
  {
   for (int u = 0; u < n ; u++)
    if (u != v) {
       for (int i = 0; i < n; i++)
	 if ((u != i) && (length[i][u] < 10000))
	   if (dist[u] > dist[i] + length[i][u]) dist[u] = dist[i] + length[i][u];
    }
   Out(n);
  }
}

void Graph::BellmanFord2(const int n_size, const int origin)
// Single source all destination shortest paths with negative edge lengths
{
  for (int i = 0; i < n_size; i++)
  {
    dist[i] = length[origin][i]; // initialize @dist@

    if(dist[i] != 10000)
      predecessor[i] = origin;
  }
  for (int k = 2 ; k <= n_size-1; k++)
  {
   for (int l = 0; l < n_size; l++)
    newdist[l] = dist[l];
   for (int to = 0; to < n_size ; to++)
    if (to != origin)
    {
       for (int from = 0; from < n_size; from++)
	      if ((to != from) && (length[from][to] < 10000))
	        if (newdist[to] > dist[from] + length[from][to])
          {
            newdist[to] = dist[from] + length[from][to];
            predecessor[to] = from;
          }
    }
   for (int i = 0; i < n_size; i++) dist[i] = newdist[i];
  }

  std::cout << "distance copare to node " << origin << "\n";
  for(int i = 0;i < n_size;i++)
    std::cout << dist[i] << " ";
  std::cout << "\n\n";
  std::cout << "each node predecessor\n";
  for(int i = 0;i < n_size;i++)
    std::cout << predecessor[i] << " ";
  std::cout << "\n\n";

  std::cout << "each node path:\n";
  for(int i = 0;i < n_size;i++)
  {
    int pre_node = predecessor[i];
    std::string path = std::to_string(i);
    while(pre_node != origin)
    {
      path = std::to_string(pre_node) + "," + path;
      pre_node = predecessor[pre_node];
    }

    std::cout << "from node " << origin << " to node " << i << "\n";
    if(i == origin)
      std::cout << path << "\n";
    else
      std::cout << origin << "," << path << "\n";
  }
  std::cout << "\n";
}

void Graph::AllLengths(const int n)
// @length[n][n]@ is the adjacency matrix of a graph with @n@ vertices.
// @a[i][j]@ is the length of the shortest path between @i@ and @j@
{
    for (int i = 0; i < n; i++)
       for (int j = 0; j < n; j++)
	   a[i][j] = length[i][j];   // copy @length@ into @a@
    for (int k = 0; k < n; k++) {  // for a path with highest vertex index @k@
       OutA(n);

       for (int i = 0; i < n; i++)  // for all possible pairs of vertices
	  for (int j = 0; j < n; j++)
	      if ((a[i][k] + a[k][j]) < a[i][j]) a[i][j] = a[i][k] + a[k][j];
    }
    OutA(n);
}



int main()
{
  {
    Graph g;
    g.Setup3();
    g.BellmanFord2(7, 0);
  }

  {
    Graph g;
    g.Setup4();
    g.BellmanFord2(3, 0);
    g.BellmanFord2(3, 1);
    g.BellmanFord2(3, 2);
  }
}