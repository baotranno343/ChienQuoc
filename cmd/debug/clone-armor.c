
#include <ansi.h>
#include <equip.h>

string *ArmorTable0 = ({
        "/item/60/0001",
        "/item/60/0002",
        "/item/60/0003",
        "/item/60/0030",
        "/item/60/0031",
        "/item/60/0032",
        "/item/60/0050",
        "/item/60/0051",
        "/item/60/0052",

        "/item/65/0001",
        "/item/65/0002",
        "/item/65/0003",
        "/item/65/0030",
        "/item/65/0031",
        "/item/65/0032",
        "/item/65/0050",
        "/item/65/0051",
        "/item/65/0052",
});

int sizeof_armor_0 = sizeof(ArmorTable0);

string *ArmorTable0x = ({
        "/item/61/0001",
        "/item/61/0002",
        "/item/61/0003",
        "/item/61/0030",
        "/item/61/0031",
        "/item/61/0032",
        "/item/61/0050",
        "/item/61/0051",
        "/item/61/0052",

        "/item/66/0001",
        "/item/66/0002",
        "/item/66/0003",
        "/item/66/0030",
        "/item/66/0031",
        "/item/66/0032",
        "/item/66/0050",
        "/item/66/0051",
        "/item/66/0052",
});

int sizeof_armor_0x = sizeof(ArmorTable0x);

string *ArmorTable1 = ({
        "/item/60/1040",
        "/item/60/1060",
        "/item/60/1080",
        "/item/60/1100",
        "/item/60/1120",

        "/item/65/1040",
        "/item/65/1060",
        "/item/65/1080",
        "/item/65/1100",
        "/item/65/1120",
});

int sizeof_armor_1 = sizeof(ArmorTable1);

string *ArmorTable1x = ({
        "/item/61/1040",
        "/item/61/1060",
        "/item/61/1080",
        "/item/61/1100",
        "/item/61/1120",

        "/item/66/1040",
        "/item/66/1060",
        "/item/66/1080",
        "/item/66/1100",
        "/item/66/1120",
});

int sizeof_armor_1x = sizeof(ArmorTable1x);

string *ArmorTable2 = ({
        "/item/60/2040",
        "/item/60/2060",
        "/item/60/2080",
        "/item/60/2100",
        "/item/60/2120",

        "/item/65/2040",
        "/item/65/2060",
        "/item/65/2080",
        "/item/65/2100",
        "/item/65/2120",
});

int sizeof_armor_2 = sizeof(ArmorTable2);

string *ArmorTable2x = ({
        "/item/61/2040",
        "/item/61/2060",
        "/item/61/2080",
        "/item/61/2100",
        "/item/61/2120",

        "/item/66/2040",
        "/item/66/2060",
        "/item/66/2080",
        "/item/66/2100",
        "/item/66/2120",
});

int sizeof_armor_2x = sizeof(ArmorTable2x);

string *ArmorTable3 = ({
        "/item/60/3040",
        "/item/60/3060",
        "/item/60/3080",
        "/item/60/3100",
        "/item/60/3120",

        "/item/65/3040",
        "/item/65/3060",
        "/item/65/3080",
        "/item/65/3100",
        "/item/65/3120",
});

int sizeof_armor_3 = sizeof(ArmorTable3);

string *ArmorTable3x = ({
        "/item/61/3040",
        "/item/61/3060",
        "/item/61/3080",
        "/item/61/3100",
        "/item/61/3120",

        "/item/66/3040",
        "/item/66/3060",
        "/item/66/3080",
        "/item/66/3100",
        "/item/66/3120",
});

int sizeof_armor_3x = sizeof(ArmorTable3x);

// 函数：命令处理
int main( object me, string arg )
{
        object item;
        string *weapon, file;
        string cmd1, cmd2, cmd3, cmd4;
        int family, z, x, y, p, i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        family = to_int(arg);

        if( family < 1 )
        {
                cmd1 = "clone-armor 1\n";
                cmd2 = "clone-armor 2\n";
                cmd3 = "clone-armor 3\n";
                cmd4 = "clone-armor 4\n";
                send_user( me, "%c%s", ':', "您想复制哪种门派的衣物？(" + ( me->get_gender() == 1 ? "男性" : "女性" ) + ")\n" 
                        ESC "普通\n" + cmd1 +
                        ESC "Thục Sơn/Cấm Vệ Quân/Đào Hoa Nguyên\n" + cmd2 +
                        ESC "Đường Môn/Vân Mộng Cốc\n" + cmd3 +
                        ESC "Mao Sơn/Côn Luân\n" + cmd4 +
                        ESC "放弃。\nCLOSE\n" );
                return 1;
        }

        if( me->get_gender() == 1 ) switch( family )
        {
      default : weapon = ArmorTable0;  size = sizeof_armor_0;  break;
       case 2 : weapon = ArmorTable1;  size = sizeof_armor_1;  break;
       case 3 : weapon = ArmorTable2;  size = sizeof_armor_2;  break;
       case 4 : weapon = ArmorTable3;  size = sizeof_armor_3;  break;
        }
        else switch( family )
        {
      default : weapon = ArmorTable0x;  size = sizeof_armor_0x;  break;
       case 2 : weapon = ArmorTable1x;  size = sizeof_armor_1x;  break;
       case 3 : weapon = ArmorTable2x;  size = sizeof_armor_2x;  break;
       case 4 : weapon = ArmorTable3x;  size = sizeof_armor_3x;  break;
        }

        z = get_z(me);  x = get_x(me);  y = get_y(me);

        for( i = 0; i < size; i ++ )
        {
                file = weapon[i];
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        item = new(file);
                        item->add_to_scene(z, p / 1000, p % 1000);
                }
        }

        return 1;
}
