#ifndef CONFIG_H_
#define CONFIG_H_

#include "struct.h"
#include "confuse.h"


extern int config_loadfile(char *filename);
extern int config_load(const char *file);

int config_bool(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_bool_as(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_bs(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_cs(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_ms(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_ns(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_bool_os(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_admin(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_akick_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_aop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_autovop(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_delay(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_expiry(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_getpass(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_hop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_hop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_keeptopic(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_leaveops(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_maxlist(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_memolevel(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_operonly(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_opwatch(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_regacc(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_restricted(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_setpass(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_cs_sop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_sop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);

int config_cs_admin_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_admin_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_admin_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_admin_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_admin_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_admin_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);

int config_cs_owner_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_owner_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_owner_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_owner_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_owner_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_owner_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);

int config_cs_sop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_uop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_cs_vop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_oper(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
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
int config_s_keeplogs(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
int config_s_globaloncycle(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result);
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
int config_bs_channel(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);
int config_bs_manage(cfg_t *cfg,cfg_opt_t *opt,const char *value,void *result);

#endif /*CONFIG_H_*/
