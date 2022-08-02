#include<iostream>
#include<sstream>
using namespace std;

const int MAXINT = 10000000;
struct Mg
{
	int arcs[100][100];
};
void dijkstra(Mg Gn, int v0, int end,int n,int path[], int dist[]);
 
int main()
{
	Mg Gn;
	int i,j;
	int n;
	int begin,end;
	cout << "��������·���м����ڵ㣺";
	cin >> n;
	cout << "��������·�ķ��ù�ϵ���󣺣���10000000���������" << endl;
	for(i=0;i<n;i++)
		for (j = 0; j < n; j++)
		{
			cin >> Gn.arcs[i][j];
		}
	cout << "���������Ϊ�ĸ��ڵ㣺";
	cin >> begin;
	cout << "�������յ�Ϊ�ĸ��ڵ㣺";
	cin >> end;
	int* path = new int[n];
	int* dist = new int[n];
	dijkstra(Gn, begin-1,end-1,n,path, dist);
	return 0; 
}

void dijkstra(Mg Gn, int v0, int end,int n,int path[], int dist[])
{
	int v,i;
	int* s = new int[n];
	for (v = 0; v < n; v++)
	{
		s[v] = 0;
		dist[v] = Gn.arcs[v0][v];
		if (dist[v] < MAXINT){
			path[v] = v0;
		}else{
			path[v] = -1;
		}
	}
	dist[v0] = 0;
	s[v0] = 1;
	for (i = 0; i <=n ; i++){
		int min = MAXINT;
		int v = -1;
		for (int w = 0; w < n; w++){
			if (!s[w] && dist[w] < min){
				v = w;
				min = dist[w];
			}
		}
			if (v == -1)break;
			s[v] = 1;
			for (int j = 0; j < n; j++){
				if (!s[j] && (min + Gn.arcs[v][j] < dist[j])){
					dist[j] = min + Gn.arcs[v][j];
					path[j] = v;
				}
			}
	}
	if (dist[end] >= MAXINT){
		cout << "��������޷�����㵽���յ�" << endl;
	}else{
		cout << "����㵽�յ����С�����ǣ�" << dist[end] << endl;
		i = end;
		int num = 0;
		do {
			s[num] = i;
			num++;
			i = path[i];
		} while (i!= v0);
		s[num] = v0;
		for (i = num; i>0;i--){
			cout << s[i]+1 << "->";
		}
		cout << s[0]+1 << endl;
	}
}
