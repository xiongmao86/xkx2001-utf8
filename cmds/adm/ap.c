int main(object me, string arg)
{
    string target_name, skill_name;
    object target, weapon;
    mapping prepare;
    if(sscanf(arg, "%s", target_name)!=1) {
        return notify_fail(
            "指令格式：ap <对象>\n"
        );
    }

    target = present(target_name, environment(me));
	if(!target) target = present(target_name, me);
	if(!target) target = find_player(target_name);
	if(!target || !me->visible(target)) target = find_object(resolve_path(me->query("cwd"), target_name));
	if(target_name=="me") target = me;
	if(!target) return notify_fail("找不到指定的物件。\n");

    weapon = target->query_temp("weapon");
    prepare = target->query_skill_prepare();
    if(objectp(weapon))
        skill_name = weapon->query("skill_type");
    else if (sizeof(prepare) == 0)
        skill_name = "unarmed";
    else if (sizeof(prepare) == 1)
        skill_name = (keys(prepare))[0];
    else if (sizeof(prepare) == 2)
        skill_name = (keys(prepare))[me->query_temp("action_flag")];

    // debug
    printf("target: %O\n", target);
    printf("skill_name: %s\n", skill_name);

    printf("ap = %d\n", COMBAT_D->skill_power(target, skill_name, 1));

    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : ap <对象>
计算特定对象的ap。
 
HELP
    );
    return 1;
}