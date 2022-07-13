
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <skill.h>
#include <action.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 6009; }

// 函数：构造处理
void create()
{
        set_name( "Bách Hợp Tiên Tử" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
        int status;
        object me = this_object();
        send_user( who, "%c%c%s", ':', 2,
                sprintf("%s：\n    恭喜你，这么快就通过了课程考验，一定获得不少老师的奖励吧？你见到我姐姐了吗？她可是个大美人呀～～即美丽又娴惠，一直都是我憧憬的目标啊～～\n    嘻嘻，对不起，我又跑题了。\n"
                ESC "继续\ntalk %x# welcome.1", me->get_name(), getoid(me) ) );        
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int date, p, z, x, y, oldz, i, size, flag;
        object who, obj, oldcity, *inv, *gift;
        who = this_player();
        who->set_time( "talk",  0);                             
        flag = to_int(arg);
        switch(flag)
        {
        case 1:
                send_user( who, "%c%c%s", ':', 2,
                        sprintf("%s：\n    快乐的时间总是短暂的，这么快就要分别我还真是舍不得……这是我临别之前的一点心意……离开这里后，你就会到达一个叫" HIY "新手村" NOR "的小村庄，我" HIY "爷爷" NOR "就住在那里。我也事先与爷爷打过招呼了，只要你把这封介绍信交给他就可以了，如果今后遇到什么困难，尽管向爷爷请教，他都会帮助你的。\n"
                        ESC "继续\ntalk %x# welcome.2", me->get_name(), getoid(me) ) );                        
                break;
        case 2:
                send_user( who, "%c%c%s", ':', 2,
                        sprintf("%s：\n    传送法术马上就要发动了，不要紧张，深呼吸，闭上双眼～开始罗～～～\n"
                        ESC "关闭\ntalk %x# welcome.3", me->get_name(), getoid(me) ) );                        
                break;
        case 3:                             
                send_user( who, "%c%d", ':', 0);
                  // 清除新手登录标志                
                who->delete_save("fighter.status");
                // 检查身上的物品
                gift = ({ });
                inv = who->get_all_equip();
                inv -= ({ 0});
                for( i = 0, size = sizeof(inv); i < size; i ++ )
                {
                        if (inv[i]->get_value()==0)
                        {
                                gift += ({ inv[i] });
                        }
                }        
                inv = all_inventory(who, 1, MAX_CARRY);
                inv -= ({ 0});
                for( i = 0, size = sizeof(inv); i < size; i ++ )
                {
                        if (inv[i]->get_value()==0)
                        {
                                gift += ({ inv[i] });
                        }
                }
                for( i = 0, size = sizeof(gift); i < size; i ++ )
                {
                        gift[i]->remove_from_user();
                        destruct(gift[i]);                        
                }
                USER_ENERGY_D->count_all_prop(who);
                oldz = get_z(who);
                oldcity = get_map_object(oldz);                
        
                MAP_D->add_to_void(who);    // 移入 VOID 场景  // 新手村！
                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(who), 
                        51141, 1, OVER_BODY, 51142, 1, OVER_BODY, 51143, 1, UNDER_FOOT, 51144, 1, UNDER_FOOT, PF_ONCE );
                who->delete_save_2("Newbie");    // "Newbie.Login"
                NEWBIE->destruct_virtual_map(oldcity, oldz);
                
                break;
        }
}