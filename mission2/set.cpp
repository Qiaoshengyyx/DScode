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
	void create_set(); //���봴�켯��
	void show_set();  //չʾ����
	void data_deduplication(); //ȥ���������ظ���Ԫ��
	set union_set(set &s);    //�󼯺ϵĲ�
	set intersection(set &s);   //�󼯺ϵĽ�
	set difference_set(set &s);       //���������ϵĲ�
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
	node_2_Head->next = set_link.Head; //����һ��ָ��ͷָ���ָ�� 
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
	cout << "����Ԫ�ظ�����";
	cin >> length;
	if(length > max_num || length<1)
	{
		cout<<"������Χ��"<<endl;
		exit(0);
	}
	Node *p = new Node;
	p = Head;
	cout << "����Ԫ�أ�";
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
	cout << "����Ϊ��";
	for (i = 0; i < length; i++)
	{
		cout << q->data << " ";
		q = q->next;
	}  
	cout << endl;
}

void set::data_deduplication()           //ȥ���ظ���Ԫ��
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
set set::union_set(set &s)                //��
{
	set s3;
	int i;

	s3.length = length + s.length;
	Node *m = Head;
	Node *h = new Node; //h��ԭ����ġ���һ����Ԫ��
	h->data = NULL;
	h->next = Head;
	for (i = 0; i < length - 1; i++)
	{
		m = m->next;
	}    //��ʱm���ԭ����ġ����һ��Ԫ��
	
	Node *n = new Node;
	n->data = NULL;
	n->next = s.Head;
	m->next = s.Head;
	for (i = 0; i < s.length; i++)
	{
		m = m->next; //m�������s�����һ��Ԫ��
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

set set::intersection(set &s)            //�����������������ϣ� ������ͬ��Ԫ�طŵ������������У�
{
	int i, j;
	set L;
	Node *L1, *L2, *L3;
	Node *temp = new Node;
	Node *t_L2 = new Node;
	L1 = Head;
	L2 = s.Head;
	L3 = L.Head;
	temp->next = L3;         //temp->nextָ��L3 ����L3
	temp->data = NULL;
	t_L2->data = NULL;        //t_L2ָ��L2 ����L2
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
set set::difference_set(set &s)              //��set�����ȥset s�����ĺ���������һ�����ϼ�ȥ֮ǰ��õĽ�����A-(A��B) s���ǽ�������ôֻ��Ҫɾ��A���е�s��Ԫ�ؼ���
{
	int i, j,count;      //count������¼��û�б�����������
	set L;
	Node *q1, *q2, *q3;
	q1 = Head;
	q2 = s.Head;
	q3 = L.Head;	
	Node *q2_link = new Node;    //����������q2
	Node *q3_link = new Node;   //����������q3
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

	cout << "�����һ������" << endl;
	s1.create_set();
	s1.data_deduplication();
	s1.show_set();

	cout << "����ڶ�������" << endl;
	s2.create_set();
	s2.data_deduplication();
	set_copy_s2 = s2.set_copy();
	s2.show_set();

	cout << "������,�����"<<endl;
	s3=s1.union_set(s2);   
	s3.data_deduplication();
	s3.show_set();

	cout << "�����㣬�����"<<endl;  
	s4 = s1.intersection(set_copy_s2);
	s4.show_set();

	cout << "�����㣨��һ�����ϼ�ȥ�ڶ������ϣ��������"; 
	s5 = s1.difference_set(s4);
	s5.show_set();

	cout << "�����㣨�ڶ������ϼ�ȥ��һ�����ϣ��������";
	s5 = set_copy_s2.difference_set(s4);
	s5.show_set();



	system("pause");
	return 0;
}
