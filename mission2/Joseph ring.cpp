#include<iostream>
using namespace std;
#define Max_num 30
struct Node
{
	int data;
	int code;
	Node *next;
};
class looplist
{
public:
	looplist();
	//~looplist();  //������������
	void create_list();
	void show_list();        //չʾ����
	void delete_node();
private:
	Node *Head;
	int first_code;   //��ʼ����
	int m;         //��ʼ���뱨������  
	int length;   //������Ԫ�ظ���
};
looplist::looplist()
{
	Head = new Node;
	Head->next = Head;
	length = 1;
}
/*
looplist::~looplist()
{
	Node *f=new Node;
	if (Head != NULL)
	{
		f = Head->next;
		while (f != Head)
		{
			Head->next = f->next;
			delete f;
			f = Head->next;
		}
		delete f;
		cout << "����������" << endl;
	}
}
*/
void looplist::create_list()  //β�巨
{
	int n,i;
	cout << "��ʼ���뱨�����ޣ�";
	cin >> m;
	cout << "����������";
	cin >> n;
	if (n > Max_num || n < 1)
	{
		cout << "������Χ��" << endl;
	
		exit(0);
	}
	length = n;
	Node *q,*s;	
	cout<<"����1�����룺";
	cin>>Head->code;
	Head->data=1;
	q=Head;
	for(i=1;i<length;i++)
	{
		s=new Node;
		cout<<"����"<<i+1<<"�����룺";
		cin>>s->code;
		s->data=i+1;
		s->next=q->next;
		q->next=s;
		q=q->next;
	}
	//qָ�����һ�� 
	//cout<<"���q�����"<<q->data<<endl;
	
}
void looplist::show_list()
{
	Node *p = new Node;
	p = Head;
	for (int i = 0; i < length; i++)
	{
		cout << p->data << "  " << p->code << endl;
		p = p->next;
	}
	
}

void looplist::delete_node()
{
	int order;       //ÿһ�ֵ�����
	cout << "���ó�ʼ���룺";
	cin >> first_code;
	order = first_code;
	Node *link = Head;
	Node *s = link;
	if (first_code > m || first_code < 1)
	{
		cout << "������Χ��" << endl;
		exit(0);
	}
	cout<<"��ʼ����Ϊ��"<<length<<endl;
	while (length)
	{
		for (int i = 1; i < order; i++)
		{
			s = link;
			link = link->next;
		}
		s->next = link->next;
		cout << "ɾ��" << link->data << "�ţ�������Ϊ��" << link->code << endl;
		order=link->code;
		link = s->next;	
		length--;
	}
	cout<<"�������"<<endl;
}

int main()
{
	looplist L;
	L.create_list();
	L.show_list();
	L.delete_node();
	return 0;
}

