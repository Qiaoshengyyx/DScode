#include<iostream>
#include<string>
//#include<stdlib.h>
#include<cmath>
using namespace std;
#define stack_length 100
#define stack_increase 10
template<class T>
class stack
{
public:
	stack();
	T GetTop();
	T GetBase();
	void push(T elem);
	bool is_empty();
	bool is_full();
	T pop();
	int get_size();
	void show();
	
private:
	T *base,*top;
	int length;
};
template<class T>
stack<T>::stack()
{
	base = new T[stack_length];
	if (!base) exit(0);
	length = stack_length;
	top = base;
}
template<class T>
T stack<T>::GetBase()
{
	if (is_empty())exit(0);
	return *base;
}
template<class T>
bool stack<T>::is_empty()
{
	if (top == base)return true;
	else return false;

}
template<class T>
void stack<T>::push(T elem)
{
	if (top-base >= length)exit(0);
	else
	{
		*top = elem;
		top++;
	}

}
template<class T>
T stack<T>::pop()
{
	double num;
	if (is_empty())exit(0);
	top--;
	num = *top;
	return num;
	
}
template<class T>
T stack<T>::GetTop()
{
	T t;
	if (is_empty())exit(0);
	t = *(top-1);
	return t;
}
template<class T>
int stack<T>::get_size()
{
	return top-base;
}
template<class T>
bool stack<T>::is_full()
{
	if (top-base == length)return true;
	else
		return false;

}
template<class T>
void stack<T>::show()
{
	int i;
	for (i = 0; i < get_size(); i++)
	{
		cout << base[i] << " ";
	}
	cout << endl;
}

int getIndex(char ch)   //获取ch所对应的索引  
{
	int index = 0;
	switch (ch)
	{
		case '+':
			index = 0;
			break;
		case '-':
			index = 1;
			break;
		case '*':
			index = 2;
			break;
		case '/':
			index = 3;
			break;
		case '(':
			index = 4;
			break;
		case ')':
			index = 5;
			break;
		case 'e':
			index = 7;
			break;
		case 'l':
			index = 8;
			break;
		case 's':
			index = 9;
			break;
		case '#':
			index = 6;
		default:
			break;
	}
	return index;
}
char getPriority(char ch1, char ch2)   //获取ch1与ch2之间的优先级  
{
	const char priority[10][10] =     //算符间的优先级关系  
	{//    +   -   *   /   (   )   #   e   l   s
		{ '>','>','<','<','<','>','>','<','<','<'},
		{ '>','>','<','<','<','>','>','<','<','<'},
		{ '>','>','>','>','<','>','>','<','<','<'},
		{ '>','>','>','>','<','>','>','<','<','<'},
		{ '<','<','<','<','<','=',' ','<','<','<'},
		{ '>','>','>','>',' ','>','>','<','<','<'},
		{ '<','<','<','<','<',' ','=','<','<','<'},
		{ '>','>','>','>','<','>','>','>','>','>'},
		{ '>','>','>','>','<','>','>','>','>','>'},
		{ '>','>','>','>','<','>','>','>','>','>'},		
	};

	int index1 = getIndex(ch1);
	int index2 = getIndex(ch2);
	return priority[index1][index2];
}
double calculate(double a, char ch, double b)   //计算a ch b   
{
	switch (ch)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
		default:
			break;
	}
	return 0;
}
bool is_d_oper(char ch) 
{ 
    char ptr[7] = {'+', '-', '*', '/', '(', ')', '#'};
    int i; 
    for(i=0; i<7; i++)
	{
		if(ch==ptr[i]) return true;
    } 
     return false; 
}
bool is_o_oper(char ch)  //是否为单目运算符 
{
	char ptr[3]={'e','l','s'};
	int i;
	for(i=0;i<3;i++)
	{
		if(ch==ptr[i])return true;
	}
	return false; 
}
bool is_oper(char ch)
{
	char ptr[10]={'+', '-', '*', '/', '(', ')', '#','e','l','s'};
	int i;
	for(i=0;i<10;i++)
	{
		if(ch==ptr[i])return true;
	}
	return false;
}
bool check(string s) 
{ //检查表达式括号是否匹配
    int flag=0, i;
    for(i=0; s[i]!='#'; i++)
	 {
        if(s[i]=='(')
            flag++;
        if(s[i]==')')
            flag--;
    }
    if(flag)
        return false;
    else
        return true;

}
int main()
{
	string str;           
	stack<double> OPND;  //操作数
	stack<char> OPTR;   //操作符
	OPTR.push('#');
	int i;
	cout << "输入表达式(以#号作为结束标志)：";
	cin>>str;
	if(!check(str))
	{
		cout<<"括号不匹配！"<<endl;
		return 0; 
	}
	double a,b,n;
	for(i=0;i<str.length();i++)
	{
		if(str[i]>='0' && str[i]<='9')
		{
			a=str[i]-'0';
			i++;
			n=1;
			for(;str[i]>='0' && str[i]<='9';i++)
			{
				n=n*10;
				b=str[i]-'0';
				a=a*n+b;
			}
			if(str[i]=='.')
			{
				i++;
				n=1;
				for(;str[i]>='0' && str[i]<='9';i++)
				{
					b=str[i]-'0';
					n=n*10;
					a=a+b/n;
				}		
			}
			OPND.push(a);
			//cout<<OPND.GetTop()<<endl;
		}
		if(is_oper(str[i]))    
		{
			char ch1,ch2,pr,theta;
			double x; 
			ch1=OPTR.GetTop();
			//cout<<ch1<<" ";
			ch2=str[i];
			//cout<<ch2<<endl;
			pr=getPriority(ch1,ch2);
			
			
			switch(pr)
			{
				case '<':
					OPTR.push(ch2);
					break;
				case '=':
					OPTR.pop();	
					break;
				case '>':
					if(is_d_oper(ch1))
					{
						theta=OPTR.pop();  //弹出一个运算符 
						double d=OPND.pop(); //第二个操作数 
						double c=OPND.pop();  //第一个操作数
						OPND.push(calculate(c,theta,d));
						i--; 
	
						//cout<<"结果："<<calculate(c,theta,d)<<endl;	
					}
					if(is_o_oper(ch1))
					{
						if(ch1=='e')
						{
							x=OPND.pop();
							ch1=OPTR.pop();
							OPND.push(exp(x));						
						//	cout<<OPND.GetTop()<<endl;
						//	cout<<i<<endl;
							i--;
						}
						if(ch1=='s')
						{
							x=OPND.pop();
							ch1=OPTR.pop();
							OPND.push(sqrt(x));
							i--;
							//cout<<"结果："<<OPND.GetTop()<<endl; 
						}
						if(ch1=='l')
						{
							x=OPND.pop();
							ch1=OPTR.pop();
							OPND.push(log10(x));
							i--;
						}
					}
					switch(ch2)
						{
							case 'e':
								i+=2;
							case 'l':
								i+=4;
							case 's':
								i+=3;
							default:
								break;
						}
					//OPTR.push(str[i]);
					//cout<<OPND.GetTop()<<endl;		
					break;			
			}
			
		}

	}
	//OPTR.show();
	//OPND.show();
	cout<<"结果："<<OPND.GetTop()<<endl;
	//cout<<"2.1213"<<endl; 
	system("pause");
	return 0;
}

