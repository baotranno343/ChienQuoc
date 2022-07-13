#include <item.h>
#include <ansi.h>
#include <equip.h>

mapping mpHole = ([1:"Thiên Ấn Toàn Năng"]); //装备的孔中镶嵌的宝石
// 函数：命令处理
int set_hole(object who, object item, object diamond);
int mix_diamond_to_hole(object who, object item, object diamond);
int main(object me, string arg)
{
        object *item, who;
        string name, make, result, forge, index;
        int *id;
        int i, flag, level, rate;

        if (!arg)
                return 1;

        item = ({
            0,
            0,
        });
        id = ({
            0,
            0,
        });
        if (sscanf(arg, "0 %x# %x#", id[0], id[1]) == 2)
                flag = 1;
        else if (sscanf(arg, "1 %x# %x#", id[0], id[1]) == 2)
        {

                flag = 2;
        }
        else
        {
                notify("Bạn muốn tinh luyện đồ vật gì?");
                return 1;
        }
        /*
        if( !objectp( who = find_char(name) ) ) return 1;

        if( !who->is_maker() ) return 1;

        if( !inside_screen_2(me, who) )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }

        me->to_front_eachother(who);
*/

        if (flag == 1) //精炼成功率
        {
                for (i = 0; i < 2; i++)
                {
                        if (!objectp(item[i] = present(sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4))) // 物品是否存在？
                        {
                                send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
                                return 1;
                        }
                }
                set_hole(me, item[0], item[1]);
                return 1;
        }
        else
        //精炼装备
        {
                for (i = 0; i < 2; i++)
                {
                        if (!objectp(item[i] = present(sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4))) // 物品是否存在？
                        {
                                send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
                                return 1;
                        }
                }

                mix_diamond_to_hole(me, item[0], item[1]);
                return 1;
        }

        return 1;
}
string get_hole_diamond_name(int idx) { return mpHole[idx]; }
//取得装备的孔的总数
//结构为： 孔的数量|宝石的序号:宝石的序号:...
int set_hole(object me, object item2, object item)
{
        string check_hole, *tach_hole;
        //return 1;
        if (item->get_name() == "Thiên Ấn Toàn Năng")
        {
                if (item2->get_item_type() == ITEM_TYPE_TALISMAN)
                {
                        // item2->add(item->get_unit(), item->get(item->get_unit()));
                        check_hole = item2->get("hole");

                        if (!stringp(check_hole))
                        {
                                item2->set("hole", "1");
                                send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
                                item->remove_from_user();
                                destruct(item);
                        }
                        else
                        {
                                tach_hole = explode(check_hole, "|");
                                if (to_int(tach_hole[0]) == 5)
                                {
                                        notify(sprintf("Bạn đã tạo ấn tối đa ", item->get_name(), item2->get_name()));
                                        return 1;
                                }
                                if ((sizeof(tach_hole)) < 2)
                                        item2->set("hole", sprintf("%d", to_int(tach_hole[0]) + 1));
                                else
                                {
                                        tach_hole[0] = sprintf("%d", to_int(tach_hole[0]) + 1);
                                        item2->set("hole", implode(tach_hole, "|"));
                                }
                                //count_hole = to_int(nTmp[0]);
                                // if (num < 5)
                                // {
                                // 	item2->set("hole", "2|5");
                                // }
                                send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
                                item->remove_from_user();
                                destruct(item);
                                //ITEM_EQUIP_D->mix_diamond_to_hole(me, item2, item);
                        }
                        notify(sprintf("Bạn đã Tạo Ấn cho %s ", item2->get_name()));
                        return 1;
                }
        }
}
int get_hole_amount(object item)
{
        int num;
        string cHole, *nTmp;

        if (!item->get_equip_type() == ITEM_TYPE_TALISMAN)
                return 0;
        cHole = item->get("hole");
        if (!stringp(cHole))
                return 0;
        nTmp = explode(cHole, "|");
        if (!sizeof(nTmp))
                return 0;
        num = to_int(nTmp[0]);
        return num;
}
//取得装备的已用的孔的总数
int get_hole_used_amount(object item)
{
        int num;
        string cHole, *nTmp, *nTmp1;

        if (!item->get_item_type() == ITEM_TYPE_TALISMAN)
                return 0;
        cHole = item->get("hole");
        if (!stringp(cHole))
                return 0;
        nTmp = explode(cHole, "|");
        if ((sizeof(nTmp)) < 2)
                return 0;
        nTmp1 = explode(nTmp[1], ":");
        num = sizeof(nTmp1);
        return num;
        /*
	3|2:3:5
	*/
}
//孔中镶嵌宝石
//增加新镶嵌的石头的话必须维护mpHole

int mix_diamond_to_hole(object who, object item, object diamond)
{
        int i, size, *nTmp, idx, num, total, used, rate;
        string cName, cHole, *nTmp1, *nTmp2, cTmp, *chi_so, idx2;
        //return 1;
        rate = random(7);
        chi_so = ({"hp%", "?%", "c?%", "!%", "-*%", "-c*%", "X@%", "-@%"});
        if (!item->get_item_type() == ITEM_TYPE_TALISMAN || diamond->get_name() != "Thiên Ấn Toàn Năng")
                return 0;
        if ((total = get_hole_amount(item)) == 0)
        {
                send_user(who, "%c%s", '!', "Pháp Bảo này chưa được Tạo Ấn hoặc không thích hợp để lắp！");
                return 0;
        }
        used = get_hole_used_amount(item);
        if (used >= total)
        {
                send_user(who, "%c%s", '!', "Pháp Bảo này chưa Tạo Ấn để khảm！");
                return 0;
        }
        cName = diamond->get_name();
        nTmp = keys(mpHole);
        for (i = 0, size = sizeof(nTmp); i < size; i++)
        {
                if (mpHole[nTmp[i]] == cName)
                        break;
        }
        if (i >= size)
        {
                send_user(who, "%c%s", '!', "Loại đá này này không thích hợp để thiết lập!");
                return 0;
        }
        idx2 = chi_so[rate];
        cHole = item->get("hole");
        nTmp1 = explode(cHole, "|");
        if (sizeof(nTmp1) < 2)
                cTmp = "";
        else
                cTmp = nTmp1[1];

        nTmp2 = explode(cTmp, ":");
        nTmp2 += ({sprintf("%s", idx2)});
        cTmp = implode(nTmp2, ":");
        nTmp1 = ({sprintf("%d", total), cTmp});
        cHole = implode(nTmp1, "|");
        item->set("hole", cHole);

        if (chi_so[rate] == "c?%" || chi_so[rate] == "double" || chi_so[rate] == "!%" || chi_so[rate] == "?%" || chi_so[rate] == "c?%")
        {
                item->add(chi_so[rate], 200);
        }
        else
        {
                item->add(chi_so[rate], 2);
        }

        send_user(who, "%c%d%c", 0x31, getoid(item), 0);
        send_user(who, "%c%s", '!', "Khắc Ấn Thành Công!");
        diamond->remove_from_user();
        destruct(diamond);
        return 1;
}