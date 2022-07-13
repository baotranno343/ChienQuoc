
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>

inherit OFFICER;
string * goodname = ({ "/item/97/9701", "/item/97/9702", "/item/97/9703", "/item/97/9704", "/item/97/9705", "/item/97/9706", "/item/97/9707", "/item/97/9708", "/item/97/9709", "/item/97/9720", "/item/97/9721", "/item/97/9722", "/item/97/9723", "/item/97/9724", "/item/97/9725", "/item/97/9726", "/item/97/9727", "/item/97/9728", "/item/97/9729", "/item/97/9730", "/item/97/9731", "/item/97/9750", "/item/97/9751", "/item/97/9752", "/item/97/9753", "/item/97/9754", "/item/97/9770", "/item/97/9771", });

int * place = ({ 001, 002, 003, 011, 014, 012, 013, 015, 021, 041, 043, 042, 082, 111, 112, 132, 131, 139, 142, 161, 162, 173, 182, 211, 231, 241, 242, 243, 261, 264, 265, 266, 271, 272, 281, 282, 289, 324, 371, 375, 054, 081, 141, 171, 172, 174, 262, 263, 269, 273, 283, 163, 164, 165, });

// 函数：小贩识别
int is_seller() { return 2; }

// 函数：获取人物造型
int get_char_picid() { return 5420; }

// 重设商品
void reset_good();

// 函数：构造处理
void create()
{
        set_name("Vân Du Thương Nhân");

        reset_good();

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        LIST_CMD->main( who, sprintf( "%x#", getoid( this_object() ) ) );
}


void reset() 
{
        int z, x, y, p, size;
        size = sizeof(place);
        z = place[random(size)];        

        if( p = get_xy_point(z, IS_CHAR_BLOCK) )
        {
                x = ( p % 1000000 ) / 1000, y = p % 1000;
                this_object()->add_to_scene(z, x, y, 3);
                TASK_MASTER_D->set_seller_locate(x, y, z);
        }
}

void do_after_buy()
{
        object me = this_object();
        __FILE__->do_after_buy_callout(me);        
}

void do_after_buy_callout(object me)
{        
        me->remove_from_scene();                
        set_z(me, 0);
        TASK_MASTER_D->set_seller_locate(0, 0, 0);    
        CALLOUT_D->seller_wait_callout();
}

void reset_good()
{
        string * good, file;
        mapping goodlist;
        int size, i;
        object me = this_object();
        good = copy(goodname);
        me->set_2( "list", ([
                "01" : 1,
                "02" : 1,
                "03" : 1,
                "04" : 1,                        
        ]) );
        goodlist = ([]);
        for (i=0;i<4;i++)
        {
                size = sizeof(good);
                file = good[random(size)];
                good -= ({ file });
                goodlist[sprintf("%02d", i+1)] = file;
        }
        me->set_2( "good", goodlist);
}