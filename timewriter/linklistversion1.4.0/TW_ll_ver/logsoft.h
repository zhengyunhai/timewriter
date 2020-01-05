//logsoft.h

//�ṹ������
typedef struct data
{
	char time[13];
	char info[200];//��������200������
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

void f0(char* ti);
//ʱ���ʽ���0

char* getday();
//��ȡ��ǰ���ڣ����ظ�ʽ��20771201

char* gettime();
//��ȡ��ǰʱ�䣬���ظ�ʽ��[19:01]

void initnode(struct wlp** head, int i);
//�ڵ��ʼ��

int loadfile(char* path, struct wlp** wl);
//�����ļ�

void outtofile(char* path, struct wlp* wl);
//������ļ�

void adddata(struct wlp** library, char* name, char* date, int b);
//��������������ݣ�����һ���ڵ�name��data�������ͬ���ڴ˽ڵ���ӣ������½��ڵ���Ӳ���Ϊ�µĵ�һ���ڵ�

void showinfo(struct wlp* node);
//��ӡnode���ڵ㼰����������Ϣ

void searchdata(struct wlp* wl, char* name);
//����nameͬ���ڵ�

int addinfo(struct wlp* node);
//��node�ڵ��������������Ϣ

void freed(struct wlp* wl);
//�ͷ�����

void freei(struct data* node);
//�ͷ�������

void outlist();
//���ָ���б�

void delnode(struct wlp** node, char* name);
//ɾ��nameͬ���ڵ�

void sampleinfo(struct wlp* node);
//��ӡ������Ϣ

void exportlog(struct wlp* node, char* name);
//����node��������Ϊname�Ľڵ㵽ͬ��txt��

void headlist();
//��ӡ������汾�ŵ�

int is_node(struct wlp* node, char* name);
//������������nameͬ���Ľڵ����

void delall(struct wlp* node);
//ɾ��ȫ���ڵ�

void menu(struct wlp** namelink, struct wlp* node);
//��node�����нڵ㰴˳�򱣴��״γ��ֵĽڵ�����namelink��

void copynode();
//���ƽڵ㵽Ŀ��λ�ã�����
