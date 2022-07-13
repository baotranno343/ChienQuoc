
#include <npc.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 8112; }

// 函数：构造处理
void create()
{
        set_name("Phúc Cáp Cáp");
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
			cmd="Ha Ha Ha Ha ～～Mùa Xuân thật ấm áp～～";
		break;
	        case 1:
			cmd="Ha Ha Ha Ha ～～Năm mới pháo bổ đầy nhà, thật náo nhiệt～～";
		break;
	        case 2:
			cmd="Ha Ha Ha Ha ～～Năm mới tới rồi, tới Thần Tiên Gia Gia nhận lễ vật thôy～～";
		break;
		case 3:
			cmd="Ha Ha Ha Ha ～～Năm mới nghe nhạc vui vẻ trong lòng～～";
		break;
		case 4:
			cmd="Ha Ha Ha Ha ～～Vui quá là vui～～";
		break;
		case 5:
			cmd="Ha Ha Ha Ha ～～Ta là búp bê năm mới Phúc Cáp Cáp ～ Phúc Cáp Cáp～～^_^";
		break;
		case 6:
			cmd="Ha Ha Ha Ha ～～Nhân loại và Nguyệt cũng giống nhau thôy";
		break;
		case 7:
			cmd="Ha Ha Ha Ha ～～Năm mới tới rồi, ngươi muốn nhận tiền mừng tuổi không ?";
		break;
	}
        result = get_name() + "：\n    "+cmd+"\n"+
       		ESC "Xác nhận\nCLOSE\n";
        send_user( who, "%c%c%w%s", ':', 3, 8112, result );  
}

