#include<iostream>
using namespace std;
#define max_num 50
struct Node
{
	Node *next;
	int data;
};
class set
{
public:
	set();
	//~set();
	set set_copy();
	void create_set(); //输入创造集合
	void show_set();  //展示集合
	void data_deduplication(); //去除集合中重复的元素
	set union_set(set &s);    //求集合的并
	set intersection(set &s);   //求集合的交
	set difference_set(set &s);       //求两个集合的差
private:
	Node *Head;
	int length;
};
set::set()
{
	Head = new Node;
	Head->data = NULL;
	Head->next = Head;
	length = 1;
}
set set::set_copy()
{
	int i;
	set set_link;
	set_link.length = length;
	Node *node_2_Head = new Node;
	node_2_Head->next = set_link.Head; //创建一个指向头指针的指针 
	set_link.Head->data = Head->data;
	Head = Head->next;
	for (i = 1; i < length; i++)
	{
		Node *k = new Node;
		k->data = Head->data;
		k->next = set_link.Head->next;
		set_link.Head->next = k;
		set_link.Head = k;
		Head = Head->next;
	}
	set_link.Head = node_2_Head->next;
	return set_link;
}
void set::create_set()
{
	int i;
	cout << "输入元素个数：";
	cin >> length;
	if(length > max_num || length<1)
	{
		cout<<"超出范围！"<<endl;
		exit(0);
	}
	Node *p = new Node;
	p = Head;
	cout << "输入元素：";
	cin >> Head->data;
	for (i = 1; i < length; i++)
	{
		Node *link = new Node;
		cin >> link->data;
		link->next = p->next;
		p->next = link;
		p = p->next;	
	}

}
void set::show_set()
{
	int i;
	Node *q = Head;
	cout << "集合为：";
	for (i = 0; i < length; i++)
	{
		cout << q->data << " ";
		q = q->next;
	}  
	cout << endl;
}

void set::data_deduplication()           //去掉重复的元素
{
	int i,j,count;
	count = length;
	Node *s1 = new Node;
	Node *s2 = new Node;
	s1 = Head;
	Node *s1_link = new Node;
	s1_link->next = Head;
	s2 = s1;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < length; j++)
		{
			if (s2->next->data == s1->data)
			{
				if (s2->next != s1)
				{
					Node *d = new Node;
					d = s2->next;
					s2->next = d->next;
					s2 = s2->next;
					length--;
					break;
				}
				else
				{
					break;
				}
				/*
				else if(s2->next->next==s1_link->next)
				{
					Node *d2 = new Node;
					d2 = s2->next;
					s2->next = d2->next;
					s2 = s2->next;					
					length--;
				}
				*/
			}
			else
			{
				s2 = s2->next;
			}
		}
		s1 = s1->next;
		s2 = s1;		
	}
	
	


}
set set::union_set(set &s)                //并
{
	set s3;
	int i;

	s3.length = length + s.length;
	Node *m = Head;
	Node *h = new Node; //h是原链表的“第一个”元素
	h->data = NULL;
	h->next = Head;
	for (i = 0; i < length - 1; i++)
	{
		m = m->next;
	}    //此时m变成原链表的“最后”一个元素
	
	Node *n = new Node;
	n->data = NULL;
	n->next = s.Head;
	m->next = s.Head;
	for (i = 0; i < s.length; i++)
	{
		m = m->next; //m变成链表s的最后一个元素
	}
	Node *n2 = new Node;
	n2->data = NULL;
	n2->next = m;
	m->next = h->next;
	s3.Head=h->next;
	m=m->next;
	s.Head = n->next;
	n2->next->next = s.Head;
	return s3;
}

set set::intersection(set &s)            //交，建立第三个集合， 把有相同的元素放到第三个集合中；
{
	int i, j;
	set L;
	Node *L1, *L2, *L3;
	Node *temp = new Node;
	Node *t_L2 = new Node;
	L1 = Head;
	L2 = s.Head;
	L3 = L.Head;
	temp->next = L3;         //temp->next指向L3 保留L3
	temp->data = NULL;
	t_L2->data = NULL;        //t_L2指向L2 保留L2
	t_L2->next = L2;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < s.length; j++)
		{
			if (L2->data != L1->data)L2 = L2->next;
			else
			{
				if (L3->data == NULL)
				{
					L3->data = L2->data;
					break;
				}
				else
				{
					L.length++;
					Node *L_link = new Node;
					L_link->data = L2->data;
					L_link->next = L3->next;
					L3->next= L_link;
					L3 = L3->next;
					break;
				}			
			}
		}
		L1 = L1->next;
		L2 = t_L2->next;
	}
	L3 = temp->next;
	return L;
}
set set::difference_set(set &s)              //求差，set本身减去set s；求差的函数可以用一个集合减去之前求得的交集，A-(A交B) s就是交集，那么只需要删除A中有的s的元素即可
{
	int i, j,count;      //count用来记录有没有遍历整个交集
	set L;
	Node *q1, *q2, *q3;
	q1 = Head;
	q2 = s.Head;
	q3 = L.Head;	
	Node *q2_link = new Node;    //用来保存结点q2
	Node *q3_link = new Node;   //用来保存结点q3
	Node *q_last = new Node;
	for (i = 0; i < s.length-1; i++)
	{
		q2 = q2->next;
	}
	q_last->next = q2;
	q2 = q2->next;
	q3_link->data = NULL;
	q3_link->next = q3;
	q2_link->data = NULL;
	q2_link->next = q2;
	L.length = length - s.length;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < s.length; j++)
		{
			if (q1->data == q2->data)
			{
				break;
			}
			else
			{
				
				if (q2->data == q_last->next->data)
				{
					if (q3->data == NULL)
					{
						q3->data = q1->data;
					}
					else
					{
						Node *n = new Node;
						n->data = q1->data;
						n->next = q3->next;
						q3->next = n;
						q3 = q3->next;
					}
				}
				q2 = q2->next;
			
			}

		}
		q1 = q1->next;
		q2 = q2_link->next;
	}
	q3=q3_link->next;
	return L;
}


int main()
{
	set s1, s2, s3,s4,s5,set_copy_s2;

	cout << "输入第一个集合" << endl;
	s1.create_set();
	s1.data_deduplication();
	s1.show_set();

	cout << "输入第二个集合" << endl;
	s2.create_set();
	s2.data_deduplication();
	set_copy_s2 = s2.set_copy();
	s2.show_set();

	cout << "并运算,结果："<<endl;
	s3=s1.union_set(s2);   
	s3.data_deduplication();
	s3.show_set();

	cout << "交运算，结果："<<endl;  
	s4 = s1.intersection(set_copy_s2);
	s4.show_set();

	cout << "差运算（第一个集合减去第二个集合），结果："; 
	s5 = s1.difference_set(s4);
	s5.show_set();

	cout << "差运算（第二个集合减去第一个集合），结果：";
	s5 = set_copy_s2.difference_set(s4);
	s5.show_set();



	system("pause");
	return 0;
}
