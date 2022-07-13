#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
//	s ID all level
//	s ID abc level ( abc = Name Skill )
int main(object me, string arg) 
{

    int p, cap;
	string result,arg2,sk;
    object item, item1, who, file;
		if( is_player(me) ) 
        {
            write_user(me, ECHO "Bạn không đủ quyền hạn !");
			return 1;
        }

		if( !arg ) return 1;
		if (arg==0) return 1;
		if( sscanf(arg, "%s %s %d", arg2 , sk, cap ) != 3 ) return 1;
			if( arg2 && !( who = find_any_char(arg2) ) )
			{
                write_user(me, ECHO "Không tìm thấy người này !");
				return 1;
			}
	if ( who->get_fam_name() == "" ) {
			write_user(me, ECHO"Đối phương là Vô Môn Phái, không có kỹ năng Môn Phái");
			return 1;
			}
	else if ( who->get_fam_name() == "Đào Hoa Nguyên" ) {
			if(sk=="thaicothanquyen"){who->set_skill(0211, cap);file = load_object( SKILL->get_skill_file(0211) );}
			if(sk=="daohoatamphap"){who->set_skill(0212, cap);file = load_object( SKILL->get_skill_file(0212) );}
			if(sk=="kimcuongbathoai"){who->set_skill(0316, cap);file = load_object( SKILL->get_skill_file(0316) );}
			if(sk=="hothekimcang"){who->set_skill(0317, cap);file = load_object( SKILL->get_skill_file(0317) );}
			if(sk=="chuthienvanchuyen"){who->set_skill(0319, cap);file = load_object( SKILL->get_skill_file(0319) );}
				if(sk=="all")
				{
who->set_skill(0211, cap);who->set_skill(0212, cap);who->set_skill(0316, cap);who->set_skill(0317, cap);who->set_skill(0319, cap);
			write_user(me, sprintf(ECHO"Kỹ năng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng Môn Phái bây giờ là cấp %d", cap ));
				}
				else if (sk=="thaicothanquyen"||sk=="daohoatamphap"||sk=="kimcuongbathoai"||sk=="hothekimcang"||sk=="chuthienvanchuyen")
				{
			write_user(me, sprintf(ECHO"Kỹ năng %s của %s(%d) bây giờ là cấp %d", file->get_name(), who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng %s bây giờ là cấp %d", file->get_name(), cap ));	
				}
				else write_user(me, ECHO"Câu lệnh sai, không thể thực hiện!");
			return 1;
			}
	else if ( who->get_fam_name() == "Thục Sơn" ) {
			if(sk=="thienladaophap"){who->set_skill(0221, cap);file = load_object( SKILL->get_skill_file(0221) );}
			if(sk=="phitienkiemphap"){who->set_skill(0231, cap);file = load_object( SKILL->get_skill_file(0231) );}
			if(sk=="daokiemtamphap"){who->set_skill(0222, cap);file = load_object( SKILL->get_skill_file(0222) );}
			if(sk=="honnguyenchankhi"){who->set_skill(0325, cap);file = load_object( SKILL->get_skill_file(0325) );}
			if(sk=="chuthienvanchuyen"){who->set_skill(0329, cap);file = load_object( SKILL->get_skill_file(0329) );}
				if(sk=="all")
				{
who->set_skill(0221, cap);who->set_skill(0231, cap);who->set_skill(0222, cap);who->set_skill(0325, cap);who->set_skill(0329, cap);				
			write_user(me, sprintf(ECHO"Kỹ năng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng Môn Phái bây giờ là cấp %d", cap ));
				}
				else if (sk=="thienladaophap"||sk=="phitienkiemphap"||sk=="daokiemtamphap"||sk=="honnguyenchankhi"||sk=="chuthienvanchuyen")
				{
			write_user(me, sprintf(ECHO"Kỹ năng %s của %s(%d) bây giờ là cấp %d", file->get_name(), who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng %s bây giờ là cấp %d", file->get_name(), cap ));	
				}
				else write_user(me, ECHO"Câu lệnh sai, không thể thực hiện!");
			return 1;
			}
	else if ( who->get_fam_name() == "Cấm Vệ Quân" ) {
			if(sk=="bavuongthuongphap"){who->set_skill(0241, cap);file = load_object( SKILL->get_skill_file(0241) );}
			if(sk=="phongmaconphap"){who->set_skill(0251, cap);file = load_object( SKILL->get_skill_file(0251) );}
			if(sk=="thuongconbophap"){who->set_skill(0242, cap);file = load_object( SKILL->get_skill_file(0242) );}
			if(sk=="binhphap"){who->set_skill(0348, cap);file = load_object( SKILL->get_skill_file(0348) );}
			if(sk=="maluyen"){who->set_skill(0349, cap);file = load_object( SKILL->get_skill_file(0349) );}
				if(sk=="all")
				{
who->set_skill(0241, cap);who->set_skill(0251, cap);who->set_skill(0242, cap);who->set_skill(0348, cap);who->set_skill(0349, cap);				
			write_user(me, sprintf(ECHO"Kỹ năng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng Môn Phái bây giờ là cấp %d", cap ));
				}
				else if (sk=="bavuongthuongphap"||sk=="phongmaconphap"||sk=="thuongconbophap"||sk=="binhphap"||sk=="maluyen")
				{
			write_user(me, sprintf(ECHO"Kỹ năng %s của %s(%d) bây giờ là cấp %d", file->get_name(), who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng %s bây giờ là cấp %d", file->get_name(), cap ));	
				}
				else write_user(me, ECHO"Câu lệnh sai, không thể thực hiện!");
			return 1;
			}
	else if ( who->get_fam_name() == "Đường Môn" ) {
			if(sk=="manthienhoavu"){who->set_skill(0261, cap);file = load_object( SKILL->get_skill_file(0261) );}
			if(sk=="duongmondockinh"){who->set_skill(0363, cap);file = load_object( SKILL->get_skill_file(0363) );}
			if(sk=="lactuyetvongan"){who->set_skill(0364, cap);file = load_object( SKILL->get_skill_file(0364) );}
			if(sk=="duongmontamphap"){who->set_skill(0365, cap);file = load_object( SKILL->get_skill_file(0365) );}
			if(sk=="cuctasatphap"){who->set_skill(0368, cap);file = load_object( SKILL->get_skill_file(0368) );}
				if(sk=="all")
				{
who->set_skill(0261, cap);who->set_skill(0363, cap);who->set_skill(0364, cap);who->set_skill(0365, cap);who->set_skill(0368, cap);				
			write_user(me, sprintf(ECHO"Kỹ năng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng Môn Phái bây giờ là cấp %d", cap ));
				}
				else if (sk=="manthienhoavu"||sk=="duongmondockinh"||sk=="lactuyetvongan"||sk=="duongmontamphap"||sk=="cuctasatphap")
				{
			write_user(me, sprintf(ECHO"Kỹ năng %s của %s(%d) bây giờ là cấp %d", file->get_name(), who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng %s bây giờ là cấp %d", file->get_name(), cap ));	
				}
				else write_user(me, ECHO"Câu lệnh sai, không thể thực hiện!");
			return 1;
			}
	else if ( who->get_fam_name() == "Mao Sơn" ) {
			if(sk=="nhapmonhangma"){who->set_skill(0271, cap);file = load_object( SKILL->get_skill_file(0271) );}
			if(sk=="daophapthanthong"){who->set_skill(0413, cap);file = load_object( SKILL->get_skill_file(0413) );}
			if(sk=="nghichthienphapthu"){who->set_skill(0414, cap);file = load_object( SKILL->get_skill_file(0414) );}
			if(sk=="thuanthienphapchu"){who->set_skill(0417, cap);file = load_object( SKILL->get_skill_file(0417) );}
			if(sk=="huyenhocchinhdao"){who->set_skill(0418, cap);file = load_object( SKILL->get_skill_file(0418) );}
				if(sk=="all")
				{
who->set_skill(0271, cap);who->set_skill(0413, cap);who->set_skill(0414, cap);who->set_skill(0417, cap);who->set_skill(0418, cap);				
			write_user(me, sprintf(ECHO"Kỹ năng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng Môn Phái bây giờ là cấp %d", cap ));
				}
				else if (sk=="nhapmonhangma"||sk=="daophapthanthong"||sk=="nghichthienphapthu"||sk=="thuanthienphapchu"||sk=="huyenhocchinhdao")
				{
			write_user(me, sprintf(ECHO"Kỹ năng %s của %s(%d) bây giờ là cấp %d", file->get_name(), who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng %s bây giờ là cấp %d", file->get_name(), cap ));	
				}
				else write_user(me, ECHO"Câu lệnh sai, không thể thực hiện!");
			return 1;
			}
	else if ( who->get_fam_name() == "Côn Luân" ) {
			if(sk=="daithuadaophap"){who->set_skill(0421, cap);file = load_object( SKILL->get_skill_file(0421) );}
			if(sk=="amduongnguhanh"){who->set_skill(0422, cap);file = load_object( SKILL->get_skill_file(0422) );}
			if(sk=="kimtienphuchu"){who->set_skill(0423, cap);file = load_object( SKILL->get_skill_file(0423) );}
			if(sk=="kimcangphapchu"){who->set_skill(0424, cap);file = load_object( SKILL->get_skill_file(0424) );}
			if(sk=="cankhonnadi"){who->set_skill(0425, cap);file = load_object( SKILL->get_skill_file(0425) );}
			if(sk=="conluandaochu"){who->set_skill(0426, cap);file = load_object( SKILL->get_skill_file(0426) );}
				if(sk=="all")
				{
who->set_skill(0421, cap);who->set_skill(0422, cap);who->set_skill(0423, cap);who->set_skill(0424, cap);who->set_skill(0425, cap);who->set_skill(0426, cap);				
			write_user(me, sprintf(ECHO"Kỹ năng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng Môn Phái bây giờ là cấp %d", cap ));
				}
				else if (sk=="daithuadaophap"||sk=="amduongnguhanh"||sk=="kimtienphuchu"||sk=="kimcangphapchu"||sk=="cankhonnadi"||sk=="conluandaochu")
				{
			write_user(me, sprintf(ECHO"Kỹ năng %s của %s(%d) bây giờ là cấp %d", file->get_name(), who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng %s bây giờ là cấp %d", file->get_name(), cap ));	
				}
				else write_user(me, ECHO"Câu lệnh sai, không thể thực hiện!");
			return 1;
			}
	else if ( who->get_fam_name() == "Vân Mộng Cốc" ) {
			if(sk=="nguphongtamphap"){who->set_skill(0281, cap);file = load_object( SKILL->get_skill_file(0281) );}
			if(sk=="trungyduocly"){who->set_skill(0501, cap);file = load_object( SKILL->get_skill_file(0501) );}
			if(sk=="ythuat"){who->set_skill(0511, cap);file = load_object( SKILL->get_skill_file(0511) );}
			if(sk=="mehonquyet"){who->set_skill(0531, cap);file = load_object( SKILL->get_skill_file(0531) );}
			if(sk=="kymondongiap"){who->set_skill(0591, cap);file = load_object( SKILL->get_skill_file(0591) );}
				if(sk=="all")
				{
who->set_skill(0281, cap);who->set_skill(0501, cap);who->set_skill(0511, cap);who->set_skill(0531, cap);who->set_skill(0591, cap);				
			write_user(me, sprintf(ECHO"Kỹ năng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng Môn Phái bây giờ là cấp %d", cap ));
				}
				else if (sk=="nguphongtamphap"||sk=="trungyduocly"||sk=="ythuat"||sk=="mehonquyet"||sk=="kymondongiap")
				{
			write_user(me, sprintf(ECHO"Kỹ năng %s của %s(%d) bây giờ là cấp %d", file->get_name(), who->get_name(), who->get_number(), cap ));
			send_user(who,"%c%s",';', sprintf("Kỹ năng %s bây giờ là cấp %d", file->get_name(), cap ));	
				}
				else write_user(me, ECHO"Câu lệnh sai, không thể thực hiện!");
			return 1;
			}
		
	return 1;
} 