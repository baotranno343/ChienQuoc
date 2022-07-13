
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <cmd.h>
#include <task.h>
inherit OFFICER;

private
static int min10 = -1; // 复位次数

// 函数：功德老人识别
int is_bonus_seller() { return 1; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void reset();
void do_buy(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5901; }

// 函数：构造处理
void create()
{
        set_name("Công Đức Lão Nhân");

        set_2("talk", (["buy":(
                                  : do_buy:),
        ]));
        reset();
        set("mpLegend2", ([0:({
                                 32 * 48 + 22,
                                 32 * 48 + 25,
                             }),
        ]));
        setup();
}

// 函数：对话处理
void do_look(object who)
{
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd101 = "", tmp;
        int id;
        "/quest/help"->send_help_tips(who, 29);
        id = getoid(this_object());
        cmd1 = sprintf("talk %x# buy.1\n", id);
        cmd2 = sprintf("talk %x# buy.2\n", id);
        cmd3 = sprintf("talk %x# buy.3\n", id);
        cmd4 = sprintf("talk %x# buy.4\n", id);
        cmd5 = sprintf("talk %x# buy.6\n", id);
        cmd6 = sprintf("talk %x# buy.8\n", id);
        if (who->get_legend(TASK_48, 21) && !who->get_legend(TASK_48, 22))
                cmd101 = sprintf(ESC HIY "Chứng Bệnh Nan Y 1\ntalk %x# buy.101\n", id);
        if (who->get_legend(TASK_48, 22) && !who->get_legend(TASK_48, 23))
                cmd101 = sprintf(ESC HIY "疑难杂症（2）\ntalk %x# buy.101\n", id);
        if (who->get_legend(TASK_48, 24) && !who->get_legend(TASK_48, 25))
                cmd101 = sprintf(ESC HIY "疑难杂症（2）\ntalk %x# buy.101\n", id);
        if (who->get_legend(TASK_48, 25) && !who->get_legend(TASK_48, 26))
                cmd101 = sprintf(ESC HIY "疑难杂症（3）\ntalk %x# buy.101\n", id);
        if (MAIN_D->get_host_type() != 4)
        {
                if (who->get_save_2("chain.save"))
                        tmp = ESC " Nghi nan tạp chứng 。\n" + sprintf("talk %x# buy.82\n", id);
                else if (who->get_save_2("chain.type"))
                        tmp = ESC " Bảo tồn chuỗi nhiệm vụ \n" + sprintf("talk %x# buy.83\n", id);
                else
                        tmp = ESC "Nhận lấy chuỗi nhiệm vụ \n" + sprintf("talk %x# buy.81\n", id);
        }
        send_user(who, "%c%s", ':', sprintf(" %s :\n Ngươi có %d điểm công năng, có việc gì ta có thể giúp ngươi?\n", get_name(), who->get_bonus() / 10) + cmd101 +
                                        //                ESC "兑换宝石、装备。\n" + cmd1 +
                                        ESC "Đổi Tiềm năng.\n" + cmd2 + ESC "Đổi Ngân lượng Khóa.\n" + cmd3 + ESC "Đổi rương dự trữ đồ.\n" + cmd4 + ESC "Rửa sạch PK.\n" + cmd5 + ESC "Dùng điểm công đức để xóa điểm.\n" + cmd6 + ESC "了解跑环任务。\n" + sprintf("talk %x# buy.80\n", id) + tmp + ESC "Rời khỏi.\nCLOSE\n");
}

string *StoneTable = ({
    "/item/89/8901",
    "/item/89/8902",
    "/item/89/8903",
    "/item/89/8904",
    "/item/89/8905",
    "/item/89/8906",
    "/item/89/8907",
    "/item/89/8908",
    "/item/89/8909",
    "/item/89/8910",
    "/item/89/8911",
    "/item/89/8912",
    "/item/89/8913",
    "/item/89/8914",
    "/item/89/8915",
    "/item/89/8916",
    "/item/89/8917",
    "/item/89/8918",
    "/item/89/8919",
    "/item/89/8920",
    "/item/89/8921",
    //      "/item/89/8922",
    "/item/89/8923",
});

int sizeof_stone = sizeof(StoneTable);

// 函数：复位处理
void reset()
{
        string *stone, *equip, file;

        if (++min10 % 6 == 0) // １小时处理(10min * 6)
        {
                reset_eval_cost();
                /*
                stone = ({ });                
                while( sizeof(stone) < 3 )
                {
                        file = StoneTable[ random(sizeof_stone) ];
                        if( member_array(file, stone) == -1 ) stone = stone + ({ file }) - ({ 0 });
                }
                add_2( "good", ([
                        "01" : stone[0],
                        "02" : stone[1],
                        "03" : stone[2],
                ]) );
                add_2( "list", ([
                        "01" : 3,
                        "02" : 3,
                        "03" : 3,
                ]) );
*/
                equip = ({});
                while (sizeof(equip) < 5)
                {
                        switch (random(4))
                        {
                        default:
                                file = WEAPON_FILE->get_weapon_file_2(60);
                                break;
                        case 1:
                                file = WEAPON_FILE->get_weapon_file_2(70);
                                break;
                        case 2:
                                file = ARMOR_FILE->get_armor_file_2(60);
                                break;
                        case 3:
                                file = ARMOR_FILE->get_armor_file_2(70);
                                break;
                        }
                        if (member_array(file, equip) == -1)
                                equip = equip + ({file}) - ({0});
                }
                add_2("good", (["04":equip[0],
                                  "05":equip[1],
                                  "06":equip[2],
                                  "07":equip[3],
                                  "08":equip[4],
                ]));
                add_2("list", (["04":2,
                                  "05":2,
                                  "06":2,
                                  "07":2,
                                  "08":2,
                ]));
        }
}

// 函数：兑换功德点
void do_buy(string arg)
{
        object me, who;
        string cmd1, cmd2, cmd3;
        int id, type, type2, p1, p2, time, i, p;
        object item;

        me = this_object();
        who = this_player();

        if (!arg)
                type = 1;
        else if (sscanf(arg, "%d.%d", type, type2))
                ;
        else
        {
                type = to_int(arg);
                type2 = 0;
        }

        if (type >= 2 && type <= 100)
        {
                if (MAIN_D->get_host_type() == 6012)
                {
                        send_user(who, "%c%s", '!', "功能尚未开放！");
                        return;
                }
        }

        switch (type)
        {
        default:
                LIST_CMD->main(who, sprintf("%x#", getoid(me)));
                return;

        case 2:
                switch (type2)
                {
                default:
                        id = getoid(me);
                        cmd1 = sprintf("talk %x# buy.2.1\n", id);
                        cmd2 = sprintf("talk %x# buy.2.2\n", id);
                        cmd3 = sprintf("talk %x# buy.2.3\n", id);
                        send_user(who, "%c%s", ':', get_name() + ": \n1 Điểm công đức có thể đổi  55  Tiềm năng, ngươi muốn như thế nào?\n" ESC "10  Công đức đổi  550  Tiềm năng.\n" + cmd1 + ESC "20  Công đức đổi  1100  Tiềm năng.\n" + cmd2 + ESC "40  Công đức đổi  2200  Tiềm năng.\n" + cmd3 + ESC "Rời đi.\nCLOSE\n");
                        return;
                case 1:
                        p1 = 100;
                        p2 = 550;
                        break;
                case 2:
                        p1 = 200;
                        p2 = 1100;
                        break;
                case 3:
                        p1 = 400;
                        p2 = 2200;
                        break;
                }

                if (who->get_bonus() < p1)
                {
                        send_user(who, "%c%s", '!', " Ngươi điểm công đức không đủ ");
                        return;
                }

                who->add_bonus(-p1);
                who->add_potential(p2);
                write_user(who, ECHO " Ngài dùng  %d  Điểm công đức đổi  %d  Tiềm năng 。", p1 / 10, p2);

                return;

        case 3:
                switch (type2)
                {
                default:
                        id = getoid(me);
                        cmd1 = sprintf("talk %x# buy.3.1\n", id);
                        cmd2 = sprintf("talk %x# buy.3.2\n", id);
                        cmd3 = sprintf("talk %x# buy.3.3\n", id);
                        send_user(who, "%c%s", ':', get_name() + ": \n1 Điểm công đức có thể đổi  1500  Ngân Lượng, ngươi muốn như thế nào?\n" ESC "20  Công đức đổi  30000  Ngân Lượng.\n" + cmd1 + ESC "40  Công đức đổi  60000  Ngân Lượng.\n" + cmd2 + ESC "80  Công đức đổi  120000  Ngân Lượng.\n" + cmd3 + ESC "Rời đi.\nCLOSE\n");
                        return;
                case 1:
                        p1 = 200;
                        p2 = 30000;
                        break;
                case 2:
                        p1 = 400;
                        p2 = 60000;
                        break;
                case 3:
                        p1 = 800;
                        p2 = 120000;
                        break;
                }

                if (who->get_bonus() < p1)
                {
                        send_user(who, "%c%s", '!', "Ngươi điểm công đức không đủ.");
                        return;
                }

                who->add_bonus(-p1);
                who->add_cashkhoa(p2);
                who->add_gold_log("sell", p2);
                who->log_money("功德", p2);
                "/sys/sys/count"->add_income("bonus", p2);
                write_user(who, ECHO " Ngươi dùng  %d  Điểm công đức đổi  %d  Ngân Lượng Khóa.", p1 / 10, p2);

                return;
        case 4:
                send_user(who, "%c%s", ':', me->get_name() + "：\n    Đổi bang phái dự trữ nhiệm vụ vật thay thế nhất định phải tiêu hao 5 Điểm điểm công đức. Ngươi nhất định phải đổi sao?？\n" + ESC "Xác định \n" + sprintf("talk %x# buy.5\n", getoid(me)) + ESC "Rời đi. \nCLOSE\n");
                break;
        case 5:
                /*	
		if (who->get_save_2("orgtask.type")==0)
		{
			send_user( who, "%c%s", ':', me->get_name() + "：\n    你在与老夫开玩笑吧？要兑换替代品你就得先去帮派帐房先生处领取储备任务\n"+
                		ESC "离开。\nCLOSE\n" );
                	return ;
		}	
*/
                if (who->get_bonus() < 50)
                {
                        send_user(who, "%c%s", ':', me->get_name() + "：\n     Ngươi công đức còn chưa đủ, dạy nhiều đồ đệ tồn điểm công đức rồi lại đến lão phu.\n" + ESC "Rời đi 。\nCLOSE\n");
                        return;
                }
                if (sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY)
                {
                        send_user(who, "%c%s", ':', me->get_name() + "：\n     Không đủ ô trống.\n" + ESC "离开。\nCLOSE\n");
                        return;
                }
                item = new ("/item/01/0006");
                if (item)
                {
                        p = item->move(who, -1);
                        item->add_to_user(p);
                        send_user(who, "%c%s", ':', me->get_name() + "：\n    Đây chính là ngươi muốn dự trữ rương, mau mau trở về kế toán tiên sinh chỗ giao nộp đi 。\n" + ESC "离开。\nCLOSE\n");
                        send_user(who, "%c%s", '!', "Đạt được một cái Rương Dự Trữ ");
                        who->add_bonus(-50);
                }
                break;
                /*		       
	case 6:		//洗红名
		if ( who->get_pk() <= 0 )
		{
			send_user( who, "%c%s", ':', get_name() + "：\n    你在和老夫开玩笑吧？\n"
                        	ESC "返回\nCLOSE\n" );
			return ;
		}
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf("%s\n    你已经造了%d个杀孽，你愿意花费20点功德来减轻自己的罪孽吗？\n"ESC"确定\ntalk %x# buy.7\n"ESC"离开",get_name(),who->get_pk(),getoid(this_object())));
		break;			
	case 7:
		if ( who->get_bonus() < 100 )
		{
                        send_user( who, "%c%s", ':', get_name() + ":\n    你的功德还是不足……年轻人还得多行善果，协助新人修炼才可以得到更多的功德啊。" );
                        return;
                }
                if ( who->get_pk() <= 0 )
                	return; 
                who->add_pk(-100);
                who->add_bonus(-100);         
                send_user( who, "%c%s", ':', get_name() + ":\n    你花费20点功德洗掉一个红名。" ) ;   	
		break;		
*/
        case 8:
                time = who->get_save("bonus_time");
                p1 = 100;
                if (time > 0)
                        for (i = 0; i < time; i++)
                                p1 *= 2;
                if (p1 > 1600)
                        p1 = 1600;
                id = getoid(me);
                cmd1 = sprintf("talk %x# buy.9\n", id);
                send_user(who, "%c%s", ':', sprintf(get_name() + "：\n   Ngươi nguyện ý tiêu hao  %d  Điểm công đức đến một lần nữa phân phối ngươi điểm thuộc tính sao?\n" ESC "Đồng Ý\n" + cmd1 + ESC "Rời Đi\nCLOSE\n", p1));
                break;
        case 9:
                time = who->get_save("bonus_time");
                p1 = 1000;
                if (time > 0)
                        for (i = 0; i < time; i++)
                                p1 *= 2;
                if (p1 > 16000)
                        p1 = 16000;
                if (who->get_bonus() < p1)
                {
                        send_user(who, "%c%s", ':', get_name() + "\n     Ngươi công đức còn là chưa đủ...... Người trẻ tuổi còn phải nhiều làm việc thiện quả, hiệp trợ người mới tu luyện mới có thể đạt được càng nhiều công đức.");
                        return;
                }
                who->add_bonus(-p1);
                who->add_save("bonus_time", 1);
                "/cmd/user/gift"->init_gift_point(who);
                id = getoid(me);
                cmd1 = sprintf("look %x#\n", id);
                send_user(who, "%c%s", ':', get_name() + "：\n     Lão phu đã giúp ngươi thực hiện nguyện vọng, còn có cái gì cần lão phu hỗ trợ sao ？\n" ESC "返回\n" + cmd1);
                who->log_legend(" Ngài tại công đức lão nhân chỗ tẩy điểm thuộc tính s。");
                break;
        case 80:
                send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
                          sprintf("%s\n   Nếu như ngươi tiếp vào giết ác bá nhiệm vụ, làm ngươi không cách nào hoàn thành thời điểm, ngươi có thể cân nhắc tìm kiếm cao thủ hỗ trợ a ~! Nếu như ngươi có thể liên tục làm xong 50 Vòng nhiệm vụ, ngươi sẽ thu hoạch được kinh nghiệm phong phú ban thưởng cùng vật phẩm ban thưởng. Ngoài ra một người cùng ngày chỉ có thể xác nhận một lần chạy xong nhiệm vụ, làm ngươi từ bỏ hoặc là hoàn thành một lần chạy vòng nhiệm vụ, như vậy cùng ngày ngươi liền chờ ngày thứ hai lại đến nhận lấy nhiệm vụ đi ~!\n" ESC "Rời đi", me->get_name()));
                break;
        case 81:
                CHAIN_D->new_chain(who, me);
                break;
        case 82:
                CHAIN_D->query_resume_chain(who, me);
                break;
        case 83:
                CHAIN_D->query_save_chain(who, me);
                break;
        case 84:
                CHAIN_D->save_chain(who, me);
                break;
        case 85:
                CHAIN_D->resume_chain(who, me);
                break;
        case 101:
                if (who->get_legend(TASK_48, 21) && !who->get_legend(TASK_48, 22))
                        send_user(who, "%c%s", ':', sprintf(" %s :\n Theo tình hình ngươi thuật lại, xem ra thôn dân không phải phát bệnh, mà là trúng độc, ngươi giúp ta nghĩ cách giải độc đi, rồi hãy đến tìm ta.\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# buy.102\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
                else if (who->get_legend(TASK_48, 22) && !who->get_legend(TASK_48, 23))
                        send_user(who, "%c%s", ':', sprintf("%s:\n     Theo ta suy đoán,trúng độc thôn dân đều là uống qua phía sau thôn miệng giếng nước kia bên trong nước sau, mới xuất hiện này triệu chứng.\n     Giải loại độc này thiết yếu hùng hoàng tán, đồng thời muốn cùng những dược vật khác phối hợp mới có hiệu quả trị liệu, thuốc này phối tốt sau không chỉ muốn cho các thôn dân ăn vào, còn phải sái nhập giếng nước bên trong làm giải độc dùng.\n     Ngươi đi trước tìm đến hùng hoàng tán đi, ta nghe nói u cốc một vùng nhỏ ong mật, con kiến nhỏ, điểm lấm tấm con ếch trên thân đều mang theo hùng hoàng tán.\n     Làm xong nhiệm vụ sau, dùng alt+w Mở ra nhân vật thuộc tính giao diện, tái sử dụng tân thủ tín vật liền có thể nhanh chóng trở lại Tân Thủ thôn a!\n" ESC "Tiếp nhận nhiệm vụ \ntalk %x# buy.103\n" ESC "Rời đi", me->get_name(), getoid(me)));
                else if (who->get_legend(TASK_48, 24) && !who->get_legend(TASK_48, 25))
                        send_user(who, "%c%s", ':', sprintf(" %s :\n Ta trộn thuốc cần có 1 thời gian nhất định, 1 lúc sau ngươi hãy quay lại để lấy thuốc nhé!\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# buy.104\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
                else if (who->get_legend(TASK_48, 25) && !who->get_legend(TASK_48, 26))
                        send_user(who, "%c%s", ':', sprintf("%s:\n       Ngươi đem cái này bao giải dược đưa cho đội trưởng bảo vệ, đồng thời nói cho hắn biết, ngàn vạn phải nhớ đến căn dặn người trong thôn gần nhất hai ngày đừng đi phía sau thôn miệng giếng nước kia bên trong múc nước uống, nhớ kỹ muốn đem giải dược đưa cho thôn dân phục dụng, còn muốn đem giải dược hất tới giếng nước bên trong, dạng này mới có thể trị phần ngọn lại trị tận gốc!\n     Còn có một việc, ngươi ngàn vạn không được lộ ra, ngươi nói cho đội trưởng bảo vệ, ta lòng nghi ngờ là có người tại giếng nước bên trong hạ độc, còn nghĩ mời thôn trưởng tra ra việc này, bắt được hạ độc nhẫn tâm người.\n" ESC "Tiếp nhận nhiệm vụ \ntalk %x# buy.105\n" ESC "Rời đi", me->get_name(), getoid(me)));
                break;
        case 102:
                if (who->get_legend(TASK_48, 21) && !who->get_legend(TASK_48, 22))
                {
                        TASK_LEGEND_D->task_finish(who);
                        who->set_legend(TASK_48, 22);
                        who->add_exp(350);
                        who->add_potential(20);
                        who->add_cash(500);
                        send_user(who, "%c%s", ';', "Chứng Bệnh Nan Y (1) Kinh nghiệm 350 Tiềm năng 20 Ngân lượng 500");
                        send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 109, "");
                        me->do_buy("101");
                }
                break;
        case 103:
                if (who->get_legend(TASK_48, 22) && !who->get_legend(TASK_48, 23))
                {
                        if (TASK_LEGEND_D->can_task_add(who) != 1)
                                return;
                        who->set_legend(TASK_48, 23);
                        send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
                        send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 110, "Chứng Bệnh Nan Y (2)");
                        send_user(who, "%c%s", '!', "Nhận nhiệm vụ " HIY "Chứng Bệnh Nan Y (2)");
                }
                break;
        case 104:
                if (who->get_legend(TASK_48, 24) && !who->get_legend(TASK_48, 25))
                {
                        if (!objectp(item = present("Bột Hùng Hoàng", who, 1, MAX_CARRY)))
                        {
                                send_user(who, "%c%s", '!', "Hùng Hoàng Tán đâu?");
                                return;
                        }
                        TASK_LEGEND_D->task_finish(who);
                        item->remove_from_user();
                        destruct(item);
                        who->add_exp(300);
                        who->add_bonus(100);
                        who->add_cash(1800);
                        who->set_legend(TASK_48, 25);
                        send_user(who, "%c%s", ';', "Chứng Bệnh Nan Y (2) Kinh nghiệm 300 công đức 10 Ngân lượng 1800");
                        send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 110, "");
                        me->do_buy("101");
                }
                break;
        case 105:
                if (who->get_legend(TASK_48, 25) && !who->get_legend(TASK_48, 26))
                {
                        if (TASK_LEGEND_D->can_carry_amount(who, 1) != 1)
                                return;
                        if (TASK_LEGEND_D->can_task_add(who) != 1)
                                return;
                        TASK_LEGEND_D->give_item(who, "item/98/0200", 1);
                        who->set_legend(TASK_48, 26);
                        send_user(who, "%c%c%c%w%s", 0x51, 2, 1, TID_NEWBIE_01, "Tân Thủ Thôn");
                        send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2, TID_NEWBIE_01, 111, "Chứng Bệnh Nan Y (3)");
                        send_user(who, "%c%s", '!', "Nhận nhiệm vụ " HIY "Chứng Bệnh Nan Y (3)");
                }
                break;
        }
}
