#ifndef CONFIG_H_
#define CONFIG_H_

#include "struct.h"
#include "confuse.h"


extern int config_loadfile(char *filename);
extern int config_load(const char *file);

int config_as_access_flag(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_bool(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_ns_expiry(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result);
int config_bool_as(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_bs(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_cs(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_ns(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_os(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bs_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result);
int config_bs_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result);
int config_bs_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result);
int config_bs_set(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result);
int config_cs_admin(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_autovop(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_delay(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_getpass(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_hop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_keeptopic(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_leaveops(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_maxlist(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_memolevel(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_mkick(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_operonly(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_opwatch(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_regacc(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_restricted(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_setpass(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_sop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_opwatch(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_leaveops(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_keeptopic(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_topiclock(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_memolevel(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_restricted(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_desc(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_password(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_successor(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_founder(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_bot(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_set_mlock(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_oper(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_os_access(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result);
int config_passAction(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_port(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_ns_admin(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_authchan(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_authnotify(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_delay(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_mnotify(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_mlock(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_autoacc(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_hidemail(cfg_t *cfg,cfg_opt_t *opt, const char *value, void *result);
int config_ns_nomemo(cfg_t *cfg,cfg_opt_t *opt, const char *value, void *result);
int config_ns_protect(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_ns_regacc(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_ns_getpass(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_ns_setpass(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_s_passlimit(cfg_t *cfg,cfg_opt_t *opt, const char *value, void *result);
int config_str32(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_str64(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_str128(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_tlock(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_uint32(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_cmd_invite(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_cmd_op(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_cmd_kick(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_cmd_ban(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_cmd_mkick(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int parse_config(void);

#endif /*CONFIG_H_*/
