#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<ctime>
#include<direct.h>
#include<windows.h>
#include"logsoft.h"
using namespace std;



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
	//�����ļ�Ĭ�ϴ���
	//������־�ļ�
	if(loadfile(path1,&wl)==2)cout<<"����־�ļ�ʧ�ܣ����½���"<<endl;
	//����ƻ��ļ�
	if (loadfile(path2, &wp) == 2)cout << "�򿪼ƻ��ļ�ʧ�ܣ����½���" << endl;

	char command[10] = { 0 };
shuru:cout << endl<<"TimeWriter>> ";
	  cin >> command;
	  char command1[13] = { 0 };
	  char command2[13] = { 0 };
	  char command3[2] = { 0 };
	  struct wlp* namelink = NULL;
	  char tc[1] = {0};
	  tc[0] = getchar();
	  //ָ��ƥ�䲿��
	  {
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
					  if (!strcmp(command1, "prog"))//�г�������־Ŀ¼
					  {
						  menu(&namelink, wl);
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
					  if (!strcmp(command1, "plan"))//�г��ƻ�Ŀ¼
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

		  if (!strcmp(command, "log"))//д��־
		  {
			  if (tc[0] == '\n')
			  {
				  adddata(&wl, td,td,0);//logend����������
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
					  adddata(&wl, command1,td,1);
					  goto shuru;
				  }
			  }
		  }

		  if (!strcmp(command, "plan"))//д�ƻ�
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
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
						  while (tc[0] != '\n')//�Ե�����Ĳ���
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
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
					  while (tc[0] != '\n')//�Ե�����Ĳ���
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
				  while (tc[0] != '\n')//�Ե�����Ĳ���
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument!" << endl;
				  goto shuru;
			  }
		  }

		  if (!strcmp(command, "exit")) //�˳�����
		  {
			  if (tc[0] == '\n')
			  {
				  cout << "LAYOUT" << endl;
				  //����
				  outtofile(path1, wl);
				  freed(wl);//cout << "�ͷ����" << endl;
				  outtofile(path2, wp);
				  freed(wp);//cout << "�ͷ����" << endl;
				  free(tt); //cout << "�ͷ����" << endl;
				  free(td);
				 // freed(namelink); cout << "�ͷ����" << endl;
				  Sleep(100);
				  return 0;
			  }
			  else
			  {
				  while (tc[0] != '\n')//�Ե�����Ĳ���
				  {
					  tc[0] = getchar();
				  }
				  cout << "Wrong argument!  Input '-help' for help. "<<endl;
				  goto shuru;
			  }
		  }
		  else {
			  cout << "Can't find command '" << command <<" "<<command1<< "' in command list." << endl;
			  while (tc[0] != '\n')//�Ե�����Ĳ���
			  {
				  tc[0] = getchar();
			  }
			  goto shuru;
		  }
	  }
}