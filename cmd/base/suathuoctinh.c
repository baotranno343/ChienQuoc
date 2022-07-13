int main( object me, string arg )
{
 int con, spi, str, cps, dex; //Tạo các biến int
 if( !is_god(me) )
	 {
	  return 1; //Kết thúc
	 }
 if( !arg || sscanf( arg, "%d %d %d %d %d", con, spi, str, cps, dex ) != 5 ) return 1; //Kiểm tra và scan giá trị
 me->set_con_2(con); //Sửa Thể Chất
 me->set_spi_2(spi); //Sửa Tinh Thần
 me->set_str_2(str); //Sửa Cường Lực
 me->set_cps_2(cps); //Sửa Nại Lực
 me->set_dex_2(dex); //Sửa Mẫn Tiệp
 USER_ENERGY_D->count_all_prop(me); //Tính lại chỉ số nhân vật sau khi chỉnh thuộc tính
 return 1; //Kết thúc // gõ /suathuoctinh thểChất tinhThần cườngLực nạiLực mẫnTiệp
}