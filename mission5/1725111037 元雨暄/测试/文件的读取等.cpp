#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream infile,tobetran; 
    infile.open("F:\\������ҵ\\���ݽṹ\\�����\\1725111037 Ԫ����\\hfmTree.txt");   //���ļ����������ļ��������� 
    tobetran.open("F:\\������ҵ\\���ݽṹ\\�����\\1725111037 Ԫ����\\ToBeTran.txt");
  //   assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

    string s,t;
  /*  while(getline(infile,s))   
    cout<<s<<endl;
    while(getline(tobetran,t))
    {
    	cout<<t<<endl;
	}*/
    char c;
    while (!tobetran.eof())
    {
        tobetran >> c;
        cout<<c<<endl;
    }
    tobetran.close();             //�ر��ļ������� 

    infile.close();             //�ر��ļ������� 
    tobetran.close();
	return 0;
 } 
