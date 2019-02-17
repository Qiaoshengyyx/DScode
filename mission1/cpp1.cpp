#include<iostream>
using namespace std;
#define MAX 100
class sequence
{
public:
	sequence();
	~sequence();
	void get_sequence();           //输入顺序表
	void insert();				   //插入元素
	void show();				   //输出顺序表
	void delete_num();			   //删除制定序号的元素
	void find_num();			   //输入指定序号，输出元素
	void in_or_not();			   //输入数字，检查是否在顺序表内，有则输出元素的序号
	void find_max_min();		   //输出顺序表的最大元素和最小元素
	void sort();				   //对顺序表进行排序
	void merge(sequence&,sequence&);//将两个有序表合并成一个表并且输出
	void reverse();					//对顺序表进行逆序排列
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
	cout<<"输入元素个数:";
	cin>>n;
	if(n>MAX || n<1)cout<<"超出范围！"<<endl;
	for(i=0;i<n;i++)
		cin>>a[i];
	length=n;
}

void sequence::insert()
{
	int index_in,in,i;
	cout<<"插入元素的序号以及该元素：";
	cin>>index_in>>in;
	if(index_in==100 || index_in<1)cout<<"超出范围！"<<endl;
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
	cout<<"删除指定元素的序号为：";
	cin>>index_out;
	if(index_out>length || index_out<1)cout<<"没有该序号的元素！"<<endl;
	for(i=index_out;i<length;i++)
		a[i-1]=a[i];
	length--;
	cout<<endl;
}
void sequence::in_or_not()
{
	int num,i;
	cout<<"输入要查找的元素：";
	cin>>num;
	for(i=0;i<length;i++)
	{
		if(a[i]==num)
		{
			cout<<"是第"<<i+1<<"个元素"<<endl;
			break;
		}
		if(a[i]==a[length] && a[i]!=num)
			cout<<"没有该元素！"<<endl;
	}
}
void sequence::show()
{
	int i;
	cout<<"顺序表为：";
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
	cout<<"读取表元，序号:";
	cin>>index_find;
	if(index_find>length || index_find<1)cout<<"超出范围！"<<endl;
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
	cout<<"最大元："<<max_num<<endl;
	cout<<"最小元："<<min_num<<endl;
}
void sequence::sort()
{
	int i,temp,j;
	cout<<"排序："<<endl;
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
	cout<<"逆置：";
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
	cout<<"合并顺序表输出L3：";
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
	cout<<"测试 输入s1："<<endl;
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
	cout<<"输入有序表L1："<<endl;
	L1.get_sequence();
	cout<<"输入有序表L2："<<endl;
	L2.get_sequence();
	L1.merge(L1,L2);
	
	return 0;
}

	






	



	


	




