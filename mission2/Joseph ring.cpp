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
	//~looplist();  //析构函数出错
	void create_list();
	void show_list();        //展示链表
	void delete_node();
private:
	Node *Head;
	int first_code;   //初始密码
	int m;         //初始密码报数上限  
	int length;   //链表中元素个数
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
		cout << "清空链表完成" << endl;
	}
}
*/
void looplist::create_list()  //尾插法
{
	int n,i;
	cout << "初始密码报数上限：";
	cin >> m;
	cout << "参与人数：";
	cin >> n;
	if (n > Max_num || n < 1)
	{
		cout << "超出范围！" << endl;
	
		exit(0);
	}
	length = n;
	Node *q,*s;	
	cout<<"输入1号密码：";
	cin>>Head->code;
	Head->data=1;
	q=Head;
	for(i=1;i<length;i++)
	{
		s=new Node;
		cout<<"输入"<<i+1<<"号密码：";
		cin>>s->code;
		s->data=i+1;
		s->next=q->next;
		q->next=s;
		q=q->next;
	}
	//q指向最后一个 
	//cout<<"最后q的序号"<<q->data<<endl;
	
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
	int order;       //每一轮的密码
	cout << "设置初始密码：";
	cin >> first_code;
	order = first_code;
	Node *link = Head;
	Node *s = link;
	if (first_code > m || first_code < 1)
	{
		cout << "超出范围！" << endl;
		exit(0);
	}
	cout<<"初始长度为："<<length<<endl;
	while (length)
	{
		for (int i = 1; i < order; i++)
		{
			s = link;
			link = link->next;
		}
		s->next = link->next;
		cout << "删除" << link->data << "号，新密码为：" << link->code << endl;
		order=link->code;
		link = s->next;	
		length--;
	}
	cout<<"出列完毕"<<endl;
}

int main()
{
	looplist L;
	L.create_list();
	L.show_list();
	L.delete_node();
	return 0;
}

