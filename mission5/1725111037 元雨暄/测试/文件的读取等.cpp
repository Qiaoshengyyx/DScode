#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream infile,tobetran; 
    infile.open("F:\\各种作业\\数据结构\\第五次\\1725111037 元雨暄\\hfmTree.txt");   //将文件流对象与文件连接起来 
    tobetran.open("F:\\各种作业\\数据结构\\第五次\\1725111037 元雨暄\\ToBeTran.txt");
  //   assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

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
    tobetran.close();             //关闭文件输入流 

    infile.close();             //关闭文件输入流 
    tobetran.close();
	return 0;
 } 
