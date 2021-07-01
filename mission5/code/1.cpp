#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;
#define MAX_LEN 9999
struct HTNode
{
	int weight,parent,lchild,rchild;
};
typedef char **HuffmanCode;
void Initialization(HTNode HT[],HuffmanCode &HC,char *&ch,int &n)
{
	void HuffmanTree(HTNode HT[],int w[],int n);
	void CreateHuffmanCode(HTNode HT[],HuffmanCode &HC,int n);
	int *p;
	int opt; //����Ĳ������	
	cout<<"1�������µĹ�������\n2����ȡ�ļ�������������\n���������";
	cin>>opt;
	if(opt==1)
	{
		ofstream myout("hfmTree.txt");	
		cout<<"����Ԫ�ظ�����";
		cin>>n;
		ch=new char[n];
		p=new int[n];
		cout<<"����ÿ��Ԫ�أ�(�ո�Ϊ�Ӻ�)";
		for(int i=0;i<n;i++)	
		cin>>ch[i];
		cout<<"����ÿ��Ԫ�ص�Ȩ�أ�";
		for(int i=0;i<n;i++)	
		cin>>p[i];
		cout<<"����ɹ�����ʼ������������\n";
		HuffmanTree(HT,p,n);  //�����������
		CreateHuffmanCode(HT,HC,n);  //������������� 
		myout<<left;
		myout<<"index\tword\tweight\tparent\tlchild\trchild\tcode\n";
		for(int i=0;i<2*n-1;++i)
		{
			if(i<n)
			myout<<i<<"\t"<<ch[i]<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<"\t"<<HC[i]<<endl;
			else
			{
				myout<<i<<"\t"<<"0\t"<<HT[i].weight<<"\t";
				myout<<HT[i].parent<<"\t";
				myout<<HT[i].lchild<<"\t";
				myout<<HT[i].rchild<<endl;
			}	
		}
		cout<<"�����ɹ������������͹��������뱣�����ļ�hfmTree.txt��\n";
		myout.close();
	}
	if(opt==2)
	{
		fstream myin;
		myin.open("hfm.txt");
		n=27;
		ch=new char[n];
		p=new int[n];
		int m1=0,m2=0;	
		while(!myin.eof())
		{
			if(m1<n)
			{
				myin>>ch[m1];
				m1++;
			} 
			else
			{
				myin>>p[m2];
				m2++;
			}
		}
		myin.close(); 
		ofstream myout("hfmTree.txt");
		HuffmanTree(HT,p,n);  //�����������
		CreateHuffmanCode(HT,HC,n);  //������������� 
		myout<<left;
		myout<<"index\tword\tweight\tparent\tlchild\trchild\tcode\n";
		for(int i=0;i<2*n-1;++i)
		{
			if(i<n)
			myout<<i<<"\t"<<ch[i]<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<"\t"<<HC[i]<<endl;
			else
			{
				myout<<i<<"\t"<<"0\t"<<HT[i].weight<<"\t";
				myout<<HT[i].parent<<"\t";
				myout<<HT[i].lchild<<"\t";
				myout<<HT[i].rchild<<endl;
			}	
		}
		cout<<"�����ɹ������������͹��������뱣�����ļ�hfmTree.txt��\n";
		myout.close();		
	}	
}
void CreateHuffmanCode(HTNode HT[],HuffmanCode &HC,int n)  //����������ʵ�� 
{
	int start,p,c;
	char *cd = new char[n];
	cd[n-1]='\0';
	for(int i=0;i<n;i++)
	{
		start=n-1;
		c=i;
		p=HT[i].parent;
		while(p!=-1)
		{
			--start;
			if(HT[p].lchild==c) cd[start]='0';
			else cd[start]='1';
			c=p;
			p=HT[p].parent;
		}
		HC[i]=new char[n-start];
		strcpy(HC[i],&cd[start]);
	}
	delete cd;
}
void Select(HTNode HT[],int sum,int &s1,int &s2)
{
	int i,j;
	for(i=0;i<sum;i++)
	{
		if(HT[i].parent==-1)
		{
			s1=i;     //��ʼ��s1
			break; 
		}
	}
	for(i=0;i<sum;i++)
	{
		if(HT[i].parent==-1 && HT[s1].weight>HT[i].weight)	s1=i;
	}
	for(j=0;j<sum;j++)
	{
		if(HT[j].parent==-1 && j!=s1)
		{
			s2=j;
			break;
		}
	}
	for(j=0;j<sum;j++)
	{
		if(HT[j].parent==-1 && HT[s2].weight>HT[j].weight&& j!=s1)	s2=j;
	}
}
void HuffmanTree(HTNode HT[],int w[],int n)
{
	for(int i=0;i<2*n-1;i++)
	{
		HT[i].weight=0;
		HT[i].parent=-1;
		HT[i].lchild=-1;
		HT[i].rchild=-1;	
	}
	for(int i=0;i<n;i++)
		HT[i].weight=w[i];
	for(int j=n;j<2*n-1;j++)
	{
		int s1,s2;
		Select(HT,j,s1,s2);
		HT[s1].parent=j;
		HT[s2].parent=j;
		HT[j].lchild=s1;
		HT[j].rchild=s2;
		HT[j].weight=HT[s1].weight+HT[s2].weight;
	}
}
void encoding(HTNode HT[],HuffmanCode &HC,char *ch,int n)   
{
	char s;
	string ss="";
	char *c=new char[9999];
	int i=0; 
	ifstream ToBeTran;
	ofstream CodeFile("CodeFile.txt");
	ToBeTran.open("ToBeTran.txt");
	cout<<"����������ļ�ToBeTran.txt�����б���\n";
	while (!ToBeTran.eof()) 
	{
		ToBeTran>>s;
		c[i]=s; //��� 
		i++;
	}
	i=0;
	while(c[i+1]!='\0')
	{
		for(int j=0;j<n;j++)
		{
			if(c[i]==ch[j])
			{
				ss=ss+HC[j];
				i++;
				break;
			}
		}
	} 
	cout<<"����Ϊ��"<<ss;
	cout<<"\n����ɹ���\n�������������ļ�CodeFile.txt��";
	CodeFile<<ss;
	CodeFile.close();
	cout<<"����ɹ���\n";		
} 
void decoding(HTNode HT[],char *ch,char *&b,int n)   //b[] ������¼������ַ� 
{
	cout<<"����������ļ�CodeFile.txt��������\n";
	char s;
	int i=0;
	string ss="";
	ifstream CodeFile;
	char *d=new char[999];
	CodeFile.open("CodeFile.txt");
	while (!CodeFile.eof()) 
	{
		CodeFile>>s;
		d[i]=s;
		i++;
	}
	i=0;
	int p=2*n-2;  //������±� 
	int k=0;
	for(i=0;d[i+1]!='\0';i++)
	{
		if(d[i]=='0')p=HT[p].lchild;
		if(d[i]=='1')p=HT[p].rchild;
		if(HT[p].lchild==-1 && HT[p].rchild==-1)
		{
			b[k++]=ch[p];	
			p=2*n-2;
		}
	} 
	b[k]='\0'; //���������TextFile
	k=0;
	ofstream TextFile("TextFile.txt");
	cout<<"����Ϊ��";
	while(b[k]!='\0')
	{
		cout<<b[k];
		TextFile<<b[k];
		k++;
	}
	TextFile.close(); 
	cout<<"\n�ɹ�����������ļ�TextFile.txt��\n"; 
}
void print() //ӡ�����ļ���Print�������ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin�С�
{
	char *q=new char[MAX_LEN];
	char in;
	ifstream CodeFile;
	ofstream CodePrin("CodePrin.txt");
	CodeFile.open("CodeFile.txt");
	int i=0,count=0;
	while(!CodeFile.eof())
	{
		CodeFile>>in;
		q[i]=in;
		i++;
	}
	i=0;
	cout<<"��ӡCodeFile���ݣ�\n"; 
	while(q[i+1]!='\0')
	{
		cout<<q[i];
		CodePrin<<q[i];
		count++;
		i++;
		if(count==50)
		{
			cout<<endl;
			count=0;
		}
	}
	cout<<"\n�ɹ�������д���ļ�CodePrin.txt��\n";
} 
void printhelp(HTNode HT[],int index,string ss,char *ch,ofstream &TreePrin,int n)
{
	ss+="	";
	if(HT[index].lchild==-1 && HT[index].rchild==-1)
	{
		//cout<<ss<<HT[index].weight<<endl;
		if(index>n)
		{
			cout<<ss<<"#"<<endl;
			TreePrin<<ss<<"#"<<endl;
		}
		else
		{
			cout<<ss<<ch[index]<<endl;
			TreePrin<<ss<<ch[index]<<endl;
		  }  
		return;
	}
	else
	{
		printhelp(HT,HT[index].lchild,ss,ch,TreePrin,n);
	//	cout<<ss<<HT[index].weight<<endl;
		if(index>n)
		{
			cout<<ss<<"#"<<endl;
			TreePrin<<ss<<"#"<<endl;
		}
		else 
		{
			cout<<ss<<ch[index]<<endl;
			TreePrin<<ss<<ch[index]<<endl;
		 } 
		printhelp(HT,HT[index].rchild,ss,ch,TreePrin,n);
	}
} 
void treeprinting(HTNode HT[],int n,char *ch)  //ӡ����������Tree printing�����������ڴ��еĹ���������ֱ�۵ķ�ʽ�����������ʽ����ʾ���ն��ϣ�ͬʱ�����ַ���ʽ�Ĺ�������д���ļ�TreePrint��
{
	ofstream TreePrin("TreePrin.txt");//
	void printhelp(HTNode HT[],int index,string ss,char *ch,ofstream &TreePrin,int n);
	string ss="";
	int index=2*n-2;  //index�����һ����㿪ʼ 
	cout<<"��ӡ����������Ȩֵ����\n";
	printhelp(HT,index,ss,ch,TreePrin,n);
} 
void menu()
{
	char g;   //g��ÿ������Ĳ��� 
	int n;    //n��Ԫ���ܸ��� 
	char *ch;  //ch�Ƕ�����ַ� ����+ a b c d e f g�� 
	HuffmanCode HC=new char*[MAX_LEN]; 
	HTNode *HT=new HTNode[MAX_LEN];
	char *b=new char[MAX_LEN];
	cout<<"�˵���\n";
	cout<<"I����ʼ����Initialization��\nE�����루Encoding��\nD�����루Decoding��\nP��ӡ�����ļ���Print��\nT��ӡ����������Tree printing��\nQ���˳�(Quit)\n";
	while(true)
	{
		cout<<"\n��������Ҫʵ�ֵĲ�����";
		cin>>g;
		switch(g)
		{
			case 'I':	
				Initialization(HT,HC,ch,n);
				break;
			case 'E':
				encoding(HT,HC,ch,n);
				break;
			case 'D':
				decoding(HT,ch,b,n);
				break;
			case 'P':
				print();
				break;
			case 'T':
				treeprinting(HT,n,ch);
				break;
			case 'Q':
				cout<<"�˳��ɹ���\n";
				exit(0);
		} 
	}
	return;
 } 
int main()
{
	void encoding(HTNode HT[],HuffmanCode &HC,int n);
	void menu();
	void encoding(HTNode HT[],HuffmanCode &HC,int n);
	void Initialization();
	menu(); 
	return 0;
}