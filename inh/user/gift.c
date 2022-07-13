
class Gift 
{
        int Con;                        // 体魄，根骨   Constitution
        int Spi;                        // 精神，灵性   Spirituality
        int Str;                        // 力量         Strength
        int Cps;                        // 耐力，定力   Composure
        int Dex;                        // 敏捷，机敏   Dexterity
}

// 先天天赋
private class Gift Gift1 = new( class Gift );
// 后天天赋
private class Gift Gift2 = new( class Gift );
// 总体天赋
private static class Gift GiftSum = new( class Gift );

private int Hair;			// 头发
private int HairColor;			// 头发的颜色

private int PersonPhoto;		// 头像

int get_login_flag();
int get_level();

private void count_con();
private void count_spi();
private void count_str();
private void count_cps();
private void count_dex();

// -------------------------------------------------------------

// 函数：获取先天体魄
int get_con_1() { return Gift1->Con; }

// 函数：获取先天精神
int get_spi_1() { return Gift1->Spi; }

// 函数：获取先天力量
int get_str_1() { return Gift1->Str; }

// 函数：获取先天耐力
int get_cps_1() { return Gift1->Cps; }

// 函数：获取先天敏捷
int get_dex_1() { return Gift1->Dex; }

// 函数：设置先天体魄
int set_con_1( int gift )
{
        Gift1->Con = gift;
        count_con();
        return gift;
}

// 函数：设置先天精神
int set_spi_1( int gift )
{
        Gift1->Spi = gift;
        count_spi();
        return gift;
}

// 函数：设置先天力量
int set_str_1( int gift )
{
        Gift1->Str = gift;
        count_str();
        return gift;
}

// 函数：设置先天耐力
int set_cps_1( int gift )
{
        Gift1->Cps = gift;
        count_cps();
        return gift;
}

// 函数：设置先天敏捷
int set_dex_1( int gift )
{
        Gift1->Dex = gift;
        count_dex();
        return gift;
}

// 函数：增添先天体魄
int add_con_1( int gift ) { return set_con_1( Gift1->Con + gift ); }

// 函数：增添先天精神
int add_spi_1( int gift ) { return set_spi_1( Gift1->Spi + gift ); }

// 函数：增添先天力量
int add_str_1( int gift ) { return set_str_1( Gift1->Str + gift ); }

// 函数：增添先天耐力
int add_cps_1( int gift ) { return set_cps_1( Gift1->Cps + gift ); }

// 函数：增添先天敏捷
int add_dex_1( int gift ) { return set_dex_1( Gift1->Dex + gift ); }

// -------------------------------------------------------------

// 函数：获取后天体魄
int get_con_2() { return Gift2->Con; }

// 函数：获取后天精神
int get_spi_2() { return Gift2->Spi; }

// 函数：获取后天力量
int get_str_2() { return Gift2->Str; }

// 函数：获取后天耐力
int get_cps_2() { return Gift2->Cps; }

// 函数：获取后天敏捷
int get_dex_2() { return Gift2->Dex; }

// 函数：设置后天体魄
int set_con_2( int gift )
{
        Gift2->Con = gift;
        count_con();
        return gift;
}

// 函数：设置后天精神
int set_spi_2( int gift )
{
        Gift2->Spi = gift;
        count_spi();
        return gift;
}

// 函数：设置后天力量
int set_str_2( int gift )
{
        Gift2->Str = gift;
        count_str();
        return gift;
}

// 函数：设置后天耐力
int set_cps_2( int gift )
{
        Gift2->Cps = gift;
        count_cps();
        return gift;
}

// 函数：设置后天敏捷
int set_dex_2( int gift )
{
        Gift2->Dex = gift;
        count_dex();
        return gift;
}

// 函数：增添后天体魄
int add_con_2( int gift ) { return set_con_2( Gift2->Con + gift ); }

// 函数：增添后天精神
int add_spi_2( int gift ) { return set_spi_2( Gift2->Spi + gift ); }

// 函数：增添后天力量
int add_str_2( int gift ) { return set_str_2( Gift2->Str + gift ); }

// 函数：增添后天耐力
int add_cps_2( int gift ) { return set_cps_2( Gift2->Cps + gift ); }

// 函数：增添后天敏捷
int add_dex_2( int gift ) { return set_dex_2( Gift2->Dex + gift ); }

// -------------------------------------------------------------

// 函数：获取总体体魄
int get_con() { return GiftSum->Con; }

// 函数：获取总体精神
int get_spi() { return GiftSum->Spi; }

// 函数：获取总体力量
int get_str() { return GiftSum->Str; }

// 函数：获取总体耐力
int get_cps() { return GiftSum->Cps; }

// 函数：获取总体敏捷
int get_dex() { return GiftSum->Dex; }

// 函数：统计总体天赋
void count_gift()
{
        count_con();
        count_spi();
        count_str();
        count_cps();
        count_dex();
}

// -------------------------------------------------------------

// 函数：统计总体体魄
private void count_con()
{
        int gift = Gift1->Con + Gift2->Con + get_level();

        if( GiftSum->Con != gift && get_login_flag() > 1 ) 
        {
                send_user( this_object(), "%c%c%w", 0x3d, 10, gift );
                USER_ENERGY_D->count_max_hp( this_object() );
        }
        GiftSum->Con = gift;
}

// 函数：统计总体精神
private void count_spi()
{
        int gift = Gift1->Spi + Gift2->Spi + get_level();

        if( GiftSum->Spi != gift && get_login_flag() > 1 ) 
        {
                send_user( this_object(), "%c%c%w", 0x3d, 11, gift );
                USER_ENERGY_D->count_max_mp( this_object() );
        }
        GiftSum->Spi = gift;
}

// 函数：统计总体力量
private void count_str()
{
        int gift = Gift1->Str + Gift2->Str + get_level();

        if( GiftSum->Str != gift && get_login_flag() > 1 ) 
        {
                send_user( this_object(), "%c%c%w", 0x3d, 12, gift );
                USER_ENERGY_D->count_ap( this_object() );
        }
        GiftSum->Str = gift;
}

// 函数：统计总体耐力
private void count_cps()
{
        int gift = Gift1->Cps + Gift2->Cps + get_level();

        if( GiftSum->Cps != gift && get_login_flag() > 1 ) 
        {
                send_user( this_object(), "%c%c%w", 0x3d, 13, gift );
                USER_ENERGY_D->count_dp( this_object() );
        }
        GiftSum->Cps = gift;
}

// 函数：统计总体敏捷
private void count_dex()
{
        int gift = Gift1->Dex + Gift2->Dex + get_level();

        if( GiftSum->Dex != gift && get_login_flag() > 1 ) 
        {
                send_user( this_object(), "%c%c%w", 0x3d, 14, gift );
                USER_ENERGY_D->count_sp( this_object() );
        }
        GiftSum->Dex = gift;
}

int get_hair() 
{
	object me = this_object();
	if (Hair==0)
	{
		Hair = me->get_fam_type()+1;		
	}
	return Hair;
}
int set_hair(int i) {return Hair=i;}

int get_hair_color() {return HairColor;}
int set_hair_color(int i) {return HairColor=i;}

int set_photo(int i) {return PersonPhoto = i; }

int get_photo()
{
	object me = this_object();
	if (PersonPhoto==0)
	{
		if (me->get_gender()==1) PersonPhoto = 1;
		else PersonPhoto = 1001;
	}
	return PersonPhoto;	
}