
#include <npc.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 8111; }

// 函数：构造处理
void create()
{
        set_name("Phúc Oa Oa");
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string result,cmd;
	int i=random(8);
        switch(i)
        {
	        case 0:
			cmd="Oa Oa Oa Oa～～Không có tuyết rơi rồi ～～～ oa oa～";
		break;
	        case 1:
			cmd="Oa Oa Oa Oa～～Tiền mừng tuổi của ta không thể nào ít như vậy ?";
		break;
	        case 2:
			cmd="Oa Oa Oa Oa～～Năm mới chỗ nào cũng đốt pháo, đáng sợ nghe～～";
		break;
		case 3:
			cmd="Oa Oa Oa Oa～～Thần Tiên Gia Gia cho ta rất ít lễ vật～～";
		break;
		case 4:
			cmd="Oa Oa Oa Oa～～Ta muốn khóc, ta muốn khóc, hu hu～～～";
		break;
		case 5:
			cmd="Oa Oa Oa Oa～～～～～";
		break;
		case 6:
			cmd="Oa Oa Oa Oa～～Ta là búp bê năm mới Phúc Oa Oa ～～ Phúc Oa Oa～～";
		break;
		case 7:
			cmd="Oa Oa Oa Oa～～Minh Nguyệt mấy khi có, đem rượu hỏi Thanh thiên...～～";
		break;
	}
        result = get_name() + "：\n    "+cmd+"\n"+
       		ESC "Xác nhận\nCLOSE\n";
        send_user( who, "%c%c%w%s", ':', 3, 8111, result );  
}
