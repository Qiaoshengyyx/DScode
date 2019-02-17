#include<iostream>
using namespace std;
#define MAX 100
class sequence
{
public:
	sequence();
	~sequence();
	void get_sequence();           //����˳���
	void insert();				   //����Ԫ��
	void show();				   //���˳���
	void delete_num();			   //ɾ���ƶ���ŵ�Ԫ��
	void find_num();			   //����ָ����ţ����Ԫ��
	void in_or_not();			   //�������֣�����Ƿ���˳����ڣ��������Ԫ�ص����
	void find_max_min();		   //���˳�������Ԫ�غ���СԪ��
	void sort();				   //��˳����������
	void merge(sequence&,sequence&);//�����������ϲ���һ���������
	void reverse();					//��˳��������������
	//void deduction();
private:
	int length;
	int *a;
};
sequence::sequence()
{
	a = new int[MAX];
	if(!a)
	{
		exit(0);
	}
	length=0;
}

sequence::~sequence()
{
	delete []a;
}

void sequence::get_sequence()
{
	int n,i;
	cout<<"����Ԫ�ظ���:";
	cin>>n;
	if(n>MAX || n<1)cout<<"������Χ��"<<endl;
	for(i=0;i<n;i++)
		cin>>a[i];
	length=n;
}

void sequence::insert()
{
	int index_in,in,i;
	cout<<"����Ԫ�ص�����Լ���Ԫ�أ�";
	cin>>index_in>>in;
	if(index_in==100 || index_in<1)cout<<"������Χ��"<<endl;
	for(i=length;i>index_in-2;i--)
	{
		a[i+1]=a[i];
	}
	a[index_in-1]=in;
	length++;
	cout<<endl;
}
void sequence::delete_num()
{
	int index_out,i;
	cout<<"ɾ��ָ��Ԫ�ص����Ϊ��";
	cin>>index_out;
	if(index_out>length || index_out<1)cout<<"û�и���ŵ�Ԫ�أ�"<<endl;
	for(i=index_out;i<length;i++)
		a[i-1]=a[i];
	length--;
	cout<<endl;
}
void sequence::in_or_not()
{
	int num,i;
	cout<<"����Ҫ���ҵ�Ԫ�أ�";
	cin>>num;
	for(i=0;i<length;i++)
	{
		if(a[i]==num)
		{
			cout<<"�ǵ�"<<i+1<<"��Ԫ��"<<endl;
			break;
		}
		if(a[i]==a[length] && a[i]!=num)
			cout<<"û�и�Ԫ�أ�"<<endl;
	}
}
void sequence::show()
{
	int i;
	cout<<"˳���Ϊ��";
	for(i=0;i<length;i++)
	{
		if(!a[i])
		continue;
		cout<<a[i]<<" ";
	}
		
	cout<<endl;
}
void sequence::find_num()
{
	int index_find;
	cout<<"��ȡ��Ԫ�����:";
	cin>>index_find;
	if(index_find>length || index_find<1)cout<<"������Χ��"<<endl;
	else cout<<a[index_find-1]<<endl;
}
void sequence::find_max_min()
{
	int max_num,min_num,i;
	max_num=a[0];
	min_num=a[0];
	for(i=0;i<length;i++)
	{
		if(max_num<a[i])max_num=a[i];
		if(min_num>a[i])min_num=a[i];
	}
	cout<<"���Ԫ��"<<max_num<<endl;
	cout<<"��СԪ��"<<min_num<<endl;
}
void sequence::sort()
{
	int i,temp,j;
	cout<<"����"<<endl;
	for(i=1; i<length; i++)
	{
		for(j=0;j<length-i; j++)
		{
			if(a[j+1]<a[j])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
void sequence::reverse()
{
	int temp,i;
	cout<<"���ã�";
	for(i=0;i<(length/2);i++)
	{
		temp=a[i];
		a[i]=a[length-i-1];
		a[length-i-1]=temp;
	}
	cout<<endl;
}
void sequence::merge(sequence &s1,sequence &s2)
{
	int *p1=s1.a,*p2=s2.a;
	int *L3=new int[s1.length+s2.length];
	int *p3=L3;
	int *p1_last,*p2_last;
	p1_last=p1+s1.length-1;
	p2_last=p2+s2.length-1;
	int count=0,i;
	while(p1<=p1_last && p2<=p2_last)
	{	
		if(*p1<*p2)
		{
			*p3++=*p1++;
			count++;
		}
		else if(*p1>*p2)
		{
			*p3++=*p2++;
			count++;		
		}
		else if(*p1==*p2)
		{
			*p3++=*p1++;
			p2++;
			count++;
		}

	}
	while(p1<=p1_last)
	{
		*p3++=*p1++;
		count++;
	}
	while(p2<=p2_last)
	{
		*p3++=*p2++;
		count++;
	}
	for(i=0;i<count;i++)
	{
		for(int j=i+1;j<count;j++)
		{
			if(L3[i]==L3[j])L3[j]=NULL;
			else
				continue;
		}
	}
	cout<<"�ϲ�˳������L3��";
	for(i=0;i<count;i++)
	{
		if(!L3[i])
		continue;
		else cout<<L3[i]<<" ";		
	}
		
	cout<<endl;	
	delete []L3;
}
/*
void sequence::deduction()
{
	int i,j; 
	for(i=0;i<length;i++)
	{
		for(j=i+1;j<length;j++)
		{
			if(a[i]==a[j])a[j]=NULL;
			else
				continue;
		}
	}
	
} */
int main()
{
	sequence s1,L1,L2;
	cout<<"���� ����s1��"<<endl;
	s1.get_sequence();
	s1.show();
	s1.insert();
	s1.show();
	s1.delete_num();
	s1.show();
	s1.find_num();
	s1.in_or_not();
	s1.find_max_min();
	s1.reverse();
	s1.show();
	s1.sort();
	s1.show();	
	cout<<"���������L1��"<<endl;
	L1.get_sequence();
	cout<<"���������L2��"<<endl;
	L2.get_sequence();
	L1.merge(L1,L2);
	
	return 0;
}

	






	



	


	




