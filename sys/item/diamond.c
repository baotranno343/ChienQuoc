
#include <ansi.h>
#include <item.h>
#include <skill.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：宝石Hợp thành 
void make_diamond( object me, object item, object item2 )
{
        string file;
        int level, rate, p;

        if( !item || !item2 || item == item2 ) return;

        if( !item->is_diamond_3() || !item2->is_diamond_2() ) return;

        item->add_amount(-1);

        level = item2->get_item_level();

        switch( level )
        {
    case 0..3 : rate = 100;  break;
       case 4 : rate = 55;  break;
       case 5 : rate = 50;  break;
       case 6 : rate = 45;  break;
      default : rate = 40;  break;
        }

        if( random(100) < rate )    // Hợp thành 成功
        {
                level = item2->add_item_level(1);

                if( level > 7 )    // 完美宝石
                {
                        if( load_object( file = item2->get_diamond_file() ) )
                        {
                                p = get_d(item2);
                                item2->remove_from_user();
                                destruct(item2);

                                item2 = new( file );
                                if( p = item2->move(me, p) ) 
                                        item2->add_to_user(p);
                                else    destruct(item2);
                        }
                }

                return;
        }

        switch( level )
        {
    case 0..3 : break;
    case 4..5 : item2->add_item_level(-1);  break;
      default : item2->set_item_level(0);  break;
        }
}

// 函数：宝石Hợp thành 
void make_diamond_2( object me, object item, object item2, object item3 )
{
        string file, result;
        int level, rate, p;

        if( !item || !item2 || !item3 || item == item2 || item2 == item3 || item == item3 ) return;

        if( !item->is_diamond_2() || !item2->is_diamond_2() || !item3->is_diamond_2() ) 
        {
                send_user( me, "%c%s", '!', "Hợp thành hoàn mỹ bảo thạch cần bảo thạch không trọn vẹn." );
                return;
        }
        if( get_file_name(item) != get_file_name(item2) || get_file_name(item) != get_file_name(item3) ) 
        {
                send_user( me, "%c%s", '!', "Bảo thạch không cùng loại." );
                return;
        }
        level = item->get_item_level();
        if( level != item2->get_item_level() || level != item3->get_item_level() ) 
        {
                send_user( me, "%c%s", '!', "Bảo thạch không cùng cấp." );
                return;
        }

        send_user( me, "%c%w%c%w%c%w%c%w%c", 0x80, 37111, 1, 37112, 1, 37113, 1, 37114, 1 );

        result = sprintf( "Bạn đem tam khối %s", item->get_name() );

        switch( level )
        {
    case 0..3 : rate = 100;  break;
       case 4 : rate = 65;  break;
       case 5 : rate = 60;  break;
       case 6 : rate = 55;  break;
      default : rate = 50;  break;
        }

        if( random(100) < rate )    // Hợp thành 成功
        {
                item2->remove_from_user();
                destruct(item2);
                item3->remove_from_user();
                destruct(item3);

                level = item->add_item_level(1);

                if( level > 7 )    // 完美宝石
                {
                        if( load_object( file = item->get_diamond_file() ) )
                        {
                                p = get_d(item);
                                item->remove_from_user();
                                destruct(item);

                                item = new( file );

                                result += sprintf( "Hợp thành một khối %s.", item->get_name() );

                                if( p = item->move(me, p) ) 
                                        item->add_to_user(p);
                                else    destruct(item);
                        }
                }
                else    result += sprintf( "Hợp thành một khối %s.", item->get_name() );

                write_user( me, ECHO + result );

                return;
        }

        item->add_item_level(-1);
        item2->add_item_level(-1);
        item3->add_item_level(-1);

        result += "Hợp thành bảo thạch thất bại, bị giảm cấp bậc.";
        write_user( me, ECHO + result );
}

// 函数：宝石Hợp thành (％)
void make_diamond_2_check( object me, object item, object item2, object item3 )
{
        string file, result;
        int level, rate, p;

        if( !item || !item2 || !item3 || item == item2 || item2 == item3 || item == item3 )
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }

        if( !item->is_diamond_2() || !item2->is_diamond_2() || !item3->is_diamond_2() )
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }
        if( get_file_name(item) != get_file_name(item2) || get_file_name(item) != get_file_name(item3) )
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }
        level = item->get_item_level();
        if( level != item2->get_item_level() || level != item3->get_item_level() ) 
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }

        switch( level )
        {
    case 0..3 : rate = 100;  break;
       case 4 : rate = 65;  break;
       case 5 : rate = 60;  break;
       case 6 : rate = 55;  break;
      default : rate = 50;  break;
        }

        send_user( me, "%c%c%c%d", 0x25, 0, rate, 0 );
}

// 函数：装备Hợp thành 
void make_equip( object me, object item, object item2, object item3, object item4 )
{
        object equip, *diamond;
        string *key, prop, prop2, result;
        int level, rate, i, j, size;

        diamond = ({ });

        if( item && item->is_equip() && ( item->get_family() || item->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item;
                level = equip->get_item_level();

                if( level < 3 )
                {
                        if( item2 && ( item2->is_diamond_2() || item2->is_diamond() ) ) diamond += ({ item2 });
                        if( item3 && ( item3->is_diamond_2() || item3->is_diamond() ) ) diamond += ({ item3 });
                        if( item4 && ( item4->is_diamond_2() || item4->is_diamond() ) ) diamond += ({ item4 });
                }
                else 
                {
                        if( item2 && item2->is_diamond() ) diamond += ({ item2 });
                        if( item3 && item3->is_diamond() ) diamond += ({ item3 });
                        if( item4 && item4->is_diamond() ) diamond += ({ item4 });
                }
        }
        else if( item2 && item2->is_equip() && ( item2->get_family() || item2->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item2;
                level = equip->get_item_level();

                if( level < 3 )
                {
                        if( item && ( item->is_diamond_2() || item->is_diamond() ) ) diamond += ({ item });
                        if( item3 && ( item3->is_diamond_2() || item3->is_diamond() ) ) diamond += ({ item3 });
                        if( item4 && ( item4->is_diamond_2() || item4->is_diamond() ) ) diamond += ({ item4 });
                }
                else
                {
                        if( item && item->is_diamond() ) diamond += ({ item });
                        if( item3 && item3->is_diamond() ) diamond += ({ item3 });
                        if( item4 && item4->is_diamond() ) diamond += ({ item4 });
                }
        }
        else if( item3 && item3->is_equip() && ( item3->get_family() || item3->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item3;
                level = equip->get_item_level();

                if( level < 3 )
                {
                        if( item && ( item->is_diamond_2() || item->is_diamond() ) ) diamond += ({ item });
                        if( item2 && ( item2->is_diamond_2() || item2->is_diamond() ) ) diamond += ({ item2 });
                        if( item4 && ( item4->is_diamond_2() || item4->is_diamond() ) ) diamond += ({ item4 });
                }
                else
                {
                        if( item && item->is_diamond() ) diamond += ({ item });
                        if( item2 && item2->is_diamond() ) diamond += ({ item2 });
                        if( item4 && item4->is_diamond() ) diamond += ({ item4 });
                }
        }
        else if( item4 && item4->is_equip() && ( item4->get_family() || item4->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item4;
                level = equip->get_item_level();

                if( level < 3 )
                {
                        if( item && ( item->is_diamond_2() || item->is_diamond() ) ) diamond += ({ item });
                        if( item2 && ( item2->is_diamond_2() || item2->is_diamond() ) ) diamond += ({ item2 });
                        if( item3 && ( item3->is_diamond_2() || item3->is_diamond() ) ) diamond += ({ item3 });
                }
                else
                {
                        if( item && item->is_diamond() ) diamond += ({ item });
                        if( item2 && item2->is_diamond() ) diamond += ({ item2 });
                        if( item3 && item3->is_diamond() ) diamond += ({ item3 });
                }
        }
        else
        {
                send_user( me, "%c%s", '!', "Chỉ có trang bị Môn Phái mới có thể hợp thành." );
                return;
        }

        if( (level + 1) * 10000 > me->get_cash() )
        {
                send_user( me, "%c%s", '!', "Ngân lượng không đủ." );
                return;
        }
        if( !( size = sizeof(diamond) ) )
        {
                if( level < 3 )
                        send_user( me, "%c%s", '!', "Phải có bảo thạch mới có thể hợp thành." );
                else    send_user( me, "%c%s", '!', "Phải có hoàn mỹ bảo thạch mới có thể hợp thành." );

                return;
        }
        for( i = 0; i < size; i ++ )
        {
                for( j = 0; j < i - 1; j ++ ) if( diamond[i] == diamond[j] ) return;    // 是否重复放置？

                if( get_file_name( diamond[0] ) != get_file_name( diamond[i] ) ) 
                {
                        send_user( me, "%c%s", '!', "Bảo thạch không cùng loại." );
                        return;
                }
        }

        if( !( prop = diamond[0]->get_diamond_type() ) )
        {
                send_user( me, "%c%s", '!', "Loại bảo thạch này không thể hợp thành." );
                return;
        }
        switch( prop )
        {
   case "-1-" : // 降低装备条件 50%
                if( !diamond[0]->is_diamond() )    // 必须是完美宝石
                {
                        send_user( me, "%c%s", '!', "Phải có hoàn mỹ bảo thạch mới có thể hợp thành." );
                        return;
                }

                result = sprintf( "Bạn đem %s đồng %s", diamond[0]->get_name(), equip->get_name() );

                rate = 50;

                for( i = 0; i < size; i ++ ) if( diamond[i] )
                {
                        diamond[i]->remove_from_user();
                        destruct( diamond[i] );
                }
                me->add_cash( - (level + 1) * 10000 );  me->add_gold_log( "make", (level + 1) * 10000 );
                me->log_money("Hợp thành ", - (level + 1) * 10000);                
                "/sys/sys/count"->add_use("diamond", (level + 1) * 10000);

                if( random(100) < rate )    // Hợp thành 成功
                {
                        equip->add("-1-", 3);   // 减少３级限制
                        send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );

                        result += sprintf( "Hợp thành %s.", equip->get_name() );

                        write_user( me, ECHO + result );

                        return;
                }
                else    // 失败取消所有
                {
                        equip->remove_from_user();
                        destruct(equip);

                        result += "Hợp thành thất bại, trang bị biến mất.";

                        write_user( me, ECHO + result );

                        return;
                }

                return;
                break;

   case "-2-" : // 恢复耐久度 100%
                if( !diamond[0]->is_diamond() )    // 必须是完美宝石
                {
                        send_user( me, "%c%s", '!', "Phải có hoàn mỹ bảo thạch mới có thể hợp thành." );
                        return;
                }

                result = sprintf( "Bạn đem %s đồng %s", diamond[0]->get_name(), equip->get_name() );

                for( i = 0; i < size; i ++ ) if( diamond[i] )
                {
                        diamond[i]->remove_from_user();
                        destruct( diamond[i] );
                }
                me->add_cash( - (level + 1) * 10000 );  me->add_gold_log( "make", (level + 1) * 10000 );
		"/sys/sys/count"->add_use("diamond", (level + 1) * 10000);
		me->log_money("Hợp thành ", - (level + 1) * 10000);                
                prop = get_file_name(equip);
                equip->set_max_lasting( prop->get_max_lasting() );   // 恢复耐久度
                equip->set_lasting( equip->get_max_lasting() );
                send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );

                result += sprintf( "Hợp thành, độ bền được khôi phục." );

                write_user( me, ECHO + result );

                return;
                break;

      default : break;
        }

        if( equip->get(prop) < 1 )
        {
                send_user( me, "%c%s", '!', "Thuộc tính trang bị hoàn mỹ bảo thạch không hợp." );
                return;
        }

        send_user( me, "%c%w%c%w%c%w%c%w%c", 0x80, 37211, 1, 37212, 1, 37213, 1, 37214, 1 );

        result = sprintf( "Bạn đem %s đồng %s", diamond[0]->get_name(), equip->get_name() );

        switch( level )
        {
    case 0..4 : rate = 100;  break;
       case 5 : rate = 30 + me->get_lucky() / 2 + size * 5 - me->get_pk() * 15;
                rate = range_value(rate, 0, 90);
                break;
       case 6 : rate = 25 + me->get_lucky() / 2 + size * 4 - me->get_pk() * 15;
                rate = range_value(rate, 0, 80);
                break;
       case 7 : rate = 20 + me->get_lucky() / 2 + size * 3 - me->get_pk() * 15;
                rate = range_value(rate, 0, 70);
                break;
       case 8 : rate = 15 + me->get_lucky() / 2 + size * 2 - me->get_pk() * 15;
                rate = range_value(rate, 0, 60);
                break;
       case 9 : rate = 10 + me->get_lucky() / 2 + size * 2 - me->get_pk() * 15;
                rate = range_value(rate, 0, 50);
                break;
      default : send_user( me, "%c%s", '!', equip->get_name() + " cấp bậc quá cao." );
                return;
                break;
        }

        for( i = 0; i < size; i ++ ) if( diamond[i] )
        {
                diamond[i]->remove_from_user();
                destruct( diamond[i] );
        }
        me->add_cash( - (level + 1) * 10000 );  me->add_gold_log( "make", (level + 1) * 10000 );
        me->log_money("Hợp thành ", - (level + 1) * 10000);                
	"/sys/sys/count"->add_use("diamond", (level + 1) * 10000);
        if( random(100) < rate )    // Hợp thành 成功
        {
                prop2 = equip->get_make_prop();
                prop2 = ( prop2 == "" ) ? prop : prop2 + "|" + prop;
                equip->set_make_prop(prop2);
                key = explode(prop2, "|");
                equip->set_item_level( sizeof(key) );

                if( !equip->get_item_color()||equip->get_item_color()==4 ) equip->set_item_color(1);    // 白色装备 -> 蓝色装备
                if (sizeof(key)>=10) equip->set_item_color(2);

                ITEM_EQUIP_D->reset_make_prop_baseon_string(equip, prop2);
                equip->add_to_user(0);
                send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );

                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 37201, 1, OVER_BODY, PF_ONCE );

                result += sprintf( "Hợp thành  %s.", equip->get_name() );

                write_user( me, ECHO + result );

                return;
        }

        switch( level )
        {
    case 0..7 : prop2 = equip->get_make_prop();
                if( ( i = strchr(prop2, '|', -1) ) > 0 ) prop2 = prop2[0..i-1];
                key = explode( prop2, "|" );
                equip->set_make_prop(prop2);
                equip->set_item_level( sizeof(key) );
                ITEM_EQUIP_D->reset_make_prop_baseon_string(equip, prop2);
                equip->add_to_user(0);
                send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );

                result += "Hợp thành thất bại, trang bị bị giảm cấp.";
                break;
       case 8 : equip->set_make_prop("");
                equip->set_item_level(0);
                ITEM_EQUIP_D->reset_make_prop_baseon_string(equip, "");
                equip->add_to_user(0);
                send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );

                result += "Hợp thành thất bại, trang bị trở về trạng thái ban đầu.";
                break;
      default : equip->remove_from_user();
                destruct(equip);
                result += "Hợp thành thất bại, trang bị biến mất.";
                break;
        }

        write_user( me, ECHO + result );
}

// 函数：装备Hợp thành (％)
void make_equip_check( object me, object item, object item2, object item3, object item4 )
{
        object equip, *diamond;
        string *key, prop, prop2, result;
        int level, rate, i, j, size;

        diamond = ({ });

        if( item && item->is_equip() && ( item->get_family() || item->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item;
                level = equip->get_item_level();

                if( equip->get_item_level() < 3 )
                {
                        if( item2 && ( item2->is_diamond_2() || item2->is_diamond() ) ) diamond += ({ item2 });
                        if( item3 && ( item3->is_diamond_2() || item3->is_diamond() ) ) diamond += ({ item3 });
                        if( item4 && ( item4->is_diamond_2() || item4->is_diamond() ) ) diamond += ({ item4 });
                }
                else 
                {
                        if( item2 && item2->is_diamond() ) diamond += ({ item2 });
                        if( item3 && item3->is_diamond() ) diamond += ({ item3 });
                        if( item4 && item4->is_diamond() ) diamond += ({ item4 });
                }
        }
        else if( item2 && item2->is_equip() && ( item2->get_family() || item2->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item2;
                level = equip->get_item_level();

                if( equip->get_item_level() < 3 )
                {
                        if( item && ( item->is_diamond_2() || item->is_diamond() ) ) diamond += ({ item });
                        if( item3 && ( item3->is_diamond_2() || item3->is_diamond() ) ) diamond += ({ item3 });
                        if( item4 && ( item4->is_diamond_2() || item4->is_diamond() ) ) diamond += ({ item4 });
                }
                else
                {
                        if( item && item->is_diamond() ) diamond += ({ item });
                        if( item3 && item3->is_diamond() ) diamond += ({ item3 });
                        if( item4 && item4->is_diamond() ) diamond += ({ item4 });
                }
        }
        else if( item3 && item3->is_equip() && ( item3->get_family() || item3->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item3;
                level = equip->get_item_level();

                if( equip->get_item_level() < 3 )
                {
                        if( item && ( item->is_diamond_2() || item->is_diamond() ) ) diamond += ({ item });
                        if( item2 && ( item2->is_diamond_2() || item2->is_diamond() ) ) diamond += ({ item2 });
                        if( item4 && ( item4->is_diamond_2() || item4->is_diamond() ) ) diamond += ({ item4 });
                }
                else
                {
                        if( item && item->is_diamond() ) diamond += ({ item });
                        if( item2 && item2->is_diamond() ) diamond += ({ item2 });
                        if( item4 && item4->is_diamond() ) diamond += ({ item4 });
                }
        }
        else if( item4 && item4->is_equip() && ( item4->get_family() || item4->get_item_type() == ITEM_TYPE_TALISMAN ) )
        {
                equip = item4;
                level = equip->get_item_level();

                if( equip->get_item_level() < 3 )
                {
                        if( item && ( item->is_diamond_2() || item->is_diamond() ) ) diamond += ({ item });
                        if( item2 && ( item2->is_diamond_2() || item2->is_diamond() ) ) diamond += ({ item2 });
                        if( item3 && ( item3->is_diamond_2() || item3->is_diamond() ) ) diamond += ({ item3 });
                }
                else
                {
                        if( item && item->is_diamond() ) diamond += ({ item });
                        if( item2 && item2->is_diamond() ) diamond += ({ item2 });
                        if( item3 && item3->is_diamond() ) diamond += ({ item3 });
                }
        }
        else
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }

        if( !( size = sizeof(diamond) ) )
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }
        for( i = 0; i < size; i ++ )
        {
                for( j = 0; j < i - 1; j ++ ) if( diamond[i] == diamond[j] ) return;    // 是否重复放置？

                if( get_file_name( diamond[0] ) != get_file_name( diamond[i] ) ) 
                {
                        send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                        return;
                }
        }

        if( !( prop = diamond[0]->get_diamond_type() ) )
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }
        switch( prop )
        {
   case "-1-" : if( !diamond[0]->is_diamond() )    // 必须是完美宝石
                {
                        send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                        return;
                }
                send_user( me, "%c%c%c%d", 0x25, 0, 50, (level + 1) * 10000 );    // 降低装备条件 50%
                return;
                break;
   case "-2-" : if( !diamond[0]->is_diamond() )    // 必须是完美宝石
                {
                        send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                        return;
                }
                send_user( me, "%c%c%c%d", 0x25, 0, 100, (level + 1) * 10000 );    // 恢复耐久度 100%
                return;
                break;
      default : break;
        }

        if( equip->get(prop) < 1 )    // 具有同样属性？
        {
                send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );
                return;
        }

        switch( level )
        {
    case 0..4 : rate = 100;  break;
       case 5 : rate = 30 + me->get_lucky() / 2 + size * 5 - me->get_pk() * 15;
                rate = range_value(rate, 0, 90);
                break;
       case 6 : rate = 25 + me->get_lucky() / 2 + size * 4 - me->get_pk() * 15;
                rate = range_value(rate, 0, 80);
                break;
       case 7 : rate = 20 + me->get_lucky() / 2 + size * 3 - me->get_pk() * 15;
                rate = range_value(rate, 0, 70);
                break;
       case 8 : rate = 15 + me->get_lucky() / 2 + size * 2 - me->get_pk() * 15;
                rate = range_value(rate, 0, 60);
                break;
       case 9 : rate = 10 + me->get_lucky() / 2 + size * 2 - me->get_pk() * 15;
                rate = range_value(rate, 0, 50);
                break;
      default : send_user( me, "%c%c%c%d", 0x25, 0, 0, 0 );    // Hợp thành 到了尽头
                return;
                break;
        }

        send_user( me, "%c%c%c%d", 0x25, 0, rate, (level + 1) * 10000 );
}
