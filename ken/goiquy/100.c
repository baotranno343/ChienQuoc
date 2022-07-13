#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

// 函数：成品编号
int get_fin_type() { return 1524; }
int get_item_color() { return 1; }
// 函数：镶嵌识别

// 函数：构造处理
void create()
{
        set_name("Gói Quỹ 100");
        set_picid_1(4980);
        set_picid_2(4980);
        set_value(100);
        set_save("diemtlnt", 100);
}

// 函数：获取描述
string get_desc()
{
        return "Khi người chơi sử dụng sẽ nhận được 30 ngày Quỹ 100\nNếu người chơi đã có Quỹ 100 thì sẽ không thể sử dụng cho tới khi hết gói quỹ 100 cũ.\nHãy đến gặp NPC Thiên Nhân ở Chu Quốc để nhận thưởng hằng ngày.";
}

int get_use_effect(object me)
{
        return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{

        if (who->get_save_2("goiquahangngay.100"))
        {
                send_user(who, "%c%s", '!', "Bạn đã có Quỹ 100.");
                return 0;
        }
        send_user(who, "%c%s", '!', "Nhận 30 ngày Quỹ 100 thành công.");
        who->set_save_2("goiquahangngay.100.luot", 30);
        return 1;
}
