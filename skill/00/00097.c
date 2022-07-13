
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM 00097
#define PF_START "00097"
#define PF_NAME "Hệ thống hỗ trợ"

// 函数：获取描述
string get_desc(object me)
{
	return "[ " PF_NAME " ]\n Hệ thống hỗ trợ nhân vật.\n ";
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
	int type;
	object *objs, target;
	int i, size;
	send_user(me, "%c%s", ':', "\nChức năng hỗ trợ cho người chơi \n"
			  //	ESC "Mệnh lệnh huyễn thú\nchuyenhuyenthu\n"
			  ESC "Ẩn/ hiện thời trang\nanthoitrang\n" ESC "Ẩn/ hiện hiệu ứng\nanhieuung\n" ESC "Bật/ khóa kỹ năng nghề nghiệp\nankynangnghe\n");
	//	"cmd/user/ht"->main(me);
	return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数：能否使用指令
void can_perform(object me)
{
	send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME);
}
