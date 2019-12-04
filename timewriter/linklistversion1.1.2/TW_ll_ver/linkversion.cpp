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
	char info[100];//��������100������
	data* next;
}data;

typedef struct wlp
{
	char today[13];
	int count;//�����÷�֧�Ͻڵ��������ȷ���÷�֧��ʱ����
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
void outlist();//���ָ���б�

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

int loadfile(char* path,struct wlp **wl)//�ٶ��ļ�����
{
	ifstream inf;
	char temp1[13];
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
		cout << "������ɣ�" << endl;
	}
}

void adddata(struct wlp** library, char* date)//new version
{
	char* tt ;
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
			else if (!strcmp(end->today, date))//Ŀ��ڵ��Ѵ���
			{
				//free(book);
				addinfo(end);
			}
			else//Ŀ��ڵ㲻����
			{
				book = (struct wlp*)malloc(sizeof(struct wlp));//����ռ� ��ע������ת�� 
				if (book == NULL)//����ʧ�� 
				{
					printf("�ڴ����ʧ��\n");
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
void adddata(struct wlp** library,char* date)//library��ͷָ��ĵ�ַ //old version
{
	char* tt = gettime();
	//char* td = getday();
	struct wlp* book, * temp,*end,*head,*head1;//����ṹ��ָ�� ���ֲ����� 
	end = *library;
	//head = end;
	temp = NULL;
	head = NULL;
	head1 = NULL;
	book = (struct wlp*)malloc(sizeof(struct wlp));//����ռ� ��ע������ת�� 
	if (book == NULL)//����ʧ�� 
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	
	//��������log���������data����������log���½�log�ڵ����data
	//���鿴����β�ڵ�����ڣ��ٿ��Ƿ�����½ڵ�
	//if(end->) adddata(); 

	//getindata(book);
	strcpy_s(book->today, 11, date);
	strcpy_s(book->lpdata.time, 11, tt);
	cout << "������Ϣ��";
	cin >> book->lpdata.info;
	book->next = NULL;

	//cout <<book->today<<" "<< book->lpdata.time << " " << book->lpdata.info << endl;
		
	if (*library == NULL)//������ 
	{
		head1 = (struct wlp*)malloc(sizeof(struct wlp));
		initnode(&head1);
		*library = head1;//ͷ�ڵ�
		//head->next = NULL;
		head1->next = book;//ע��book��ָ�룬�����Ǵ��ݵ�ַ 
		//book->next = NULL;
	}
	else//�ǿ����� ,ͷ�巨
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
		if (count == 0) cout << "There's no data for " << date << endl;
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
	cout<< "  " << "��������������������������������������������" << endl
		<< "  " << "|             * Command list *             |" << endl
		<< "  " << "��������������������������������������������" << endl
		<< "  " << "|     sh       -show command list          |" << endl
		<< "  " << "��������������������������������������������" << endl
		<< "  " << "|  log        -to start writing a log      |" << endl
		<< "  " << "|  endw       -to finish writing the log   |" << endl
		<< "  " << "|   cl        -check today's log           |" << endl
		<< "  " << "| cl date     -check log in date           |" << endl
		<< "  " << "��������������������������������������������" << endl
		<< "  " << "|  plan       -to start writing a plan     |" << endl
		<< "  " << "| plan date   -to start writing a plan     |" << endl
		<< "  " << "|  endw       -to finish writing the plan  |" << endl
		<< "  " << "|   cp        -check today's plan          |" << endl
		<< "  " << "| cp date     -check plan in date          |" << endl
		<< "  " << "��������������������������������������������" << endl
		//<<" exit     -to stop this program"<<endl
		<< "  " << "��������������������������������������������" << endl
		<< "  " << "*    DO NOT use 'exit' before you really   *" << endl
		<< "  " << "*       want to FINISH this program.       *" << endl
		<< "  " << "��������������������������������������������" << endl;
}

int main(void)
{
	ofstream outf;
	ifstream inf;
	char command[5];
	char command1[11] = {0};
	char temp2[11];
	char* td = getday();
	char* tt = gettime();
	cout << td<<" "<<tt << endl;
	char path1[] = ".\\data\\log";
	char path2[] = ".\\data\\plan";
	//command list
	{
		cout<< "����������������������������������������������������" << endl
			<< "|                   TimeWriter                     |" << endl
			<< "����������������������������������������������������" << endl
			<< "|                  Version1.1.2                    |" << endl
			<< "����������������������������������������������������" << endl
			<< "| https://github.com//zhengyunhai/timewriter.git   |" << endl
			<< "����������������������������������������������������" << endl;
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
	if(loadfile(path1,&wl)==2)cout<<"����־�ļ�ʧ�ܣ�"<<endl;
	//����ƻ��ļ�
	if (loadfile(path2, &wp) == 2)cout << "�򿪼ƻ��ļ�ʧ�ܣ�" << endl;
	
shuru:cout << "TimeWriter>> ";
	  cin >> command;
	  //��д�ַ���ƥ��
	  char tc[1] = {0};
	  tc[0] = getchar();
	  {
		  if (!strcmp(command, "sh"))
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
		  if (!strcmp(command, "log"))
		  {
			  if (tc[0] == '\n')
			  {
				  adddata(&wl, td);//logend����������
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
		  if (!strcmp(command, "plan"))
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "Please input Date>>";
				  cin >> temp2;
				  adddata(&wp, temp2);
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  adddata(&wp, command1);
				  goto shuru;
			  }	  
		  }
		  if (!strcmp(command, "cl"))
		  {
			  if (tc[0] == '\n')
			  {
				  searchdata(wl, td);
				  goto shuru;
			  }
			  else
			  {
				  cin >> command1;
				  searchdata(wl, command1);
				  goto shuru;
			  }
		  }
		  if (!strcmp(command, "cp"))
		  {
			  if (tc[0] == '\n')
			  {
				  searchdata(wp, td);
				  goto shuru;
			  }
			  else
			  {
				  cin>>command1;
				  searchdata(wp, command1);
				  goto shuru;
			  }
		  }
		  if (!strcmp(command, "exit")) 
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
			  char command = { 0 };
			  char command1 = { 0 };
			  goto shuru;
		  }
	  }
}