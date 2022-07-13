#include <ansi.h>
#include <effect.h>
#include <chia_kenh.h>
int add_pet(object who, object pet, int value);
int delete_pet(object me, object pet);

// 函数：命令处理
int main(object me, string arg)
{
        mapping store;
        object *team, obj;
        string *key, what;
        int i, size, value;
        if (me->get_ride())
                return 1;
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        if (me->get_pk())
        {
                notify("Có điểm PK không thể bày bán.");
                return 1;
        }
        if (get_effect(me, EFFECT_USER_PK))
        {
                notify("Còn hiệu quả PK không thể bày bán.");
                return 1;
        }
        if (get_z(me) != 80)
        {
                notify("Chỉ có thể bày bán ở \"Chu\".");
                return 1;
        }
        if (MAIN_D->get_kenh() != KENH_MUABAN && KENH_MUABAN != 0)
        {
                notify("Chỉ có thể bày bán ở Kênh Mua Bán");
                return;
        }
        if ((!arg || arg[0] != '?') && !inside_jumpin(get_z(me), get_x(me), get_y(me), 31) && !inside_jumpin(get_z(me), get_x(me), get_y(me), 32))
        {
                if (me->is_store_open())
                        arg = "close";
                else
                {
                        notify("Chỉ có thể bày bán ở \"Chu\".");
                        return 1;
                }
        }

        if (!arg) // 显示摆摊界面
        {
                if (me->is_store_open())
                {
                        send_user(me, "%c%c%c%c", 0x7b, 0, 1, 1);
                }
                else
                {
                        team = get_range_object_2(me, 2, USER_TYPE);
                        for (i = 0, size = sizeof(team); i < size; i++)
                                if (team[i] && team[i]->is_store_open())
                                {
                                        notify("Bạn cách sạp hàng khác quá gần!");
                                        return 1;
                                }

                        me->init_store_dbase();
                        me->open_store(1);
                        send_user(me, "%c%c%c%c", 0x7b, 0, 1, 1);
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%s", 0x3d, 81, getoid(me), me->get_store_name());
                }

                if (stringp(what = me->get_store_name()))
                        send_user(me, "%c%c%s", 0x7b, 0xff, what);
                if (!mapp(store = me->get_store_dbase()) || !(size = sizeof(key = keys(store))))
                        return 1;

                for (i = 0; i < size; i++)
                {
                        value = to_int(key[i]);
                        if (objectp(number_present(me, value, 1, MAX_CARRY)))
                                send_user(me, "%c%c%d", 0x7b, value, store[key[i]]);
                }
        }
        else if (arg == "open") // 摆摊
        {
                if (!me->is_store_open())
                {
                        team = get_range_object_2(me, 2, USER_TYPE);
                        for (i = 0, size = sizeof(team); i < size; i++)
                                if (team[i] && team[i]->is_store_open())
                                {
                                        notify("Bạn cách sạp hàng khác quá gần!");
                                        return 1;
                                }

                        me->init_store_dbase();
                        me->open_store(1);
                        send_user(me, "%c%c%c%c", 0x7b, 0, 1, 1);
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%s", 0x3d, 81, getoid(me), me->get_store_name());
                        send_user(me, "%s", ECHO + "Bạn bắt đầu bày bán.");
                }
        }
        else if (arg == "close") // 收摊
        {
                if (me->is_store_open())
                {
                        me->init_store_dbase();
                        me->open_store(0);
                        //召唤兽
                        team = me->get_all_beast();
                        for (i = 0, size = sizeof(team); i < size; i++)
                                team[i]->delete ("store");
                        send_user(me, "%c%c%c%c", 0x7b, 0, 0, 1);
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 81, getoid(me), 0);
                        send_user(me, "%s", ECHO + "Bạn kết thúc bày bán.");
                }
        }
        else if (sscanf(arg, "name %s", what)) // 设置商铺名称
        {
                if (strstr(what, "%") != -1)
                {
                        send_user(me, "%c%s", '!', "Ký tự phi pháp!");
                        return;
                }
                if (what)
                        me->set_store_name(what);
        }
        else if (sscanf(arg, "+ %s %d", what, value)) // 展示商品
        {
                obj = find_char(what);
                if (obj && obj->is_pet()) //宠物上架
                {
                        add_pet(me, obj, value);
                        return;
                }
                if (!what || !objectp(obj = present(what, me, 1, MAX_CARRY)))
                {
                        notify("Không tìm được vật phẩm này.");
                        return 1;
                }
                if (obj->get_save("ghep") || obj->get_save("tppc") || obj->get_save_2("diemnhiemvu.score") || obj->get_save("knb") || obj->get_save("qsvst") || obj->get_save("knb2") || obj->get_save("mt150") || obj->get_save("cs123") || obj->get_save("tbpt"))
                {
                        notify(obj->get_name() + " không thể đem bán.");
                        return 1;
                }
                if (obj->get_no_drop() || obj->get_no_give())
                {
                        notify(obj->get_name() + " không thể đem bán.");
                        return 1;
                }
                if (obj->get_bind() == 2 || obj->get_bind() == 4 || obj->get_bind() == 3 || obj->get_bind() == 5)
                {
                        notify(obj->get_name() + " không thể đem bán.");
                        return 1;
                }
                if (obj->get_lock_time() > 0)
                {
                        notify(obj->get_name() + " không thể đem bán.");
                        return 1;
                }
                if (obj->is_locked() > 0)
                {
                        notify(sprintf("%s mất hiệu quả Khoá Càn Khôn còn %d giờ.", obj->get_name(), obj->is_locked() / 3600));
                        return 1;
                }
                if (value > 50000000)
                {
                        notify("Giá nám đã vượt quá 50 triệu lượng.");
                        return 1;
                }
                if (value <= 0)
                {
                        notify("Giá bán này không được chấp nhận.");
                        return 1;
                }
                me->set_store(sprintf("%02d", get_d(obj)), to_int(value));
        }
        else if (sscanf(arg, "- %s", what)) // 放下商品
        {
                obj = find_char(what);
                if (obj && obj->is_pet()) //宠物下架
                {
                        delete_pet(me, obj);
                        return;
                }
                if (!what || !objectp(obj = present(what, me, 1, MAX_CARRY)))
                {
                        notify("Không tìm được vật phẩm này.");
                        return 1;
                }

                me->delete_store(sprintf("%02d", get_d(obj)));
        }
        else if (sscanf(arg, "? %d %s", i, what) == 2) // 查询宠物信息
        {
                if (to_int(what) < 100)
                        return 1;
                obj = find_char(sprintf("%d", i));
                if (!obj || !obj->is_store_open())
                        return 1;
                what = obj->get_store_beast_id(what);
                if (!what)
                        return 1;
                obj = find_char(what);
                if (!obj || !obj->is_pet())
                        return;
                obj->send_info_to(me);
        }
        return 1;
}
//宠物上架
int add_pet(object me, object pet, int value)
{
        int pos;

        if (pet->get_owner() != me)
                return 0;
        if (pet->get_save("no_give") || pet->get_save("no_sell"))
        {
                notify("Sủng vật này không thể bày bán.");
                return 0;
        }
        if (pet->get_save("locktime") > time())
        {
                notify("Sủng vật đang bị khoá.");
                return 0;
        }
        if (pet->get("store"))
        {
                notify("Sủng vật này đang bày bán.");
                return 0;
        }
        pos = me->get_store_beast_pos();
        if (!sizeof(pos))
        {
                notify("Vị trí không đúng.");
                return 0;
        }
        if (value <= 0)
        {
                notify("Giá bán phải lớn hơn 0.");
                return 0;
        }
        if (value > 50000000)
        {
                notify("Giá nám đã vượt quá 50 triệu lượng.");
                return 0;
        }
        me->set_store(pos, value);
        me->set_store_beast_id(pos, sprintf("%x#", getoid(pet)));
        pet->set("store", pos);
        return 1;
}

//宠物下架
int delete_pet(object me, object pet)
{
        string pos;

        if (pet->get_owner() != me)
                return 0;
        if (!(pos = pet->get("store")))
                return 0;
        me->delete_store(pos);
        me->delete_store_beast_id(pos);
        pet->delete ("store");
        return 1;
}
