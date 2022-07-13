
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5501; }

// 函数：构造处理
void create()
{
        set_name( "文曲星" );
        set_char_photoid(5502);
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();    
}

void do_look( object who )
{
        int status;
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 4, 5501,
                sprintf("%s：\n    欢迎欢迎～～你就是百合提到的新朋友吧？名字叫……\n"
                        "    ‘%s’没错吧？真是不错的名字。\n"
                        "    我将会对你讲解游戏界面操作的基本知识。当然，如果你已经掌握了这些知识，可以直接跳过这一步，找另外几位老师学习其他知识。\n"
                ESC "我希望了解界面操作的相关知识。\ntalk %x# welcome.1\n"
                ESC "你教的我都知道，不需要再学习什么。\nCLOSE\n"
                , me->get_name(), who->get_name(), getoid(me) ) );
}

void do_welcome( string arg )
{
        int flag, date ;
        object who, me, obj;
        string cmd1, cmd2, result;
        me = this_object();
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 0:
                do_look(who);
                break;                
        case 1:
                cmd1 = sprintf("talk %x# welcome.2", getoid(me));
                cmd2 = "CLOSE";
                result = sprintf("%s：\n    你可要认真听罗。现在你可以看到游戏画面左上方有三条不同颜色的长条，其中红色表示你当前的" HIR "气血" NOR "，蓝色表示你当前的" HIR "法力" NOR "，最后绿色那条表示你当前升级所需的" HIR "经验值" NOR "。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\n%s\n"
                        , me->get_name(), cmd1, cmd2 );
                send_user( who, "%c%c%w%s", ':', 4, 5501, result );
                break;
        case 2:
                cmd1 = sprintf("talk %x# welcome.3", getoid(me));
                cmd2 = "CLOSE";
                result = sprintf("%s：\n    游戏画面右上方显示的是当前场景的" HIR "小地图" NOR "。小地图会清晰地标识出你当前所在场景位置，其上方有一个" HIR "坐标显示框" NOR "。此外，在小地图中也会清晰地标示同相邻场景之间的连接，告诉你相邻场景的名称。同时，你也可以在小地图中看到许多 NPC的位置标识，你很容易就能找到各种店铺的老板。\n    对了，你可以尝试一下按"HIR"Ａｌｔ＋Ｍ"NOR"键，这样便能查阅整个战国世界的地图。\n    噢，对了，你是否注意到小地图右上角有一个金黄色的小点？点击它可以将小地图变为" HIR "半透明" NOR "状态。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\n%s\n"
                        , me->get_name(), cmd1, cmd2 );
                send_user( who, "%c%c%w%s", ':', 4, 5501, result );
                break;                                
        case 3:
                cmd1 = sprintf("talk %x# welcome.4", getoid(me));
                cmd2 = "CLOSE";
                result = sprintf("%s：\n    游戏面画左下方有个半透明的信息框，称为" HIR "聊天框" NOR "，所有聊天的内容都会显示在里面。还要注意，聊天信息是被划分为几个不同的频道，包括：" HIR "当前、公众、国家、帮派、门派、队伍、交易、谣言" NOR "七个。\n    在输入想说的话同时，点击'" HIR "当前" NOR "'按钮，会弹出一个频道切换的选项框。在聊天框右下方还有一排小按钮，将鼠标移动到在相关按钮上面，便会显示相关提示信息，根据这些提示你很容易便能了解每个按钮的功用。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\n%s\n"
                        , me->get_name(), cmd1, cmd2 );
                send_user( who, "%c%c%w%s", ':', 4, 5501, result );
                break;              
        case 4:
                cmd1 = sprintf("talk %x# welcome.5", getoid(me));
                cmd2 = "CLOSE";
                result = sprintf("%s：\n    在游戏画面的最下方，从左到右排列着底面写着 F1～F10 的方框，它们即是" HIR "自定义快捷键" NOR "，在游戏中学到的武功招式、生活技能，甚至获得的物品都可以拖曳到此定义快捷键。快捷框一共分为四层，点击一下 F10 快捷框旁边的小箭头，就可以在各层之间来回切换。如果嫌麻烦，按'" HIR "Ａｌｔ＋Z" NOR "'键和'" HIR "Ａｌｔ＋Ａ" NOR "'键同样可以实现这个功能。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\n%s\n"
                        , me->get_name(), cmd1, cmd2 );
                send_user( who, "%c%c%w%s", ':', 4, 5501, result );
                break;
        case 5:
                result = sprintf("%s：\n    没想到这么长的课程内容你还是坚持听下去了，实在是了不起。游戏画面中的大致功能也介绍完了，更多深入的知识还需要你在往后的旅途中慢慢体会。\n    话我也不多说，但如果你还没有找到" HIR "武曲星" NOR "，建议你去拜访他一下，他会教导你许多关于战斗方面的知识。\n"
                        ESC "关闭\nCLOSE\n",  me->get_name() );
                send_user( who, "%c%c%w%s", ':', 4, 5501, result );
                break;        
        }
}