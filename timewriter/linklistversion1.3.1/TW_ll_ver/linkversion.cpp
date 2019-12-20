#include<iostream>
#include<fstream>
#include<iomanip>
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
	char info[200];//��������100������
	data* next;
}data;

typedef struct wlp
{
	char name[20];
	char today[13];
	int b;//b=0,��ͨ��־,b=1,������־
	int count;//�����÷�֧�Ͻڵ��������ȷ���÷�֧��ʱ����
	struct data lpdata;
	wlp* next;
}wlp;



char* getday();//��ȡ��ǰ����
char* gettime();//��ȡ��ǰʱ��
void initnode(struct wlp** head, int i);//�ڵ��ʼ��
int addinfo(struct wlp* node);
void adddata(struct wlp** library, char* date);
void searchdata(struct wlp* wl, char* date);
void freed(struct wlp* wl);
void showinfo(struct wlp* node);
void freei(struct data* node);
void f0(char* ti);//���0
void outlist();//���ָ���б�
void delnode(struct wlp** node,char* date);//ɾ���ڵ�
void sampleinfo(struct wlp* node);//������Ϣ
void exportlog(struct wlp* node,char* name);//����node��������Ϊname�Ľڵ㵽ͬ��txt��
void headlist();

void f0(char* ti)//���0
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
		if (temp == NULL) { cout << "�ڴ����ʧ��" << endl; exit(1); }
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

char* getday()//��ȡ��ǰ����
{
	char temp1[13] = {0};
	char temp2[8] = {0};
	char temp3[8] = {0};
	char* r;
	r = (char*)malloc(sizeof(temp1));
	if (r == NULL) { cout << "�ڴ����ʧ��" << endl; exit(1); }
	time_t sec = time(0);
	struct tm now;
	localtime_s(&now, &sec);
	_itoa_s(now.tm_year + 1900, temp1, 10);
	_itoa_s(now.tm_mon + 1, temp2, 10);
	if (now.tm_mon < 10) f0(temp2);
	_itoa_s(now.tm_mday, temp3, 10);
	if (now.tm_mday < 10) f0(temp3);
	strcat_s(temp1, sizeof(temp1), temp2);
	strcat_s(temp1, sizeof(temp1), temp3);//temp1��������
	strcpy_s(r, 13, temp1);
	return r;
}

char* gettime()//��ȡ��ǰʱ��
{
	char temp1[13] = { 0 };
	char temp2[8] = { 0 };
	char temp3[8] = { 0 };
	char temp4[13] = "[";
	char* r;
	r = (char*)malloc(sizeof(temp1));
	if (r == NULL) { cout << "�ڴ����ʧ��" << endl; exit(1); }
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

void initnode(struct wlp** head,int i)//δ��ɣ�i=1ʱ��
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

int loadfile(char* path,struct wlp **wl)//�ٶ��ļ�����
{
	ifstream inf;
	char temp1[30];//�������ȶ����name
	struct wlp* lend,*head;
	lend = NULL;
	head = (struct wlp*)malloc(sizeof(struct wlp));
	if (head == NULL) { cout << "�ڴ����ʧ��" << endl; exit(1); }
	initnode(&head,0);
	*wl = head;
	lend = head;
	inf.open(path);
	if (!inf.is_open()) { return 2; }
	else
	{
		while (inf >> temp1)//��������
		{
			struct wlp* temp2;
			struct data* tempend1,*nn;
			int i = 2;
			tempend1 = NULL;
			nn = NULL;
			temp2 = (struct wlp*)malloc(sizeof(struct wlp));
			if (temp2 == NULL) { cout << "�ڴ����ʧ��" << endl; exit(1); }
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
				if (nn == NULL) { cout << "�ڴ����ʧ��" << endl; exit(1); }
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
	lend = wtemp->next;//��һ���ڵ�
	if (wtemp == NULL) { cout << "û�пɱ�����Ϣ" << endl; }
	else 
	{
		cout << "���ڱ���..." << endl;
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
		cout << "������ɣ�" << endl;
	}
}

void adddata(struct wlp** library, char* name,int b)//new version
											  //ԭ�����˵�����鿴��һ���ڵ��Ƿ�ΪĿ��ڵ㣬����������������ݣ������½��ڵ㲢���룬��ֻ����һ���ڵ㣬���Ǳ�����������
{
	char* td=getday() ;
	char* tt;
	struct wlp* book, * temp, * end, * head, * head1;//����ṹ��ָ�� ���ֲ����� 
	end = *library;
	head= *library;
	book = NULL;
	temp = NULL;
	head1 = NULL;
	//�����ڵ㣨ֻ����һ���ڵ㣩��ͷ�ڵ��ĵ�һ���ڵ㣩	
		if (*library == NULL)//������ ��ֻ�пյ�ͷָ��//����loadfile()�Ĵ��ڣ�������Ϊ������������һ��ͷ�ڵ�
		{
			book = (struct wlp*)malloc(sizeof(struct wlp));//����ռ� ��ע������ת�� 
			if (book == NULL)//����ʧ�� 
			{
				printf("�ڴ����ʧ��\n");
				exit(1);
			}
			strcpy_s(book->name, 20, name);
			strcpy_s(book->today, 13, td);
			book->b = b;
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
				if (head1 == NULL) { cout << "�ڴ����ʧ��" << endl; exit(1); }
				initnode(&head1, 0);
				*library = head1;//ͷ�ڵ�
				head1->next = book;//ע��book��ָ�룬�����Ǵ��ݵ�ַ 
			}
		}
		else//�ǿ����� ,��ͷ�ڵ㣬ͷ�巨
		{
			end = end->next;//ָ���һ���ڵ�
			if (end == NULL)//��һ���ڵ�Ϊ�գ�ֻ��һ��ͷ�ڵ�
			{
				book = (struct wlp*)malloc(sizeof(struct wlp));//����ռ� ��ע������ת�� 
				if (book == NULL) {printf("�ڴ����ʧ��\n");exit(1);}
				strcpy_s(book->name, 20, name);
				strcpy_s(book->today, 13, td);
				book->b = b;
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
			else if (!strcmp(end->name, name))//Ŀ��ڵ��Ѵ���,����һ���ڵ�ΪĿ��ڵ�
			{
				addinfo(end);
			}
			else//Ŀ��ڵ㲻���ڣ�����һ���ڵ㲻��Ŀ��ڵ�
			{
				book = (struct wlp*)malloc(sizeof(struct wlp));//����ռ� ��ע������ת�� 
				if (book == NULL)//����ʧ�� 
				{
					printf("�ڴ����ʧ��\n");
					exit(1);
				}
				strcpy_s(book->name, 20, name);
				strcpy_s(book->today, 13, td);
				book->b = b;
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

void outlist()
{
	cout << "  " << "                                         " << getday() << " " << gettime() << endl;
	cout << "  " << "����������������������������������������������������������" << endl
		<< "  " << "|                    * Command list *                    |" << endl
		<< "  " << "����������������������������������������������������������" << endl
		
		<< "  " << "����������������������������������������������������������" << endl
		<< "  " << "|     shc                     -show command list         |" << endl
		<< "  " << "����������������������������������������������������������" << endl
		<< "  " << "|     list [log/prog/plan]    -show logmenu              |" << endl
		<< "  " << "����������������������������������������������������������" << endl
		<< "  " << "|     log                     -to start writing a log    |" << endl
		<< "  " << "|     prog [progname]         -to start writing a proglog|" << endl
		<< "  " << "|     endw                    -to finish writing the log |" << endl
		<< "  " << "|     cl [name]               -check log/prog            |" << endl
		<< "  " << "����������������������������������������������������������" << endl
		<< "  " << "|     plan [name]             -to start writing a plan   |" << endl
		<< "  " << "|     endw                    -to finish writing the plan|" << endl
		<< "  " << "|     cp [date/name]          -check plan in date        |" << endl
		<< "  " << "����������������������������������������������������������" << endl
		<< "  " << "|     del [log/plan] [name]   -delete data               |" << endl
		<< "  " << "����������������������������������������������������������" << endl
		<< "  " << "|     expd [name]             -export log data           |" << endl
		<< "  " << "|     exit                    -save and exit             |" << endl
		<< "  " << "����������������������������������������������������������" << endl;
	/*	<< "  " << "*           DO NOT use 'exit' before you really          *" << endl
		<< "  " << "*               want to FINISH this program.             *" << endl
		<< "  " << "����������������������������������������������������������" << endl;
	*/
}

void delnode(struct wlp** node, char* name)//ע�����ɾ����nameͬ�������нڵ�
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
		if (head == NULL) {//��һ���ڵ�Ϊ��
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
		if(N==12)strcat_s(temp, sizeof(temp), " ... ...");
		
		cout << temp;
	}
	cout << endl;
}

void exportlog(struct wlp* node,char* name)
{
	char path[50]= ".\\data\\";
	strcat_s(path, 50, name);
	strcat_s(path, 50, ".txt");
	ofstream outf;
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

void headlist()
{
	cout << "  " << "������������������������������������������������������" << endl
		<< "  " << "|                     Time Writer                    |" << endl
		<< "  " << "������������������������������������������������������" << endl
		<< "  " << "|                    Version 1.3.1                   |" << endl
		<< "  " << "������������������������������������������������������" << endl
		<< "  " << "|   https://github.com//zhengyunhai/timewriter.git   |" << endl
		<< "  " << "������������������������������������������������������" << endl;
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
	clist:outlist();
	}
	struct wlp* wl = NULL;
	struct wlp* lend;
	struct wlp* pend;
	struct wlp* wp = NULL;
	lend = wl;
	pend = wp;
	//�����ļ�Ĭ�ϴ���
	//������־�ļ�
	if(loadfile(path1,&wl)==2)cout<<"����־�ļ�ʧ�ܣ����½���"<<endl;
	//����ƻ��ļ�
	if (loadfile(path2, &wp) == 2)cout << "�򿪼ƻ��ļ�ʧ�ܣ����½���" << endl;

	char command[10] = { 0 };
shuru:cout << "TimeWriter>> ";
	  cin >> command;
	  char command1[13] = { 0 };
	  char command2[13] = { 0 };
	  char command3[2] = { 0 };
	  char tc[1] = {0};
	  tc[0] = getchar();
	  //ָ��ƥ�䲿��
	  {
		  if (!strcmp(command, "shc"))//show command list
		  {
			  if (tc[0] =='\n') goto clist;
			  else 
			  { 
				  while (tc[0] != '\n')//�Ե�����Ĳ���
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument."<<endl; 
				  goto  shuru;
			  }
		  }

		  if (!strcmp(command, "list"))//�г���Ŀ��
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  if (!strcmp(command1, "log"))//�г���ͨ��־Ŀ¼
					  {
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
								  cout << "  " << setw(20) << setiosflags(ios::left) << "LogName"; cout << "  " << setw(10) << "LogDate" << "  " << "SampleInfo" << endl;
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
						  goto shuru;
					  }
					  if (!strcmp(command1, "prog"))//�г�������־Ŀ¼
					  {
						  if (wl == NULL)cout << "No prog!" << endl;
						  else {
							  temp = wl;//prog��log����ͬһ������
							  temp = temp->next;
							  if (temp == NULL)
							  {
								  cout << "No prog!" << endl;
							  }
							  else
							  {
								  cout << "  " << setw(20) << setiosflags(ios::left) << "ProgName"; cout << "  " << setw(10) << "ProgDate" << "  " << "SampleInfo" << endl;
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
						  goto shuru;
					  }
					  if (!strcmp(command1, "plan"))//�г��ƻ�Ŀ¼
					  {
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
									cout << "  " << setw(20) << setiosflags(ios::left) << "PlanName"; cout << "  " << setw(10) << "PlanDate" << "  " << "SampleInfo" << endl;
									while (temp != NULL)
									{
										cout << "  " << setw(20) << setiosflags(ios::left) << temp->name; cout << " " << "[" << temp->today << "]" << "   ";
										sampleinfo(temp);
										temp = temp->next;
									}
								}
							}
							goto shuru;
					  }
					
					  else {
						  cout << "Wrong argument!" << endl;
						  goto shuru;
					  }
					  	  
				  }
			  }
		  }

		  if (!strcmp(command, "log"))//д��־
		  {
			  if (tc[0] == '\n')
			  {
				  adddata(&wl, td,0);//logend����������
				  goto shuru;
			  }
			  else 
			  {
				  while (tc[0] != '\n')//�Ե�����Ĳ���
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  adddata(&wl, command1,1);
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "plan"))//д�ƻ�
		  {
			  if (tc[0] == '\n')//plan
			  {
				  adddata(&wp, td,0);
				  goto shuru;
			  }
			  else//plan [date]
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//�Ե�����Ĳ���
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  adddata(&wp, command1,0);
					  goto shuru;
				  }		  
			  }	  
		  }

		  if (!strcmp(command, "cl"))//check logs in date
		  {
			  if (tc[0] == '\n')
			  {
				  cout << td <<":"<< endl;
				  searchdata(wl, td);
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  tc[0] = getchar();
				  if (tc[0] != '\n')
				  {
					  while (tc[0] != '\n')//�Ե�����Ĳ���
					  {
						  tc[0] = getchar();
					  }
					  cout << "Wrong argument!" << endl;
					  goto shuru;
				  }
				  else
				  {
					  cout << command1 << ":" << endl;
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
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

		  if (!strcmp(command, "del"))//ɾ������
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

		  if (!strcmp(command, "expd"))//��ʱֻ���ڵ���������־
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
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

		  if (!strcmp(command, "exit")) //�˳�����
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "OUTNOW" << endl;
				  //����
				  outputfile(path1, wl);
				  freed(wl);//cout << "�ͷ����" << endl;
				  outputfile(path2, wp);
				  freed(wp);//cout << "�ͷ����" << endl;
				  free(tt);// cout << "�ͷ����" << endl;
				  free(td); cout << "�ͷ����" << endl;
				  Sleep(100);
				  return 0;
			  }
			  else
			  {
				  while (tc[0] != '\n')//�Ե�����Ĳ���
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument!";
				  goto shuru;
			  }
		  }
		  else {
			  cout << "Can't find command '" << command <<" "<<command1<< "' in command list." << endl;
			  goto shuru;
		  }
	  }
}