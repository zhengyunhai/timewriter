//logsoft.h

//结构体声明
typedef struct data
{
	char time[13];
	char info[200];//字数限制200？？？
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

void f0(char* ti);
//时间格式填充0

char* getday();
//获取当前日期，返回格式例20771201

char* gettime();
//获取当前时间，返回格式例[19:01]

void initnode(struct wlp** head, int i);
//节点初始化

int loadfile(char* path, struct wlp** wl);
//载入文件

void outtofile(char* path, struct wlp* wl);
//输出到文件

void adddata(struct wlp** library, char* name, char* date, int b);
//向链表中添加数据，若第一个节点name，data与参数相同则在此节点添加，否则新建节点添加并作为新的第一个节点

void showinfo(struct wlp* node);
//打印node本节点及其子链表信息

void searchdata(struct wlp* wl, char* name);
//搜索name同名节点

int addinfo(struct wlp* node);
//在node节点子链表上添加信息

void freed(struct wlp* wl);
//释放链表

void freei(struct data* node);
//释放子链表

void outlist();
//输出指令列表

void delnode(struct wlp** node, char* name);
//删除name同名节点

void sampleinfo(struct wlp* node);
//打印简略信息

void exportlog(struct wlp* node, char* name);
//导出node链表中名为name的节点到同名txt中

void headlist();
//打印软件名版本号等

int is_node(struct wlp* node, char* name);
//返回链表中与name同名的节点个数

void delall(struct wlp* node);
//删除全部节点

void menu(struct wlp** namelink, struct wlp* node);
//将node链表中节点按顺序保存首次出现的节点名到namelink中

void copynode();
//复制节点到目标位置，暂无
