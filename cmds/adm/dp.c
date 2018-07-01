int main(object me, string arg)
{
    string target_name, skill_name;
    object target;

    if(!stringp(arg) || sscanf(arg, "%s", target_name)!=1) {
        return notify_fail(
            "指令格式：dp <对象>\n"
        );
    }

    target = present(target_name, environment(me));
	if(!target) target = present(target_name, me);
	if(!target) target = find_player(target_name);
	if(!target || !me->visible(target)) target = find_object(resolve_path(me->query("cwd"), target_name));
	if(target_name=="me") target = me;
	if(!target) return notify_fail("找不到指定的物件。\n");

    skill_name = "dodge";
    // debug
    printf("target: %O\n", target);
    printf("skill_name: %s\n", skill_name);

    printf("dp = %d\n", COMBAT_D->skill_power(target, skill_name, 1));

    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : dp <对象>
计算特定对象的dp。
 
HELP
    );
    return 1;
}