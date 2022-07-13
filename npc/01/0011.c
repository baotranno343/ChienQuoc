
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <skill.h>
#include <task.h>

inherit OFFICER;

string * skillname = ({ "基本拳脚", "基本刀法", "基本剑法", "基本枪法", "基本棍法", "暗器投射", });

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 4143; }

// 函数：构造处理
void create()
{
        set_name( "武曲星" );
        set_char_photoid(4144);
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();    
}


void do_look( object who )
{
        int status, date;
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 4, 4153, 
		sprintf("%s：\n    啊，你就是%s吧。我在登录名册上已经见过你的名字，看你资质不错，应该是个练武的好材料。\n    长话短说，我会向你说明相关人物属性的理论知识和实际战斗的技巧。听懂的话课程马上要开始！\n"
                ESC "继续\ntalk %x# welcome.1\n"
                ESC "关闭\nCLOSE\n",  me->get_name(), who->get_name(), getoid(me) ) );           
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        object map, map2, who, npc, item, *inv, *gift;
        int z, z2, x, y, p;
        int flag, date , status, i, size;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, result;
        who = this_player();
        flag = to_int(arg);
        status = who->get("wuquxing");
        who->set_time( "talk", 0);
        switch(flag)
        {
        case 1:
                cmd1 = sprintf("talk %x# welcome.2", getoid(me));
                cmd2 = "CLOSE";
                result = sprintf("%s：\n    "HIR "体魄、精神、力量、耐力、敏捷" NOR "是影响人物能力的五个最根本的属性。\n    "HIR "体魄" NOR "影响着你的" HIR "气血" NOR "，体魄越高，气血也会越多。\n    气血吗？气血就是你的生命力，当你每次战斗中" HIR "受到的伤害都会直接扣除你等量的气血" NOR "。当你的气血值变为零的时候，你便会挂掉，这点必须注意！\n    "HIR "精神" NOR "决定了你的" HIR "最大法力、法术攻击力和法术防御力" NOR "，这个属性对于擅长法术的" HIR "门派" NOR "来说是至关重要的。施放法术造成的伤害、防御法术攻击的伤害，都会受到精神值所限制。\n    "HIR "力量" NOR "能体现出你物理攻击能力的高低，力量越高，" HIR "物理攻击力" NOR "便会越强，战斗中对敌人所造成的伤害便会越大。\n    "HIR "耐力" NOR "决定了你的物理防御能力高低，这个属性与力量是相对的，你的耐力越高，敌人对你所造成的" HIR "物理伤害" NOR "便会越低。\n    "HIR "敏捷" NOR "就是速度，能否迅速地回避敌人的攻击、能否准确地命中敌人都由敏捷来决定。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\n%s\n", me->get_name(), cmd1, cmd2 );
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;
        case 2:
                cmd1 = sprintf("talk %x# welcome.3", getoid(me));
                result = sprintf("%s：\n    "HIR "体魄、精神、力量、耐力、敏捷" NOR "是影响人物能力的五个最根本的属性。\n    " HIR "体魄" NOR "影响着你的" HIR "气血" NOR "，体魄越高，气血也会越多。\n    气血吗？气血就是你的生命力，当你每次战斗中" HIR "受到的伤害都会直接扣除你等量的气血" NOR "。当你的气血值变为零的时候，你便会挂掉，这点必须注意！\n    " HIR "精神" NOR "决定了你的" HIR "最大法力、法术攻击力和法术防御力" NOR "，这个属性对于擅长法术的" HIR "门派" NOR "来说是至关重要的。施放法术造成的伤害、防御法术攻击的伤害，都会受到精神值所限制。\n    "HIR "力量" NOR "能体现出你物理攻击能力的高低，力量越高，" HIR "物理攻击力" NOR "便会越强，战斗中对敌人所造成的伤害便会越大。\n    " HIR "耐力" NOR "决定了你的物理防御能力高低，这个属性与力量是相对的，你的耐力越高，敌人对你所造成的" HIR "物理伤害" NOR "便会越低。\n    " HIR "敏捷" NOR "就是速度，能否迅速地回避敌人的攻击、能否准确地命中敌人都由敏捷来决定。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), cmd1 );
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;             
        case 3:
                cmd1 = sprintf("talk %x# welcome.4", getoid(me));
                result = sprintf("%s：\n    五个基本属性已经讲解完了，现在请你打开" HIR "人物属性界面" NOR "，就是下方有一个小人的按钮，或者直接按'" HIR "Ａｌｔ＋Ｗ" NOR "'，这是对应人物属性界面的快捷键。\n    当你的等级提升后，五个属性都会自动提升一点。\n    注意每项属性旁边出现的小箭头。每当等级提升，除了各项属性会自动提升一点外，还会得到额外的4个属性点奖励，这些奖励点会保留在属性框中。单击一下对应属性旁边的小加号，便消耗一个属性奖励点，该奖励点会分配到相对应的基本属性中。\n    记住，分配了的属性点是无法再反悔的，如何合理地分配属性点也是一门相当高深的学问。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), cmd1 );
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;           
        case 4:
                cmd1 = sprintf("talk %x# welcome.5", getoid(me));
                cmd2 = sprintf("talk %x# welcome.6", getoid(me));
                cmd3 = sprintf("talk %x# welcome.7", getoid(me));
                cmd4 = sprintf("talk %x# welcome.8", getoid(me));
                cmd5 = sprintf("talk %x# welcome.9", getoid(me));         
                result = sprintf("%s：\n    关于能力属性部分我已经讲解完了，还有没有什么问题？\n", me->get_name() );
                result += sprintf( ESC "法术攻击力？物理攻击力？有什么区别吗？\n%s\n", cmd1 );
                result += sprintf( ESC "门派是什么？\n%s\n", cmd2 );
                result += sprintf( ESC "怎样才是最好的配点？\n%s\n", cmd3 );                        
                result += sprintf(
                        ESC "如何获得潜能？\n%s\n"
                        ESC "我都懂了，继续下一个课程吧\n%s\n", 
                        cmd4, cmd5 );
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;                
        case 5:
                cmd1 = sprintf("talk %x# welcome.4", getoid(me));
                result = sprintf("%s：\n    问得好！这两个概念你必须要区分清楚。\n    所谓的法术攻击力，就是使用各种法术攻击时所能造成的伤害，当然，这个伤害值会受到被攻击者的法术防御力影响。通常的法术譬如" HIR "五雷咒、驱魔诀" NOR "等等，都是一种" HIR "远程攻击" NOR "的手段。\n    由力量属性决定的物理攻击力，则应用于所有非法术技能攻击的计算中。包括普通的攻击、武功招式使用，都是以物理攻击力来计算的，制约着物理伤害的大小便是物理防御力。”\n"
                        ESC "返回\n%s\n", me->get_name(), cmd1 );                
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;        
        case 6:
                cmd1 = sprintf("talk %x# welcome.4", getoid(me));
                result = sprintf("%s：\n    不错，这么快就看到重点了。在往后的游戏中，当你达到 10 级以后，便有资格拜入门派学习更高深的武艺。如今天下一共有七大门派，分别是：‘" HIR "桃花源、禁卫军、蜀山、唐门、茅山、昆仑山和云梦泽" NOR "’。七个门派各有特色，并分散在天下各地。到时你可以去找驻留在" HIR "新手村的门派向导" NOR "，他会送你到门派去的。\n"
                        ESC "返回\n%s\n", me->get_name(), cmd1 );                
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;                                                                                                
        case 7:
                cmd1 = sprintf("talk %x# welcome.4", getoid(me));
                result = sprintf("%s：\n    我之前也说过，这是一个相当高深的学问。有没有最好的配点方案还难以定论。不过通常以" HIR "物理攻击" NOR "为主的门派就建议多些将点数分配给力量、耐力、体魄上，而注重"HIR"法术攻击"NOR"的门派则建议将点数分配在精神上。当然这些只是个人观点，如何分配点数还要由你自己决定。\n"
                        ESC "返回\n%s\n", me->get_name(), cmd1 );                
                status |= 4;
                who->set("wuquxing", status);
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;                
        case 8:
                cmd1 = sprintf("talk %x# welcome.4", getoid(me));
                result = sprintf("%s：\n    这很简单，每次你消灭怪物后，自然会得到一定的潜能奖励，但是这个奖励会随着你与怪物之间的等级差距有所修正。你与怪物之间的等级差距越大，所能获得的潜能会越少。一些特殊的药品也能增加你的潜能值，只不过这种药品相当罕见。\n"
                        ESC "返回\n%s\n", me->get_name(), cmd1 );                
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;                                                                                                    
        case 9:
                cmd1 = sprintf("talk %x# welcome.10", getoid(me));
                result = sprintf("%s：\n    好，继续！谈到战斗，就离不开战斗时所运用的各种武功招式。要学会这些招式，就必须先从相应的" HIR "技能修炼" NOR "开始，只要将某个技能修炼到一定的等级，自然可以领会其包含的" HIR "武功" NOR "。\n    所有的武功技能在每个门派的师傅处都能学到，不过相应的代价就是要消耗定量的" HIR "潜能" NOR "与金钱。随着修炼技能等级的越高，这个消耗便会越大。\n    除了门派武功之外，你加入帮派后还可以学习到一些特殊的帮派技能武功。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), cmd1 );                
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;       
        case 10:
                result = sprintf("%s：\n    能教你的我都教了，以后你也许还会面对更多的难关。一切都得看自己的造化。还有什么不懂的地方就去拜访其他几位老师。如果要离开仙灵岛的话，你找百合仙子帮忙就可以了。\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), cmd1 );                
                send_user( who, "%c%c%w%s", ':', 4, 4153, result );
                break;                                    
        }
}
