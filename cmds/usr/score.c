//Change by Server (5/25/2001)
// score.c
// modified by fear@xkx 5-march-2000

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string bar_string = "■■■■■■■■■■■■";
string blank_string = "□□□□□□□□□□□□";
string blank_half_width = "            ";
//string bar_string = "●〓〓〓〓〓〓〓〓〓〓〓";
//string blank_string= "●───────────";

string display_attr(int gift, int value);
string status_color(int current, int max);
string date_string(int date);
string line_of(string head, int val, int eff, int max, string end);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
	object ob;
	mapping my;
	string line, str, skill_type;
	object weapon;
	int attack_points, dodge_points, parry_points;

	seteuid(getuid(me));

	if(!arg)
		ob = me;
	else if (wizardp(me)) {
		ob = present(arg, environment(me));
		if (!ob) ob = find_player(arg);
		if (!ob) ob = find_living(arg);
		if (!ob) return notify_fail("你要察看谁的状态？\n");
	} else
		return notify_fail("只有巫师能察看别人的状态。\n");

	my = ob->query_entire_dbase();

    line = sprintf("[44;1m[1;33m                  【侠客行个人档案】(%s中文)                       [37;0m\n\n", ob->query("language"),);
	line += sprintf( BOLD " %s" NOR "%s\n\n", RANK_D->query_rank(ob), ob->short(1) );

	line += sprintf(" 你是一%s%s岁%s个月的%s%s，%s生。\n",
		ob->query("unit"),
		chinese_number(ob->query("age")), 
		chinese_number(ob->query("month")), 
		ob->query("gender"),
		ob->query("race"),
		CHINESE_D->chinese_date(((int)ob->query("birthday") - 14*365*24*60) * 60) );

	if( mapp(my["family"]) && my["family"]["master_name"] ) {
		line = sprintf("%s 你的师父是%s。",
			line, my["family"]["master_name"] );

		if( mapp(my["spouse"])
		&& my["spouse"]["title"] && my["spouse"]["name"] )
			line = sprintf("%s 你的%s是%s。\n\n",
				line, my["spouse"]["title"], my["spouse"]["name"] );
		else
			line = sprintf("%s\n\n", line);
	} else {
		if( mapp(my["spouse"])
		&& my["spouse"]["title"] && my["spouse"]["name"] )
		        line = sprintf("%s 你的%s是%s。\n\n",
 				line, my["spouse"]["title"], my["spouse"]["name"] );
      else
		line += "\n ";
 	}			

	if( 1 || wizardp(me) || (int)ob->query("age") >= 18 ) {
		line += sprintf(
			" 膂力：[%s/%s] 悟性：[%s/%s] 根骨：[%s/%s] 身法：[%s/%s]\n\n", 
			display_attr(my["str"], ob->query_str()),
			display_attr(my["str"], ob->query("str")),
			display_attr(my["int"], ob->query_int()),
			display_attr(my["int"], ob->query("int")),
			display_attr(my["con"], ob->query_con()),
			display_attr(my["con"], ob->query("con")),
			display_attr(my["dex"], ob->query_dex()),
			display_attr(my["dex"], ob->query("dex")));
	}
	
    line += line_of(" 精  ：", my["jing"], my["eff_jing"], my["max_jing"], "\t");

	if( my["max_jingli"] > 0 )
		line += line_of(" 精力：", my["jingli"], my["max_jingli"], my["max_jingli"], "\n");
	else
		line += " 精力：\n";
	
    line += line_of(" 气  ：", my["qi"], my["eff_qi"], my["max_qi"], "\t");

	if( my["max_neili"] > 0 )
		line += line_of(" 内力：", my["neili"], my["max_neili"], my["max_neili"], "\n");
	else
		line += " 内力：\n";

	if( ob->max_food_capacity() > 0 )
		line += line_of(" 食物：", my["food"], ob->max_food_capacity(), ob->max_food_capacity(), "\t");
	else
		line += " 食物：\t";
	
	if( my["max_potential"] > 0 )
		line += line_of(" 潜能：", my["potential"], my["max_potential"], my["max_potential"], "\n");
	else
		line += " 潜能：\n";

	if( ob->max_water_capacity() > 0 )
		line += line_of(" 饮水：", my["water"], ob->max_water_capacity(), ob->max_water_capacity(), "\t");
	else
		line += " 饮水：\t";
		
	line += sprintf(" 经验： " HIM "%d\n" NOR, ob->query("combat_exp") );

	line += sprintf(" 神  ： " HIR "%10d            \t" NOR, ob->query("shen") );
	line += sprintf(" 阅历： " HIC "%d           " NOR, ob->query("quest_exp") );
//	line += sprintf(" 武德：     " HIR "%d\n" NOR, ob->query("behavior_exp") );

	attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

	if( objectp(weapon = ob->query_temp("weapon")) )
		skill_type = weapon->query("skill_type");
	else
		skill_type = "kick";

	if (wizardp(me))
	line += sprintf("\n 攻击力: " HIW "%d (+%d)" NOR "\t\t 防御力： " HIW "%d (+%d)\n" NOR,
		attack_points/100 + 1, ob->query_temp("apply/damage"),
		(dodge_points + (weapon? parry_points: (parry_points/10)))/100 + 1, ob->query_temp("apply/armor"));
	else line += "\n";

	line += sprintf("\n 你到目前为止总共杀了 %d 个人，其中有 %d 个是其他玩家。",
		my["MKS"] + my["PKS"], my["PKS"]);
	line += sprintf("\n 你到目前为止总共死了 %d 次，其中 %d 次是正常死亡。 \n\n", 
		my["death_count"], my["death_times"] );

	write(line);
	return 1;
}

string display_attr(int gift, int value)
{
	if( value > gift ) return sprintf( HIY "%3d" NOR, value );
	else if( value < gift ) return sprintf( CYN "%3d" NOR, value );
	else return sprintf("%3d", value);
}

string status_color(int current, int max)
{
	int percent;

	if( max ) percent = current * 100 / max;
	else percent = 100;

	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}

// TODO: recently

string tribar_graph(int val, int eff, int max)
{
    string color = status_color(val, max);
    int bar_length = 12;
    int character_length = 3;
    // off by one;
    int end_idx = bar_length * character_length - 1;

    if( val > max ) 
        return color + bar_string[0..end_idx] + NOR;
    // val <= max <= eff
    if( eff >= max ) {
        int val_idx = (val * bar_length / max) * character_length - 1;
        return color + bar_string[0..val_idx]
            + blank_string[val_idx+1..end_idx] + NOR;
    }
    // val <= eff < max
    else {
        int val_idx = (val * bar_length / max) * character_length - 1;
        int eff_idx = (eff * bar_length / max) * character_length - 1;
        int eff_idx_half_width = (eff_idx+1)/3;
        return color + bar_string[0..val_idx] 
            + blank_string[val_idx+1..eff_idx]
            + blank_half_width[eff_idx_half_width..11] + NOR;
    }   
}

string line_of(string head, int val, int eff, int max, string end) {
    return head + tribar_graph(val, eff, max) + end;
}

int help(object me)
{
	write(@HELP
指令格式 : score
           score <对象名称>                   (巫师专用)

这个指令可以显示你(你)或指定对象(含怪物)的基本资料。

see also : hp
HELP
    );
    return 1;
}

//基本资料的设定请参阅 'help setup'。

