
#include <ansi.h>
#include <equip.h>

string *WeaponTable0 = ({
        "/item/70/0001",
        "/item/70/0010",
        "/item/70/0020",
        "/item/70/1030",
        "/item/70/1040",
        "/item/70/1050",
        "/item/70/1060",
        "/item/70/1070",
        "/item/70/1080",
        "/item/70/1090",
        "/item/70/1100",
        "/item/70/1110",
        "/item/70/1120",
});

int sizeof_weapon_0 = sizeof(WeaponTable0);

string *WeaponTable1 = ({
        "/item/71/0001",
        "/item/71/0010",
        "/item/71/0020",
        "/item/71/1030",
        "/item/71/1040",
        "/item/71/1050",
        "/item/71/1060",
        "/item/71/1070",
        "/item/71/1080",
        "/item/71/1090",
        "/item/71/1100",
        "/item/71/1110",
        "/item/71/1120",
        "/item/71/1130",
});

int sizeof_weapon_1 = sizeof(WeaponTable1);

string *WeaponTable2 = ({
        "/item/72/0001",
        "/item/72/0010",
        "/item/72/0020",
        "/item/72/1030",
        "/item/72/1040",
        "/item/72/1050",
        "/item/72/1060",
        "/item/72/1070",
        "/item/72/1080",
        "/item/72/1090",
        "/item/72/1100",
        "/item/72/1110",
        "/item/72/1120",
});

int sizeof_weapon_2 = sizeof(WeaponTable2);

string *WeaponTable3 = ({
        "/item/76/0001",
        "/item/76/0010",
        "/item/76/0020",
        "/item/76/1030",
        "/item/76/1040",
        "/item/76/1050",
        "/item/76/1060",
        "/item/76/1070",
        "/item/76/1080",
        "/item/76/1090",
        "/item/76/1100",
        "/item/76/1110",
        "/item/76/1120",
});

int sizeof_weapon_3 = sizeof(WeaponTable3);

string *WeaponTable4 = ({
        "/item/74/0001",
        "/item/74/0010",
        "/item/74/0020",
        "/item/74/1030",
        "/item/74/1040",
        "/item/74/1050",
        "/item/74/1060",
        "/item/74/1070",
        "/item/74/1080",
        "/item/74/1090",
        "/item/74/1100",
        "/item/74/1110",
        "/item/74/1120",
});

int sizeof_weapon_4 = sizeof(WeaponTable4);

string *WeaponTable5 = ({
        "/item/75/0001",
        "/item/75/0010",
        "/item/75/0020",
        "/item/75/1030",
        "/item/75/1040",
        "/item/75/1050",
        "/item/75/1060",
        "/item/75/1070",
        "/item/75/1080",
        "/item/75/1090",
        "/item/75/1100",
        "/item/75/1110",
        "/item/75/1120",
});

int sizeof_weapon_5 = sizeof(WeaponTable5);

string *WeaponTable6 = ({
        "/item/77/0001",
        "/item/77/0010",
        "/item/77/0020",
        "/item/77/1030",
        "/item/77/1040",
        "/item/77/1050",
        "/item/77/1060",
        "/item/77/1070",
        "/item/77/1080",
        "/item/77/1090",
        "/item/77/1100",
        "/item/77/1110",
        "/item/77/1120",
});

int sizeof_weapon_6 = sizeof(WeaponTable6);

string *WeaponTable7 = ({
        "/item/78/0001",
        "/item/78/0010",
        "/item/78/0020",
        "/item/78/1030",
        "/item/78/1040",
        "/item/78/1050",
        "/item/78/1060",
        "/item/78/1070",
        "/item/78/1080",
        "/item/78/1090",
        "/item/78/1100",
        "/item/78/1110",
        "/item/78/1120",
});

int sizeof_weapon_7 = sizeof(WeaponTable7);

string *WeaponTable8 = ({
        "/item/79/0001",
        "/item/79/0010",
        "/item/79/0020",
        "/item/79/1030",
        "/item/79/1040",
        "/item/79/1050",
        "/item/79/1060",
        "/item/79/1070",
        "/item/79/1080",
        "/item/79/1090",
        "/item/79/1100",
        "/item/79/1110",
        "/item/79/1120",
});

int sizeof_weapon_8 = sizeof(WeaponTable8);

// 函数：命令处理
int main( object me, string arg )
{
        object item;
        string *weapon, file;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8, cmd9;
        int family, z, x, y, p, i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        family = to_int(arg);

        if( family < 1 )
        {
                cmd1 = "clone-weapon 1\n";
                cmd2 = "clone-weapon 2\n";
                cmd3 = "clone-weapon 3\n";
                cmd4 = "clone-weapon 4\n";
                cmd5 = "clone-weapon 5\n";
                cmd6 = "clone-weapon 6\n";
                cmd7 = "clone-weapon 7\n";
                cmd8 = "clone-weapon 8\n";
                cmd9 = "clone-weapon 9\n";
                send_user( me, "%c%s", ':', "您想复制哪种门派的武器？\n"
                        ESC "Đào Hoa Nguyên\n" + cmd1 +
                        ESC "Đường Môn\n" + cmd2 +
                        ESC "Thục Sơn (Đao)\n" + cmd3 +
                        ESC "Thục Sơn(Kiếm)\n" + cmd4 +
                        ESC "Cấm Vệ Quân (Thương)\n" + cmd5 +
                        ESC "Cấm Vệ Quân (Côn)\n" + cmd6 +
                        ESC "Mao Sơn\n" + cmd7 +
                        ESC "Côn Luân\n" + cmd8 +
                        ESC "Vân Mộng Cốc\n" + cmd9 +
                        ESC "放弃。\nCLOSE\n" );
                return 1;
        }

        switch( family )
        {
      default : weapon = WeaponTable0;  size = sizeof_weapon_0;  break;
       case 2 : weapon = WeaponTable1;  size = sizeof_weapon_1;  break;
       case 3 : weapon = WeaponTable2;  size = sizeof_weapon_2;  break;
       case 4 : weapon = WeaponTable3;  size = sizeof_weapon_3;  break;
       case 5 : weapon = WeaponTable4;  size = sizeof_weapon_4;  break;
       case 6 : weapon = WeaponTable5;  size = sizeof_weapon_5;  break;
       case 7 : weapon = WeaponTable6;  size = sizeof_weapon_6;  break;
       case 8 : weapon = WeaponTable7;  size = sizeof_weapon_7;  break;
       case 9 : weapon = WeaponTable8;  size = sizeof_weapon_8;  break;
        }

        z = get_z(me);  x = get_x(me);  y = get_y(me);

        for( i = 0; i < size; i ++ )
        {
                file = weapon[i];
                if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
                {
                        item = new(file);
                        item->set_hide(0);
                        item->add_to_scene(z, p / 1000, p % 1000);
                }
        }

        return 1;
}
