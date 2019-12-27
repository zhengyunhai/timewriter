#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<ctime>
#include<direct.h>
#include<windows.h>
const char *ver = "1.4.0";
using namespace std;

typedef struct data
{
	char time[13];
	char info[200];//字数限制100？？？
	data* next;
}data;

typedef struct wlp
{
	char name[20];
	char today[13];
	int b;//b=0,普通日志,b=1,开发日志
	int count;//计数该分支上节点个数，以确定该分支何时结束
	struct data lpdata;
	wlp* next;
}wlp;

typedef struct namelink {
	char name[20];
	namelink* next;
}namelink;

char* getday();//获取当前日期
char* gettime();//获取当前时间
void initnode(struct wlp** head, int i);//节点初始化
int addinfo(struct wlp* node);
void adddata(struct wlp** library, char* name,char* date,int b);
void searchdata(struct wlp* wl, char* date);
void freed(struct wlp* wl);
void showinfo(struct wlp* node);
void freei(struct data* node);
void f0(char* ti);//填充0
void outlist();//输出指令列表
void delnode(struct wlp** node,char* date);//删除节点
void sampleinfo(struct wlp* node);//简略信息
void exportlog(struct wlp* node,char* name);//导出node链表中名为name的节点到同名txt中
void headlist();
int is_node(struct wlp* node, char* name);//返回链表中与name匹配的节点个数
void delall(struct wlp* node);//删除全部节点
void menu(struct wlp** namelink, struct wlp* node);//将node链表中节点按顺序保存首次出现的节点名到namelink中
void copynode();

void f0(char* ti)//填充0
{
	char temp[8]="0";
	strcat_s(temp,sizeof(temp),ti);
	strcpy_s(ti, sizeof(temp), temp);
}

int addinfo(struct wlp* node)
{
	char* tt ;
	struct data* temp;
	struct data *endn;
	char temp2[100] = { 0 };
	endn = &(node->lpdata);
sr:	cout <<endl<< "AddInfo>>";
	cin >> temp2;
	while(strcmp(temp2, "endw")) 
	{
		temp = (struct data*)malloc(sizeof(struct data));
		if (temp == NULL) { cout << "Memory allocation failed." << endl; exit(1); }
		tt = gettime();
		strcpy_s(temp->time, 13, tt);
		temp->next = NULL;
		strcpy_s(temp->info, strlen(temp2)+1, temp2);

		while (endn->next != NULL)
		{
			endn = endn->next;
		}
		endn->next = temp;
		node->count++;
		goto sr;
	}
	return 0;
}

char* getday()//获取当前日期
{
	char temp1[13] = {0};
	char temp2[8] = {0};
	char temp3[8] = {0};
	char* r;
	r = (char*)malloc(sizeof(temp1));
	if (r == NULL) { cout << "Memory allocation failed." << endl; exit(1); }
	time_t sec = time(0);
	struct tm now;
	localtime_s(&now, &sec);
	_itoa_s(now.tm_year + 1900, temp1, 10);
	_itoa_s(now.tm_mon + 1, temp2, 10);
	if (now.tm_mon < 10) f0(temp2);
	_itoa_s(now.tm_mday, temp3, 10);
	if (now.tm_mday < 10) f0(temp3);
	strcat_s(temp1, sizeof(temp1), temp2);
	strcat_s(temp1, sizeof(temp1), temp3);//temp1返回日期
	strcpy_s(r, 13, temp1);
	return r;
}

char* gettime()//获取当前时间
{
	char temp1[13] = { 0 };
	char temp2[8] = { 0 };
	char temp3[8] = { 0 };
	char temp4[13] = "[";
	char* r;
	r = (char*)malloc(sizeof(temp1));
	if (r == NULL) { cout << "Memory allocation failed." << endl; exit(1); }
	time_t sec = time(0);
	struct tm now;
	localtime_s(&now, &sec);
	_itoa_s(now.tm_hour, temp1, 10);
	if (now.tm_hour < 10) f0(temp1);
	_itoa_s(now.tm_min, temp2, 10);
	if (now.tm_min < 10) f0(temp2);
	strcat_s(temp1, sizeof(temp1), ":");
	strcat_s(temp1, sizeof(temp1), temp2);
	strcat_s(temp4, sizeof(temp4), temp1);
	strcat_s(temp4, sizeof(temp4), "]");
	strcpy_s(r, 13, temp4);
	return r;
}

void initnode(struct wlp** head,int i)//未完成，i=1时？
{
	struct wlp* r = *head;
	if (i == 0)
	{
		strcpy_s(r->name, 20, "LOGNAME");
		strcpy_s(r->today, 13, "LOGHEAD");
		r->count=1;
		r->b = 0;
		strcpy_s(r->lpdata.time, 13, "LOGTIME");
		strcpy_s(r->lpdata.info, 13, "LOGINFO");
		r->next = NULL;
		r->lpdata.next = NULL;
	}
	if (i == 1)
	{
		strcpy_s(r->name, 20, "LOGNAME");
		strcpy_s(r->today, 13, "LOGHEAD");
		r->count=1;
		r->b = 0;
		strcpy_s(r->lpdata.time, 13, "LOGTIME");
		strcpy_s(r->lpdata.info, 13, "LOGINFO");
		r->next = NULL;
		r->lpdata.next = NULL;
	}
}

int loadfile(char* path,struct wlp **wl)//假定文件存在
{
	ifstream inf;
	char temp1[30];//缓存最先读入的name
	struct wlp* lend,*head;
	lend = NULL;
	head = (struct wlp*)malloc(sizeof(struct wlp));
	if (head == NULL) { cout << "Memory allocation failed." << endl; exit(1); }
	initnode(&head,0);
	*wl = head;
	lend = head;
	inf.open(path);
	if (!inf.is_open()) { return 2; }
	else
	{
		while (inf >> temp1)//读入链表
		{
			struct wlp* temp2;
			struct data* tempend1,*nn;
			int i = 2;
			tempend1 = NULL;
			nn = NULL;
			temp2 = (struct wlp*)malloc(sizeof(struct wlp));
			if (temp2 == NULL) { cout << "Memory allocation failed." << endl; exit(1); }
			strcpy_s(temp2->name,strlen(temp1)+1 , temp1);
			inf >> temp2->today;
			inf >> temp2->b;
			inf >> temp2->count;
			inf >> temp2->lpdata.time;
			inf >> temp2->lpdata.info;
			temp2->lpdata.next = NULL;
			temp2->next = NULL;
			lend->next = temp2;
			lend = temp2;
			tempend1 = &(temp2->lpdata);
			while (i <= temp2->count)
			{
				nn = (struct data*)malloc(sizeof(struct data));
				if (nn == NULL) { cout << "Memory allocation failed." << endl; exit(1); }
				inf >> nn->time;
				inf >> nn->info;
				nn->next = NULL;
				tempend1->next = nn;
				tempend1 = nn;
				i++;
			}
		}
	}
	inf.close();
	return 0;
}

void outtofile(char*path,struct wlp* wl)
{
	ofstream outf;
	struct wlp* wtemp = wl;
	struct wlp* lend;
	struct data* temp = NULL;
	lend = wtemp->next;//第一个节点
	if (wtemp == NULL) { cout << "No data to save!" << endl; }
	else 
	{
		cout << "Saving..." << endl;
		outf.open(path);
		while (lend != NULL)
		{
			outf << lend->name<<" "<<lend->today << " " << lend->b<<" "<<lend->count << endl<< lend->lpdata.time << endl<< lend->lpdata.info << endl;
			temp =&(lend->lpdata);
			while (temp->next!= NULL)
			{
				temp = temp->next;
				outf << temp->time << endl << temp->info << endl;	
			}
			lend = lend->next;
		}
		outf.close();
		cout << "Save finished！" << endl;
	}
}

void adddata(struct wlp** library, char* name,char* date,int b)//new version//可以继续优化
											  //原理过程说明：查看第一个节点是否为目标节点，是则在其上添加数据，否则新建节点并插入，即只检测第一个节点，并非遍历整个链表
{
	char* td=getday() ;
	char* tt;
	struct wlp* book, * temp, * end, * head, * head1;//定义结构体指针 ，局部变量 
	end = *library;
	head= *library;
	book = NULL;
	temp = NULL;
	head1 = NULL;
	//搜索节点（只看第一个节点）（头节点后的第一个节点）	
		if (*library == NULL)//空链表 ，只有空的头指针//由于loadfile()的存在，不可能为空链表，至少有一个头节点
		{
			book = (struct wlp*)malloc(sizeof(struct wlp));//分配空间 ，注意类型转换 
			if (book == NULL)//分配失败 
			{
				printf("Memory allocation failed.\n");
				exit(1);
			}
			strcpy_s(book->name, 20, name);
			strcpy_s(book->today, 13, td);
			book->b = b;
			book->count = 1;
			cout << endl<<"AddInfo>>" ;
			cin >> book->lpdata.info;
			if (!strcmp(book->lpdata.info, "endw"))
			{
				free(book);
			}
			else
			{
				tt = gettime();
				strcpy_s(book->lpdata.time, 13, tt);
				book->lpdata.next = NULL;
				book->next = NULL;
				addinfo(book);
				head1 = (struct wlp*)malloc(sizeof(struct wlp));
				if (head1 == NULL) { cout << "Memory allocation failed." << endl; exit(1); }
				initnode(&head1, 0);
				*library = head1;//头节点
				head1->next = book;//注意book是指针，这里是传递地址 
			}
		}
		else//非空链表 ,有头节点，头插法
		{
			end = end->next;//指向第一个节点
			if (end == NULL)//第一个节点为空，只有一个头节点
			{
				book = (struct wlp*)malloc(sizeof(struct wlp));//分配空间 ，注意类型转换 
				if (book == NULL) {printf("Memory allocation failed.\n");exit(1);}
				strcpy_s(book->name, 20, name);
				strcpy_s(book->today, 13, td);
				book->b = b;
				book->count = 1;
				cout << endl<<"AddInfo>>";
				cin >> book->lpdata.info;
				if (!strcmp(book->lpdata.info, "endw"))
				{
					free(book);
				}
				else
				{
					tt = gettime();
					strcpy_s(book->lpdata.time, 13, tt);
					book->lpdata.next = NULL;
					book->next = NULL;
					addinfo(book);
					temp = head->next;
					head->next = book;
					book->next = temp;
				}	
			}
			else if (!strcmp(end->name, name)&&!strcmp(end->today,date))//目标节点已存在,即第一个节点为目标节点，日志本身是以日期为名，故可以用name判断，但开发日志以项目为名，同时以日期进行判断
			{
				addinfo(end);
			}
			else//目标节点不存在，即第一个节点不是目标节点
			{
				book = (struct wlp*)malloc(sizeof(struct wlp));//分配空间 ，注意类型转换 
				if (book == NULL)//分配失败 
				{
					printf("Memory allocation failed.\n");
					exit(1);
				}
				strcpy_s(book->name, 20, name);
				strcpy_s(book->today, 13, td);
				book->b = b;
				book->count = 1;
				cout << endl<<"AddInfo>>";
				cin >> book->lpdata.info;
				if (!strcmp(book->lpdata.info, "endw"))
				{
					free(book);
				}
				else
				{
					tt = gettime();
					strcpy_s(book->lpdata.time, 13, tt);
					book->lpdata.next = NULL;
					book->next = NULL;
					addinfo(book);
					temp = head->next;
					head->next = book;
					book->next = temp;
				}		
			}
		}
	
}

void showinfo(struct wlp* node)
{
	struct data* end;
	cout<< node->today << endl;
	end = &(node->lpdata);
	while (end!=NULL)
	{
		cout << " "<<end->time << " " << end->info << endl;
		end = end->next;
	}
}

void searchdata(struct wlp* wl,char* name)
{
	struct wlp* temp;
	int count = 0;
	temp = wl;
	if (temp == NULL) cout << "Empty Data." << endl;
	else
	{
		cout << endl;
		while (temp!= NULL)
		{
			if (!strcmp(temp->name, name))
			{
				showinfo(temp);
				count++;
			}
			temp = temp->next;
		}
		if (count == 0) cout << "There's no data for '" << name <<"'"<< endl;
	}
}

void freei(struct data* node)
{
	struct data* temp=NULL;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp);
	}
}

void freed(struct wlp* wl)
{
	struct wlp* temp=NULL;
	struct data* temp2 = NULL;
	while (wl != NULL)
	{
		temp = wl; 
		temp2 = wl->lpdata.next;
		wl = wl->next;		
		freei(temp2);	
		free(temp);
	}
}

void delnode(struct wlp** node, char* name)//注意这会删除与name同名的所有节点
{
	struct wlp* temp;
	struct wlp* head;
	int i = 0;
	head = *node;
	temp = NULL;

	if (*node == NULL) {
		cout << "No data for '" << name <<"'"<< endl;
	}
	else
	{
		temp = head;
		head = head->next;
		if (head == NULL) {//第一个节点为空
			cout << "No data for '" << name <<"'"<< endl;
		}
		else
		{
			while (head != NULL)
			{
				if (strcmp(head->name, name))
				{
					temp = head;
					head = head->next;
				}
				else
				{
					temp->next = head->next;
					freei(head->lpdata.next);
					free(head);
					i = i+1;
					head = temp->next;
				}

			}
			
		}	
	}
//shuchu:
	if (i == 1)cout <<i<<" Data node '"<< name << "' has been deleted!" << endl;
		else if (i > 1)cout << i << " Data nodes '" << name << "' have been deleted!" << endl;
			 else cout << "No such data '" << name <<"'"<< endl;
}

void delall(struct wlp* node)
{
	struct wlp* temp;
	temp = node->next;
	node->next = NULL;
	freed(temp);
}

void sampleinfo(struct wlp* node)
{
	if (node->count != 0)
	{
		int i=0;
		int N;
		char temp[21] = { 0 };
		if (strlen(node->lpdata.info) >= 12)
		{
			N = 12;
		}
		else N = strlen(node->lpdata.info);

		for (i = 0; i < N;i++)
		{
			temp[i] = node->lpdata.info[i];
		}
		if(node->count>1||N==12)strcat_s(temp, sizeof(temp), " ... ...");
		
		cout << temp;
	}
	cout << endl;
}

int is_node(struct wlp* node,char* name)
{
	struct wlp* temp;
	temp = node;
	int i = 0;
	while (temp != NULL)
	{
		if (!strcmp(temp->name, name))
		{
			i++;
		}
		temp = temp->next;
	}
	return i;
}

void exportlog(struct wlp* node,char* name)
{
	char path[50]= ".\\data\\";
	strcat_s(path, 50, name);
	strcat_s(path, 50, ".txt");
	ofstream outf;
	if(!is_node(node,name))
	{
		cout << "No data can be exported." << endl;
	}
	else
	{
		outf.open(path, ios::app);
		struct wlp* temp;
		struct data* end;
		temp = node->next;
		while (temp != NULL)
		{
			if (!strcmp(temp->name, name))
			{
				outf << temp->today << endl;
				end = &(temp->lpdata);
				while (end != NULL)
				{
					outf << end->time << " " << end->info << endl;
					end = end->next;
				}
			}
			temp = temp->next;
		}
		outf.close();
		cout << "Data '" << name << "' has been exported in TXT.'" << endl;
	}
}

void outlist()
{
	cout << "  " << "                                         " << getday() << " " << gettime() << endl;
	cout << "  " << "—————————————————————————————" << endl
		<< "  " << "|                    * Command list *                    |" << endl
		<< "  " << "—————————————————————————————" << endl

		<< "  " << "—————————————————————————————" << endl
		<< "  " << "|     -help                     -show command list       |" << endl
		<< "  " << "—————————————————————————————" << endl
		<< "  " << "|     list [log/prog/plan]    -show logmenu              |" << endl
		<< "  " << "—————————————————————————————" << endl
		<< "  " << "|     log                     -to start writing a log    |" << endl
		<< "  " << "|     prog [progname]         -to start writing a proglog|" << endl
		<< "  " << "|     endw                    -to finish writing the log |" << endl
		<< "  " << "|     cl [name]               -check log/prog            |" << endl
		<< "  " << "—————————————————————————————" << endl
		<< "  " << "|     plan [name]             -to start writing a plan   |" << endl
		<< "  " << "|     endw                    -to finish writing the plan|" << endl
		<< "  " << "|     cp [date/name]          -check plan in date        |" << endl
		<< "  " << "—————————————————————————————" << endl
		<< "  " << "|     del [log/plan] [name]   -delete data               |" << endl
		<< "  " << "|     delall [log/plan]       -delete data               |" << endl
		<< "  " << "—————————————————————————————" << endl
		<< "  " << "|     expd [name]             -export log data           |" << endl
		<< "  " << "|     save                    -save data                 |" << endl
		<< "  " << "|     save [log/plan]         -save data                 |" << endl
		<< "  " << "|     exit                    -save and exit             |" << endl
		<< "  " << "—————————————————————————————" << endl;
	/*	<< "  " << "*           DO NOT use 'exit' before you really          *" << endl
		<< "  " << "*               want to FINISH this program.             *" << endl
		<< "  " << "—————————————————————————————" << endl;
	*/
}

void headlist()
{
	cout << "  " << "———————————————————————————" << endl
		<< "  " << "|                     Time Writer                    |" << endl
		<< "  " << "———————————————————————————" << endl
		<< "  " << "|                    Version "<<ver<<"                   |" << endl
		<< "  " << "———————————————————————————" << endl
		<< "  " << "|   https://github.com//zhengyunhai/timewriter.git   |" << endl
		<< "  " << "———————————————————————————" << endl;
}

void menu(struct wlp** namelink, struct wlp* node)
{
	struct wlp* head, * temp,*temp1;
	head = node->next;
	*namelink = (struct wlp*)malloc(sizeof(struct wlp));
	initnode(namelink, 0);
	temp =* namelink;//头节点不存信息
	while (head != NULL)
	{
		if (!is_node(*namelink, head->name))
		{
			temp1 = (struct wlp*)malloc(sizeof(struct wlp));
			initnode(&temp1, 0);
			strcpy_s(temp1->name, sizeof(head->name), head->name);
			temp1->b = head->b;		
			strcpy_s(temp1->today, sizeof(head->today), head->today);
			temp1->count = head->count;
			strcpy_s(temp1->lpdata.info, sizeof(head->lpdata.info), head->lpdata.info);
			temp->next = temp1;
			temp = temp1;
		}
		head = head->next;
	}

}

void copynode()
{

}

int main(void)
{
	ofstream outf;
	ifstream inf;
	char* td = getday();
	char* tt = gettime();
	cout <<"["<< td<<"] "<<tt << endl;
	char path1[] = ".\\data\\log";
	char path2[] = ".\\data\\plan";
	//command list
	{
		headlist();
	//clist:outlist();
	}
	struct wlp* wl = NULL;
	struct wlp* lend;
	struct wlp* pend;
	struct wlp* wp = NULL;
	
	lend = wl;
	pend = wp;
	//读入文件默认存在
	//载入日志文件
	if(loadfile(path1,&wl)==2)cout<<"打开日志文件失败！已新建。"<<endl;
	//载入计划文件
	if (loadfile(path2, &wp) == 2)cout << "打开计划文件失败！已新建。" << endl;

	char command[10] = { 0 };
shuru:cout << endl<<"TimeWriter>> ";
	  cin >> command;
	  char command1[13] = { 0 };
	  char command2[13] = { 0 };
	  char command3[2] = { 0 };
	  struct wlp* namelink = NULL;
	  char tc[1] = {0};
	  tc[0] = getchar();
	  //指令匹配部分
	  {
		  if (!strcmp(command, "list"))//列出项目名
		  {
			  struct wlp* temp=NULL;
			  if (tc[0] == '\n')
			  {
				  cout << "Need more arguments!" << endl;
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  if (!strcmp(command1, "log"))//列出普通日志目录
					  {
						  menu(&namelink, wl);
						  if (wl == NULL)cout << "No logs!" << endl;
						  else {
							  temp = wl;
							  temp = temp->next;
							  if (temp == NULL)
							  {
								  cout << "No logs!" << endl;
							  }
							  else
							  {							  
								  temp = namelink->next;
								  cout << "  " << setw(20) << setiosflags(ios::left) << "LogName"; cout << "  " << setw(10) << "LogDate" << "  " << "SampleInfo" << endl<<endl;
								  while (temp != NULL)
								  {
									  if (temp->b == 0)
									  {
										  cout << "  " << setw(20) << setiosflags(ios::left) << temp->name; cout << " " << "[" << temp->today << "]" << "   ";
										  sampleinfo(temp);
									  }
									  temp = temp->next;
								  }
							  }
						  }
						  freed(namelink);
						  goto shuru;
					  }
					  if (!strcmp(command1, "prog"))//列出开发日志目录
					  {
						  menu(&namelink, wl);
						  if (wl == NULL)cout << "No prog!" << endl;
						  else {
							  temp = wl;//prog与log存在同一链表中
							  temp = temp->next;
							  if (temp == NULL)
							  {
								  cout << "No prog!" << endl;
							  }
							  else
							  {
								  temp = namelink->next;
								  cout << "  " << setw(20) << setiosflags(ios::left) << "ProgName"; cout << "  " << setw(10) << "ProgDate" << "  " << "SampleInfo" << endl<<endl;
								  while (temp != NULL)
								  {
									  if (temp->b)
									  {
										  cout << "  " << setw(20) << setiosflags(ios::left) << temp->name; cout << " " << "[" << temp->today << "]" << "   ";
										  sampleinfo(temp);
									  }
									  temp = temp->next;
								  }
							  }
						  }
						  freed(namelink);
						  goto shuru;
					  }
					  if (!strcmp(command1, "plan"))//列出计划目录
					  {
						  menu(&namelink, wp);
							if (wp == NULL)cout << "No plans!" << endl;
							else
							{
								temp = wp;
								temp = temp->next;
								if (temp == NULL)
								{
									cout << "No plans!" << endl;
								}
								else
								{
									temp = namelink->next;
									cout << "  " << setw(20) << setiosflags(ios::left) << "PlanName"; cout << "  " << setw(10) << "PlanDate" << "  " << "SampleInfo" << endl<<endl;
									while (temp != NULL)
									{
										cout << "  " << setw(20) << setiosflags(ios::left) << temp->name; cout << " " << "[" << temp->today << "]" << "   ";
										sampleinfo(temp);
										temp = temp->next;
									}
								}
							}
							freed(namelink);
							goto shuru;
					  }
					
					  else {
						  cout << "Wrong argument!" << endl;
						  goto shuru;
					  }
					  	  
				  }
			  }
		  }

		  if (!strcmp(command, "log"))//写日志
		  {
			  if (tc[0] == '\n')
			  {
				  adddata(&wl, td,td,0);//logend包含在其中
				  goto shuru;
			  }
			  else 
			  {
				  while (tc[0] != '\n')//吃掉多余的参数
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument!" << endl;
				  goto shuru;
			  }
		  }

		  if (!strcmp(command, "prog"))
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "No argument!" << endl;
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  adddata(&wl, command1,td,1);
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "plan"))//写计划
		  {
			  if (tc[0] == '\n')//plan
			  {
				  adddata(&wp, td,td,0);
				  goto shuru;
			  }
			  else//plan [date]
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  adddata(&wp, command1,td,0);
					  goto shuru;
				  }		  
			  }	  
		  }

		  if (!strcmp(command, "cl"))//check logs in date
		  {
			  if (tc[0] == '\n')
			  {
				  //cout << td <<":"<< endl;
				  searchdata(wl, td);
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  //cout << command1 << ":" << endl;
					  searchdata(wl, command1);
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "cp"))//check plan in date
		  {
			  if (tc[0] == '\n')
			  {
				  searchdata(wp, td);
				  goto shuru;
			  }
			  else
			  {
				  cin>>command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  searchdata(wp, command1);
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "del"))//删除功能
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "No argument!" << endl;
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] == '\n')
				  {
					  cout << "Need more arguments!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  cin>>command2;
					  tc[0] = getchar();
					  if (tc[0] != '\n')
					  {
						  cout << "Too many argument!" << endl;
						  while (tc[0] != '\n')//吃掉多余的参数
						  {
							  tc[0] = getchar();
						  }
						  goto shuru;
					  }
					  else
					  {
						  cout << command1 << " in " << command2 << " will be deleted.Countinue?(Y/N):";
						  cin>>command3;
						  if (!strcmp(command3, "y") || !strcmp(command3, "Y"))
						  {
							  if (!strcmp(command1, "log")||!strcmp(command1,"prog"))
							  {
								  delnode(&wl, command2);
							  }
							  else if (!strcmp(command1, "plan"))
							  {
								  delnode(&wp, command2);
							  }
							  else cout << "Wrong argument!" << endl;
							  goto shuru;
						  }
						  else goto shuru;
						  
					  }
					  
				  }
			  }
		  }	

		  if (!strcmp(command, "delall"))
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "No argument!" << endl;
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  cout << "Too many argument!" << endl;
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  goto shuru;
				  }
				  else
				  {
					  cout << "ALL "<<command1<<" WILL BE DELETED.COUNTINUE?(Y/N)";
					  cin >> command2;
					  if (!strcmp(command2, "y") || !strcmp(command2, "Y"))
					  {
						  if (!strcmp(command1, "log"))	{ delall(wl); cout << "ALL " << command1 << " have been DELETED."<<endl;  }
						  else if (!strcmp(command1, "plan")) { delall(wp); cout << "ALL " << command1 << " have been DELETED." << endl;}
						  else cout << "Wrong Argument!" << endl;
					  }				  
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "expd"))//暂时只用于导出开发日志
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "No argument." << endl; 
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  exportlog(wl, command1);
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "save"))
		  {
			  if (tc[0] == '\n')
			  {
				  outtofile(path1, wl);
				  outtofile(path2, wp);
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//吃掉多余的参数
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  if (!strcmp(command1, "log")) { outtofile(path1, wl); }
					  else if (!strcmp(command1, "plan")) { outtofile(path2, wp); }
					  else cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "-help"))
		  {
			  if (tc[0] == '\n')
			  {
				  outlist();
				  goto shuru;
			  }
			  else
			  {
				  while (tc[0] != '\n')//吃掉多余的参数
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument!" << endl;
				  goto shuru;
			  }
		  }

		  if (!strcmp(command, "exit")) //退出程序
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "LAYOUT" << endl;
				  //保存
				  outtofile(path1, wl);
				  freed(wl);//cout << "释放完毕" << endl;
				  outtofile(path2, wp);
				  freed(wp);//cout << "释放完毕" << endl;
				  free(tt); //cout << "释放完毕" << endl;
				  free(td);
				 // freed(namelink); cout << "释放完毕" << endl;
				  Sleep(100);
				  return 0;
			  }
			  else
			  {
				  while (tc[0] != '\n')//吃掉多余的参数
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument!  Input '-help' for help. "<<endl;
				  goto shuru;
			  }
		  }
		  else {
			  cout << "Can't find command '" << command <<" "<<command1<< "' in command list." << endl;
			  while (tc[0] != '\n')//吃掉多余的参数
			  {
				  tc[0] = getchar();
			  }
			  goto shuru;
		  }
	  }
}