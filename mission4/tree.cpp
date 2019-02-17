#include<iostream>
#include<stack>
#include<queue>
using namespace std;
struct Node
{
	char data;
	Node *lchild,*rchild;
};
bool visit(char m)
{
	cout<<m<<" ";
	return true;
}
void CreateTree(Node *&T)
{
	char a;
	cin>>a;
	if(a =='#') T=NULL;
	else
	{
		T=new Node;
		T->data=a; 
		CreateTree(T->lchild);
		CreateTree(T->rchild);
	}

}
void PreOrderTraverse(Node *T)
{
	if(T)
	{
		cout<<T->data<<" ";
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(Node *T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		cout<<T->data<<" ";
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(Node *T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout<<T->data<<" ";
	}
}

void PreOrderTraverse_2(Node *T)
{
	stack<Node *> s;
	Node *p;
	s.push(T->rchild);
	//cout<<s.top()->data<<endl;
	p=T;
	while(!s.empty())
	{
		while(p->lchild)
		{
			visit(p->data);
			s.push(p->rchild);
			//cout<<s.top()->data<<"!"; 
			p=p->lchild;
		}
		visit(p->data);
		p=s.top();
		s.pop();
	}
}

void InOrderTraverse_2(Node *T)
{
	stack<Node *> s;
	Node *p;
	s.push(T);
	while(!s.empty())
	{
		while((p=s.top()) && p)s.push(p->lchild);
		p=s.top();
		s.pop();
		if(!s.empty())
		{
			p=s.top();
			s.pop();
			if(!visit(p->data))exit(0);
			s.push(p->rchild);
		}
	}
}
void PostOrderTraverse_2(Node* T)
{
    if (T == NULL)
        return;
    stack<Node*> s;  
    Node* pCur, *pLastVisit;//pCur:��ǰ���ʽڵ㣬pLastVisit:�ϴη��ʽڵ�
    pCur = T;
    pLastVisit = NULL;
    while (pCur)
    {
        s.push(pCur);
        pCur = pCur->lchild;
    }
    while (!s.empty())
    {
        pCur = s.top();
        s.pop();
        if (pCur->rchild == NULL || pCur->rchild == pLastVisit)     //һ�����ڵ㱻���ʵ�ǰ���ǣ������������������ѱ����ʹ�
        {
            cout << pCur->data<< " ";
            pLastVisit = pCur;
        }
        else
        {
            s.push(pCur);
            pCur = pCur->rchild;
            while (pCur)
            {
                s.push(pCur);
                pCur = pCur->lchild;
            }
        }
    }
    cout << endl;
}
void q_Traverse(Node *T)
{
	Node *p;
	queue<Node *> q;
	if(T!=NULL)
	{
		q.push(T);
		while(!q.empty())
		{
			p=q.front();
			q.pop();
			cout<<p->data<<" ";
			if(p->lchild!=NULL)q.push(p->lchild);
			if(p->rchild!=NULL)q.push(p->rchild);
		}
	}
 } 
void print(Node *T) //������ӡ 
{  
	void printHelp(Node* T,string ss);
	string ss="";  
	printHelp(T,ss); 
}
void printHelp(Node* T,string ss) //������ӡ���ṹ 
{
	if(T==NULL)   
		return;  
	ss+="   ";  
	printHelp(T->rchild,ss);  
	cout<<ss<<T->data<<endl;  
	printHelp(T->lchild,ss); 
}
int main()
{
	Node *T;
		
	cout<<"�������������û�е�Ԫ����#�ţ�"<<endl;
	CreateTree(T);
	cout<<"����ݹ������"<<endl;
	PreOrderTraverse(T);
	cout<<endl;
	cout<<"����ݹ������"<<endl;
	InOrderTraverse(T);
	cout<<endl;
	cout<<"����ݹ������"<<endl;
	PostOrderTraverse(T);
	cout<<endl;
	cout<<"����ǵݹ������"<<endl;
	PreOrderTraverse_2(T);
	cout<<endl;
	cout<<"����ǵݹ������"<<endl;
	InOrderTraverse_2(T);
	cout<<endl;
	cout<<"����ǵݹ������"<<endl;
	PostOrderTraverse_2(T);
	cout<<"���ö��в��������"<<endl;
	q_Traverse(T);
	cout<<endl;
	cout<<"���ð�����ӡ��������"<<endl;
	print(T);
	return 0;
	//-+a##*b##-c##d##/e##f## 
}
