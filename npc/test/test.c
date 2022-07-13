
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 5; }

// 函数：获取人物造型
int get_char_picid() { return 9004; }

// 函数：构造处理
void create()
{
        set_name("Hỗ Trợ Open Beta");
        set_city_name("Chu Quốc");

        set_2("good", (["01":"/tran/test/exp",
                          "02":"/tran/test/nganluong",
                          "03":"/tran/test/nganluongkhoa",
                          "04":"/tran/test/knb",
                          "05":"/tran/test/knbkhoa",
                          "06":"/item/test/tuihoangkimtanthucap60",
                          "07":"/ken/hotrotanthu/bikipnghe/coquan",
                          "08":"/ken/hotrotanthu/bikipnghe/daubep",
                          "09":"/ken/hotrotanthu/bikipnghe/dieukhac",
                          "10":"/ken/hotrotanthu/bikipnghe/luyendon",
                          "11":"/ken/hotrotanthu/bikipnghe/maymac",
                          "12":"/ken/hotrotanthu/bikipnghe/renduc",

        ]));

        setup();
}

// 函数：对话处理
void do_look(object who)
{
        "/quest/help"->send_help_tips(who, 41);
        "/cmd/std/look"->main(who, sprintf("%x#", getoid(this_object())));
}
