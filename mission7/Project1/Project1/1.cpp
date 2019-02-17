#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;
#define MAX 10
struct Node    //Node 每一本书为一个结点
{
	string name, writer;  //分别是书名，著者
	int quantity;   //现有库存
	string key;   //key为书的编号
	int sum; //总库存
	int height;   //高度
	Node * left;
	Node * right;
	Node(string key = "")  //初始化
	{
		this->key = key;
		this->height = 1;
		this->left = this->right = nullptr;
		this->name = "";
		this->quantity = 0;
		this->sum = 0;
		this->writer = "";
	}
};
class AVL  //用于记录各种书的数据
{
public:
	AVL();
	~AVL();
	void insert(string key, int n, string na, string p, int all); //用户输入,插入书籍
	Node * find(string key);
	void erase(string key);
	void print();
	void print2txt();
	void read_avl();
	void Indentation();
private:
	Node * header;  
	Node * ll_rotate(Node * y);
	Node * rr_rotate(Node * y);
	Node * lr_rotate(Node * y);
	Node * rl_rotate(Node * y);
	void destroy(Node * node);  
	int get_height(Node * node);
	int get_balance(Node * node);
	Node * insert_real(string key, Node * node, int n, string na, string p, int all);
	Node * find_real(string key, Node * node);
	Node * erase_real(string key, Node * node); //删除某个结点
	void in_order(Node * node);
	void print_txt(Node *node, ofstream &printavl);
	void printhelp(Node *node,string str);
};
Node * AVL::ll_rotate(Node * y)
{
	Node * x = y->left;
	y->left = x->right;
	x->right = y;
	y->height = max(get_height(y->left), get_height(y->right)) + 1;
	x->height = max(get_height(x->left), get_height(x->right)) + 1;
	return x;
}
Node * AVL::rr_rotate(Node * y)
{
	Node * x = y->right;
	y->right = x->left;
	x->left = y;
	y->height = max(get_height(y->left), get_height(y->right)) + 1;
	x->height = max(get_height(x->left), get_height(x->right)) + 1;
	return x;
}
Node * AVL::lr_rotate(Node * y)
{
	Node * x = y->left;
	y->left = rr_rotate(x);
	return ll_rotate(y);
}
Node * AVL::rl_rotate(Node * y)
{
	Node * x = y->right;
	y->right = ll_rotate(x);
	return rr_rotate(y);
}
void AVL::destroy(Node * node)
{
	if (node == nullptr)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
}
int AVL::get_height(Node * node)
{
	if (node == nullptr)
		return 0;
	return node->height;
}
int AVL::get_balance(Node * node)
{
	if (node == nullptr)
		return 0;
	return get_height(node->left) - get_height(node->right);
}
Node * AVL::insert_real(string key, Node * node,int n,string na,string p,int all)
{
	if (node == nullptr)
	{
		Node *b = new Node(key);
		b->quantity = n;
		b->name = na;
		b->sum = all;
		b->writer = p;
		return b;
	}
	if (key < node->key)
		node->left = insert_real(key, node->left,n,na,p,all);
	else if (key > node->key)
		node->right = insert_real(key, node->right,n, na, p, all);
	else  //已有图书则增加数量
	{
		node->quantity += n;
		return node;
	}	
	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	int balance = get_balance(node);
	if (balance > 1 && get_balance(node->left) > 0)// 左左失衡
		return ll_rotate(node);
	if (balance < -1 && get_balance(node->right) < 0)// 右右失衡
		return rr_rotate(node);
	if (balance > 1 && get_balance(node->left) < 0)// 左右失衡
		return lr_rotate(node);
	if (balance < -1 && get_balance(node->right) > 0)// 右左失衡
		return rl_rotate(node);
	return node;
}
Node * AVL::find_real(string key, Node * node)
{
	if (node == nullptr)
		return nullptr;
	if (key < node->key)
		return find_real(key, node->left);
	else if (key > node->key)
		return find_real(key, node->right);
	else
		return node;
}
Node * AVL::erase_real(string key, Node * node)
{
	if (node == nullptr)
		return node;
	if (key < node->key)
		node->left = erase_real(key, node->left);
	else if (key > node->key)
		node->right = erase_real(key, node->right);
	else
	{
		if (node->left && node->right)
		{
			Node * x = node->right;// 找到后继结点
			while (x->left)
				x = x->left;		
			node->key = x->key;// 后继直接复制	
			node->right = erase_real(x->key, node->right);// 转化为删除后继
		}
		else
		{
			Node * t = node;
			node = node->left ? node->left : node->right;
			delete t;
			if (node == nullptr)
				return nullptr;
		}
	}
	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	int balance = get_balance(node);
	if (balance > 1 && get_balance(node->left) >= 0) //注意等号
		return ll_rotate(node);
	if (balance < -1 && get_balance(node->right) <= 0) // 需要加等号
		return rr_rotate(node);
	if (balance > 1 && get_balance(node->left) < 0)
		return lr_rotate(node);
	if (balance < -1 && get_balance(node->right) > 0)
		return rl_rotate(node);
	return node;
}
void AVL::in_order(Node * node)
{
	if (node == nullptr)
		return;
	in_order(node->left);
	cout << node->key << " ";
	in_order(node->right);
}
AVL::AVL()
{
	header = new Node("1");
}
AVL::~AVL()
{
	destroy(header->left);
	delete header;
	header = nullptr;
}
void AVL::insert(string key, int n, string na, string p, int all)
{
	header->left = insert_real(key, header->left,n,na,p,all);
}
Node * AVL::find(string key)
{
	return find_real(key, header->left);
}
void AVL::erase(string key)
{
	header->left = erase_real(key, header->left);
}
void AVL::print() //中序遍历 打印平衡二叉树
{
	in_order(header->left);
	cout << endl;
}
void AVL::print_txt(Node *node, ofstream &printavl) //将平衡二叉树写入文件avl.txt
{
	if (node == nullptr)return;
	print_txt(node->left, printavl);
	printavl <<node->key << " " <<node->name<<" "<<node->writer<<" "<<node->quantity<<" "<<node->sum<<endl;
	print_txt(node->right, printavl);
}	
void AVL::print2txt()
{
	ofstream printavl("avl.txt");
	print_txt(header->left, printavl);
	printavl.close();
}
void AVL::read_avl()
{
	string s;
	int x;
	int i = 0;
	ifstream inval("avl.txt");;
	Node *d = new Node;
	while (!inval.eof())  //string类型:书号 书名 作者  int类型:现库存 总库存
	{
		if (i % 5 == 0)
		{
			inval >> s;
			d->key = s;
		}
		if (i % 5 == 1)
		{
			inval >> s;
			d->name = s;
		}
		if (i % 5 == 2)
		{
			inval >> s;
			d->writer = s;
		}
		if (i % 5 == 3)
		{
			inval >> x;
			d->quantity = x;
		}
		if (i % 5 == 4)
		{
			inval >> x;
			d->sum = x;
		}
		i++;
		if (i % 5 == 0 && d->name != "")
		{
			insert(d->key, d->quantity, d->name, d->writer, d->sum);// 书号、现有库存、书名、作者、总库存
		}
	}
	delete d;
	inval.close();
}
void AVL::printhelp(Node *node, string str)
{
	if (node==NULL)
		return;
	str += "		";
	printhelp(node->right, str);
	cout << str << node->key << "\n\n";
	printhelp(node->left, str);
}
void AVL::Indentation()
{
	string ss = "";
	printhelp(header->left, ss);
}
class Library
{
public:
	Library();
	void book_storing();
	void book_lending();
	void book_returning();
	void menu();
	void write();
	void read();
	void print_avl();
	void erase_book(string s);
private:
	struct record
	{
		string dayleft;
		string book_key;
		record *next;
	};
	struct borrower
	{
		string id;
		record *first;
	};
	AVL avl;
	borrower *br;
};
Library::Library()
{	
	br = new borrower[MAX];  
	for (int i = 0; i < MAX; i++)
	{
		br[i].id = "";
		br[i].first = new record;
	}
}
void Library::book_storing()
{
	string s,na,p;
	int n,all;
	cout << "输入书名：";
	cin >> na;
	cout << "输入著者：";
	cin >> p;
	cout << "输入新增图书的编号：ISBN ";
	cin >> s;
	cout << "输入现库存数量：";
	cin >> n;
	cout << "输入总库存量：";
	cin >> all;
	avl.insert(s,n, na, p, all);
	cout << "新增图书成功！\n";
	//avl.print();
}
void Library::book_lending()
{
	int str2num(string);
	string s1;
	int j=1;
	string id_num;
	cout << "输入要借阅的书的编号：ISBN ";
	cin >> s1;
	Node *find = avl.find(s1);
	if (!find)
	{
		cout << "没有这个编号的书！\n";
		return;
	}
	else
	{
		if (find->quantity <= 0)
		{
			cout << "库存数量不够了!借书失败。\n";
			return;
		}
		else
		{
			cout << "库存数量尚足\n输入图书证号：";
			cin >> id_num;
			br[0].id = id_num;
			int i = MAX;
			while (br[i].id != br[0].id)
				i--;
			if (i == 0)   //说明之前没有借阅记录
			{
				for (j = 1; j < MAX; j++)//!!!
				{
					if (br[j].id=="")
					{
						br[j].id = id_num;
						br[j].first->book_key = s1;
						br[j].first->dayleft = "30";
						br[j].first->next = NULL;
						avl.find(s1)->quantity--;
						break;
					}
				}
			}
			else //有借阅记录 (还要看有无超期未归还的书）
			{
				record *r =br[j].first;
				while (r->next)
				{
					r = r->next;
					if (str2num(r->dayleft) <= 0)
					{
						cout << "有超期未归还的书，借书失败，请先还书！\n";
						return;
					}
				}
				avl.find(s1)->quantity--;
				record *e = new record;
				e->book_key = s1;
				e->dayleft = "30";
				e->next = NULL;
				r->next = e;
			}
			cout << "借书成功！归还期限为30天。\n";
			return;
		}
	}
}
void Library::book_returning()
{
	string m;
	int i;
	string s2;
	record *c;
	cout << "输入图书证号：";
	cin >> m;
	cout << "输入要还的书的编号：ISBN ";
	cin >> s2;
	for (i = 1; i <MAX; i++)
	{
		if (br[i].id == m)
		{
			c = br[i].first;
			if (c->book_key == s2)
			{
				avl.find(s2)->quantity++;
				if (c->next)				
				{
					c = c->next;
					cout << "还书成功！\n";
					break;
				}
				else
				{
					cout << "还书成功！\n所有书清还完毕！注销借阅者的登记\n";
					br[i].id = "";
					br[i].first = NULL; //c=NULL;
					break;
				}
			}		
			while (c)
			{ //find 并且加上quantity
				if (c->next->book_key == s2)
				{
					record *link = c->next;
					c->next = link->next;        
					avl.find(s2)->quantity++;
					cout << "还书成功！\n";
					return;
				}
				else c = c->next;
			}
		}
	}
}
void Library::write()
{
	avl.print2txt();
	ofstream outbr("borrower.txt");
	for (int i = 1; i < MAX; i++)
	{
		if (br[i].id != "")
		{
			record *f;
			outbr <<br[i].id << " ";  //借书证号
			f = br[i].first;
			while (f)
			{
				outbr <<f->book_key <<" "<< f->dayleft <<" ";  //书号，归还期限 
				f = f->next;
			}
			outbr << "#"<<endl;
		}
	}
	outbr.close();
}
void Library::read()  //读入
{
	avl.read_avl();
	ifstream inbr;
	inbr.open("borrower.txt");
	int k = 1,step = 0;
	string g;
	while (!inbr.eof())
	{
		inbr >> g;
		br[k].id = g;
		cout << g<<" ";//
		record *rd = br[k].first;
		while (g != "#")
		{
			inbr >> g;
			if (rd->dayleft=="")
			{
				if (step == 0)
				{
					br[k].first->book_key = g;
					step++;
					cout << g << " ";//
				}
				else
				{
					br[k].first->dayleft = g;
					step = 0;
					cout << g << " ";//
				}
			}
			else
			{
				record *nex = new record;
				if (nex->dayleft == "")
				{
					if (step == 0)
					{
						nex->book_key = g;
						step++;
						cout << g << " ";//
					}
					else
					{
						nex->dayleft = g;
						step = 0;
						rd->next = nex;
						rd = rd->next;
						nex->next = NULL;
						cout << g << " ";//
					}
				}
			}
		}
		k++;
	}
	inbr.close();
}
void Library::print_avl()
{
	avl.Indentation();
}
void Library::erase_book(string s)
{
	avl.erase(s);
}
void Library::menu()
{
	char ch;
	string f;
	cout<<"==================================================================="<<endl;
	cout<<"\n*******************欢迎来到图书馆管理系统！**********************\n"<<endl;
	cout<<"==================================================================="<<endl;
	cout<<"操作如下：\n1、采编入库\n2、借阅\n3、归还\n4、将书库管理信息和借阅信息写入文件\n5、读取书库管理信息和借阅信息\n6、打印平衡二叉树\n7、删除书籍记录\n8、退出\n";
	ch = '0';
	while (ch!='4')
	{
		cout << "输入要进行的操作：";
		cin >> ch;
		switch (ch)
		{
		case '1':
			book_storing();
			continue;
		case '2':
			book_lending();
			continue;
		case '3':
			book_returning();
			continue;
		case '4':
			cout << "写入信息......\n";
			write();
			cout << "写入成功！\n";
			continue;
		case '5':
			cout << "读取信息......\n";
			read();
			cout << "读取成功！\n";
			continue;
		case '6':
			cout << "凹入表打印平衡二叉树：\n";
			print_avl();
			cout << endl;
			continue;
		case '7':
			cout << "输入需要删除记录的书的书号：ISBN ";
			cin >> f;
			erase_book(f);
			cout << "删除成功！\n";
			continue;
		case '8':
			cout << "退出成功！欢迎下次再来！" << endl;
			return;
		}
	}
}
int str2num(string str)
{
	int i,len = str.length(), num = 0;
	i = 0;
	while(i < len)
	{
		num = num * 10 + (int)(str[i] - '0');
		i++;
	}
	return num;
}
int main()
{
	Library lib;
	lib.menu();
	system("pause");
	return 0;
}
