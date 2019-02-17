#include<iostream>
#include<string>
#include<queue>
using namespace std;
bool visited[6];
struct ArcNode 
{
	int weight;
	int adjvex;//�ڽӵ�
	ArcNode *next; //ָ����һ���� 
};
struct VNode
{
    int data;
    ArcNode *firstedge;
};
struct Graph
{
	int vexnum,arcnum; //��������ͱ���  
	VNode *adjlist;     //�ڽӱ����� 
};
struct EdgeArr
{
	int start,end;
};
EdgeArr Darr[20];
EdgeArr Barr[20]; 
int d=0,b=0;
void CreateGraph(Graph &G)
{
	int i;
	int v1,v2,w;
	G.vexnum=6;
	G.arcnum=11;
	G.adjlist=new VNode[G.vexnum];
	ArcNode *e,*p,*q;
	for(i=0;i<G.vexnum;i++)
	{
		G.adjlist[i].data=i;
		G.adjlist[i].firstedge=NULL;
	} 
	cout<<"����ÿ����(i,j,w)\n";
	for(i=0;i<G.arcnum;i++)
	{
		cout<<"�����"<<i+1<<"����:";
		cin>>v1>>v2>>w;        //�������������Ȩ��
		if(G.adjlist[v1].firstedge==NULL)
		{
			e=new ArcNode;  //newһ���µĻ��� 
			e->adjvex=v2; 
			e->weight=w;
			e->next=NULL;
			G.adjlist[v1].firstedge=e;
		} 
		else
		{
			p=G.adjlist[v1].firstedge;
			while(p->next)
			{
				p=p->next;
			}
			e=new ArcNode;
			e->adjvex=v2;
			e->weight=w;
			e->next=NULL;
			p->next=e;
		}
		if(G.adjlist[v2].firstedge==NULL)
		{
			e=new ArcNode;
			e->adjvex=v1;
			e->weight=w;
			e->next=NULL;
			G.adjlist[v2].firstedge=e;
		}
		else
		{
			p=G.adjlist[v2].firstedge;
			while(p->next)
			{
				p=p->next;
			}
			e=new ArcNode;
			e->adjvex=v1;
			e->weight=w;
			e->next=NULL;
			p->next=e;
		}
	}	 
	cout<<"�����ɹ���"<<endl;
} 
void DFSTraverse(Graph &G,int v)  //�������
{
	cout<<G.adjlist[v].data<<" ";
	visited[v]=true; 
	ArcNode *arc;
	arc=G.adjlist[v].firstedge;
	while(arc)
	{
		if(!visited[arc->adjvex])
		{
			Darr[d].start=v;
			Darr[d].end=arc->adjvex;
			d++;
			DFSTraverse(G,arc->adjvex);			
		} 
		arc=arc->next;
	}	
}
void BFSTraverse(Graph &G,int v)  //�������
{
	queue<int> q;
	bool visit[G.vexnum];
	for(int i=0;i<G.vexnum;i++)
	visit[i]=false;
	ArcNode *p;
	int w;
	if(!visit[v])
	{
		visit[v]=true;
		cout<<G.adjlist[v].data<<" ";
		q.push(G.adjlist[v].data);
	}
	while(!q.empty())
	{
		int f=q.front();
		q.pop();
		p=G.adjlist[f].firstedge;
		while(p) 
		{
			w=p->adjvex;
			if(!visit[w])
			{
				Barr[b].start=f;
				Barr[b].end=w;
				b++;
				visit[w]=true;
				cout<<G.adjlist[w].data<<" ";
				q.push(G.adjlist[w].data);
			}
			p=p->next;
		}
	}		
}
int main()
{
	Graph g;
	int v;
	CreateGraph(g);
	cout<<"������ȱ���\n������ʼ�㣺";
	cin>>v;
	DFSTraverse(g,v);
	cout<<"\n������ȱ�����ɣ�\n��Ӧ�������ı߼�Ϊ��"<<endl;
	for(int i=0;i<d;i++)
	cout<<"("<<Darr[i].start<<","<<Darr[i].end<<")";
	cout<<"\n������ȱ���\n������ʼ�㣺";
	cin>>v;
	BFSTraverse(g,v);
	cout<<"\n���������ɣ�\n��Ӧ�������ı߼�Ϊ��"<<endl;
	for(int i=0;i<b;i++)
	cout<<"("<<Barr[i].start<<","<<Barr[i].end<<")";
	cout<<endl;
	return 0;
 } 
