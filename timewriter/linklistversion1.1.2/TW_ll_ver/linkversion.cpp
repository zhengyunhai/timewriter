#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<ctime>
#include<direct.h>
#include<windows.h>
using namespace std;

typedef struct data
{
	char time[13];
	char info[100];//字数限制100？？？
	data* next;
}data;

typedef struct wlp
{
	char today[13];
	int count;//计数该分支上节点个数，以确定该分支何时结束
	struct data lpdata;
	wlp* next;
}wlp;

char* getday();
char* gettime();
void initnode(struct wlp** head, int i);
int addinfo(struct wlp* node);
void adddata(struct wlp** library, char* date);
void searchdata(struct wlp* wl, char* date);
void freed(struct wlp* wl);
void showinfo(struct wlp* node);
void freei(struct data* node);
void f0(char* ti);
void outlist();//输出指令列表
void delnode(struct wlp** node,char* date);

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
sr:	cout << "AddInfo>>";
	cin >> temp2;
	while(strcmp(temp2, "endw")) 
	{
		temp = (struct data*)malloc(sizeof(struct data));
		if (temp == NULL) { cout << "内存分配失败" << endl; exit(1); }
		tt = gettime();
		strcpy_s(temp->time, 11, tt);
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
	if (r == NULL) { cout << "内存分配失败" << endl; exit(1); }
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
	if (r == NULL) { cout << "内存分配失败" << endl; exit(1); }
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
		strcpy_s(r->today, 13, "LOGHEAD");
		r->count=1;
		strcpy_s(r->lpdata.time, 13, "LOGTIME");
		strcpy_s(r->lpdata.info, 13, "LOGINFO");
		r->next = NULL;
		r->lpdata.next = NULL;
	}
	if (i == 1)
	{
		strcpy_s(r->today, 13, "LOGHEAD");
		r->count=1;
		strcpy_s(r->lpdata.time, 13, "LOGTIME");
		strcpy_s(r->lpdata.info, 13, "LOGINFO");
		r->next = NULL;
		r->lpdata.next = NULL;
	}
}

int loadfile(char* path,struct wlp **wl)//假定文件存在
{
	ifstream inf;
	char temp1[13];
	struct wlp* lend,*head;
	lend = NULL;
	head = (struct wlp*)malloc(sizeof(struct wlp));
	if (head == NULL) { cout << "内存分配失败" << endl; exit(1); }
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
			if (temp2 == NULL) { cout << "内存分配失败" << endl; exit(1); }
			strcpy_s(temp2->today,strlen(temp1)+1 , temp1);
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
				if (nn == NULL) { cout << "内存分配失败" << endl; exit(1); }
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

void outputfile(char*path,struct wlp* wl)
{
	ofstream outf;
	struct wlp* wtemp = wl;
	struct wlp* lend;
	struct data* temp = NULL;
	lend = wtemp->next;//第一个节点
	if (wtemp == NULL) { cout << "没有可保存信息" << endl; }
	else 
	{
		cout << "正在保存..." << endl;
		outf.open(path);
		while (lend != NULL)
		{
			outf << lend->today << " " << lend->count << endl<< lend->lpdata.time << endl<< lend->lpdata.info << endl;
			temp =&(lend->lpdata);
			while (temp->next!= NULL)
			{
				temp = temp->next;
				outf << temp->time << endl << temp->info << endl;	
			}
			lend = lend->next;
		}
		outf.close();
		cout << "保存完成！" << endl;
	}
}

void adddata(struct wlp** library, char* date)//new version
{
	char* tt ;
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
				printf("内存分配失败\n");
				exit(1);
			}
			strcpy_s(book->today, 13, date);
			book->count = 1;
			cout << "AddInfo>>" ;
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
				if (head1 == NULL) { cout << "内存分配失败" << endl; exit(1); }
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
				if (book == NULL) {printf("内存分配失败\n");exit(1);}
				strcpy_s(book->today, 11, date);
				book->count = 1;
				cout << "AddInfo>>";
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
			else if (!strcmp(end->today, date))//目标节点已存在
			{
				//free(book);
				addinfo(end);
			}
			else//目标节点不存在
			{
				book = (struct wlp*)malloc(sizeof(struct wlp));//分配空间 ，注意类型转换 
				if (book == NULL)//分配失败 
				{
					printf("内存分配失败\n");
					exit(1);
				}
				strcpy_s(book->today, 13, date);
				book->count = 1;
				cout << "AddInfo>>";
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

/*
void adddata(struct wlp** library,char* date)//library是头指针的地址 //old version
{
	char* tt = gettime();
	//char* td = getday();
	struct wlp* book, * temp,*end,*head,*head1;//定义结构体指针 ，局部变量 
	end = *library;
	//head = end;
	temp = NULL;
	head = NULL;
	head1 = NULL;
	book = (struct wlp*)malloc(sizeof(struct wlp));//分配空间 ，注意类型转换 
	if (book == NULL)//分配失败 
	{
		printf("内存分配失败\n");
		exit(1);
	}
	
	//搜索当天log再其中添加data，若当天无log再新建log节点添加data
	//即查看链表尾节点的日期，再看是否接入新节点
	//if(end->) adddata(); 

	//getindata(book);
	strcpy_s(book->today, 11, date);
	strcpy_s(book->lpdata.time, 11, tt);
	cout << "输入信息：";
	cin >> book->lpdata.info;
	book->next = NULL;

	//cout <<book->today<<" "<< book->lpdata.time << " " << book->lpdata.info << endl;
		
	if (*library == NULL)//空链表 
	{
		head1 = (struct wlp*)malloc(sizeof(struct wlp));
		initnode(&head1);
		*library = head1;//头节点
		//head->next = NULL;
		head1->next = book;//注意book是指针，这里是传递地址 
		//book->next = NULL;
	}
	else//非空链表 ,头插法
	{
		temp = end->next;
		end->next = book;
		book->next = temp;
	}
}
*/

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

void searchdata(struct wlp* wl,char* date)
{
	struct wlp* temp;
	int count = 0;
	temp = wl;
	if (temp == NULL) cout << "Empty Data." << endl;
	else
	{
		while (temp!= NULL)
		{
			if (!strcmp(temp->today, date))
			{
				showinfo(temp);
				count++;
			}
			temp = temp->next;
		}
		if (count == 0) cout << "There's no data for '" << date <<"'"<< endl;
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

void outlist()
{
	cout << "  " << "———————————————————————————" << endl
		<< "  " << "|                  * Command list *                  |" << endl
		<< "  " << "———————————————————————————" << endl
		<< "  " << "|       shc              -show command list          |" << endl
		<< "  " << "———————————————————————————" << endl
		<< "  " << "|       list             -show command list          |" << endl
		<< "  " << "———————————————————————————" << endl
		<< "  " << "|       log             -to start writing a log      |" << endl
		<< "  " << "|       endw            -to finish writing the log   |" << endl
		//<< "  " << "|   cl        -check today's log           |" << endl
		<< "  " << "|      cl [date]        -check log in date           |" << endl
		<< "  " << "———————————————————————————" << endl
		//<< "  " << "|  plan       -to start writing a plan     |" << endl
		<< "  " << "|     plan [date]       -to start writing a plan     |" << endl
		<< "  " << "|       endw            -to finish writing the plan  |" << endl
		//<< "  " << "|        cp        -check today's plan          |" << endl
		<< "  " << "|     cp [date]         -check plan in date          |" << endl
		<< "  " << "———————————————————————————" << endl
		<< "  " << "|   del log [date]      -check plan in date          |" << endl
		<< "  " << "|   del plan [date]     -check plan in date          |" << endl
		<< "  " << "———————————————————————————" << endl
		//<<" exit     -to stop this program"<<endl
		<< "  " << "———————————————————————————" << endl
		<< "  " << "*         DO NOT use 'exit' before you really        *" << endl
		<< "  " << "*             want to FINISH this program.           *" << endl
		<< "  " << "———————————————————————————" << endl;
}

void delnode(struct wlp** node, char* date)
{
	struct wlp* temp;
	struct wlp* head;
	int i = 0;
	head = *node;
	temp = NULL;
	//temp = (struct wlp*)malloc(sizeof(struct wlp));

	if (*node == NULL) {
		cout << "No data for '" << date <<"'"<< endl;
	}
	else
	{		
		temp = head->next;
		if (temp == NULL) {//第一个节点为空
			cout << "No data for '" << date <<"'"<< endl;
		}
		else
		{
			while (temp != NULL)
			{
				if (strcmp(temp->today, date))
				{
					head = temp;
					temp = head->next;
				}
				else
				{
					head->next = temp->next;
					//temp->next = NULL;
					freei(temp->lpdata.next);
					free(temp);
					i = 1;
					goto shuchu;
				}
			}
			
		}	
	}
shuchu:	if (i == 1)cout <<"Data '"<< date << "' has been deleted!" << endl;
	else cout << "No such data '" << date <<"'"<< endl;
}

int main(void)
{
	ofstream outf;
	ifstream inf;
	
	//char temp2[11];
	char* td = getday();
	char* tt = gettime();
	cout << td<<" "<<tt << endl;
	char path1[] = ".\\data\\log";
	char path2[] = ".\\data\\plan";
	//command list
	{
		cout << "  " << "———————————————————————————" << endl
			<< "  " << "|                     Time Writer                     |" << endl
			 << "  " << "———————————————————————————" << endl
			<< "  " << "|                    Version 1.2.0                    |" << endl
			 << "  " << "———————————————————————————" << endl
			<< "  " << "|   https://github.com//zhengyunhai/timewriter.git   |" << endl
			 << "  " << "———————————————————————————" << endl;
	clist:outlist();
	}
	struct wlp* wl = NULL;
	struct wlp* lend;
	struct wlp* pend;
	struct wlp* wp = NULL;
	lend = wl;
	pend = wp;
	//读入文件默认存在
	//载入日志文件
	if(loadfile(path1,&wl)==2)cout<<"打开日志文件失败！"<<endl;
	//载入计划文件
	if (loadfile(path2, &wp) == 2)cout << "打开计划文件失败！" << endl;

	char command[5] = { 0 };
shuru:cout << "TimeWriter>> ";
	  cin >> command;
	  //重写字符串匹配
	  char command1[11] = { 0 };
	  char command2[11] = { 0 };
	  char command3[2] = { 0 };
	  char tc[1] = {0};
	  tc[0] = getchar();
	  {
		  if (!strcmp(command, "shc"))//show command list
		  {
			  if (tc[0] =='\n') goto clist;
			  else 
			  { 
				  while (tc[0] != '\n')//吃掉多余的参数
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument."<<endl; 
				  goto  shuru;
			  }
		  }

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
				  //char tc[1] = { 0 };
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
					  if (!strcmp(command1, "log"))
					  {
						  if (wl == NULL)cout << "No logs!" << endl;
						  temp = wl;
						  temp = temp->next;
						  if (temp == NULL)
						  {
							  cout << "No logs!" << endl;
						  }
						  else
						  {
							  while (temp != NULL)
							  {
								  cout << " "<<temp->today << endl;
								  temp = temp->next;
							  }
						  }						  
					  }
					  else if (!strcmp(command1, "plan"))
						  {
							if (wp == NULL)cout << "No plans!" << endl;
							  temp = wp;
							  temp = temp->next;
							  if (temp == NULL)
							  {
								  cout << "No plans!" << endl;
							  }
							  else
							  {
								  while (temp != NULL)
								  {
									  cout <<" "<< temp->today << endl;
									  temp = temp->next;
								  }
							  }					  
						  }
					  else {
						  cout << "Wrong argument!" << endl;
					  }
					  goto shuru;	  
				  }
			  }
		  }

		  if (!strcmp(command, "log"))//写日志
		  {
			  if (tc[0] == '\n')
			  {
				  adddata(&wl, td);//logend包含在其中
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

		  if (!strcmp(command, "plan"))//写计划
		  {
			  if (tc[0] == '\n')//plan
			  {
				  //cout << "Please input Date>>";
				  //cin >> temp2;
				  adddata(&wp, td);
				  goto shuru;
			  }
			  else//plan [date]
			  {
				  cin >> command1;
				  //char tcc[1] = { 0 };
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
					  adddata(&wp, command1);
					  goto shuru;
				  }		  
			  }	  
		  }

		  if (!strcmp(command, "cl"))//check logs in date
		  {
			  if (tc[0] == '\n')
			  {
				  searchdata(wl, td);
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  //char tc[1] = { 0 };
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
				  //char tcc[1] = { 0 };
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
				  //char tcc[1] = { 0 };
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
						  goto shuru;
					  }
					  else
					  {
						  cout << command1 << " in " << command2 << " will be deleted.Countinue?(Y/N):";
						  cin>>command3;
						  if (!strcmp(command3, "y") || !strcmp(command3, "Y"))
						  {
							  if (!strcmp(command1, "log"))
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

		  if (!strcmp(command, "exit")) //退出程序
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "OUTNOW" << endl;
				  //保存
				  outputfile(path1, wl);
				  freed(wl);//cout << "释放完毕" << endl;
				  outputfile(path2, wp);
				  freed(wp);//cout << "释放完毕" << endl;
				  free(tt);// cout << "释放完毕" << endl;
				  free(td); cout << "释放完毕" << endl;
				  Sleep(100);
				  return 0;
			  }
			  else
			  {
				  while (tc[0] != '\n')//吃掉多余的参数
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument!";
				  goto shuru;
			  }
		  }
		  else {
			  cout << "Can't find command '" << command <<" "<<command1<< "' in command list." << endl;
			 // char command = { 0 };
			 // char command1 = { 0 };
			  goto shuru;
		  }
	  }
}