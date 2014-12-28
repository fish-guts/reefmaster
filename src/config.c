/*
 *      config.c - severin
 *      
 *      Copyright (c) 2014 Severin Mueller <severin.mueller@reefmaster.org>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, alBoston,
 *      MA 02110-1301, USA.
 */
#include "main.h"

int config_bool(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	return 0;
}
int config_os_access(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 2) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 2, 6);
		return -1;
	}
	os_access_flag = val;
	return 0;
}
int config_bool_as(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	as_enabled = val;
	return 0;
}
int config_bool_bs(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	bs_enabled = val;
	return 0;
}
int config_bool_cs(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	cs_enabled = val;
	return 0;
}
int config_bool_ns(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	ns_enabled = val;
	return 0;
}
int config_bool_os(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	os_enabled = val;
	return 0;
}
int config_bs_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	bs_access_add = val;
	return 0;
}
int config_bs_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	bs_access_del = val;
	return 0;
}
int config_bs_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	bs_access_list = val;
	return 0;
}
int config_bs_set(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	bs_access_set = val;
	return 0;
}
int config_bs_setpass(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	bs_access_setpass = val;
	return 0;
}
int config_bs_getpass(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	bs_access_getpass = val;
	return 0;
}
int config_cs_akick_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_akick_add = val;
	return 0;
}
int config_cs_akick_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_akick_del = val;
	return 0;
}
int config_cs_akick_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_akick_list = val;
	return 0;
}
int config_cs_akick_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_akick_wipe = val;
	return 0;
}

int config_cs_akick_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_akick_enable = val;
	return 0;
}
int config_cs_akick_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_akick_disable = val;
	return 0;
}
int config_cs_aop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_sop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_aop_add = val;
	return 0;
}
int config_cs_aop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_sop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_aop_del = val;
	return 0;
}
int config_cs_aop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_sop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_aop_list = val;
	return 0;
}
int config_cs_aop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 1000)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0,
				1000);
		addlog(2, CONF_LOG_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 1000);
		return -1;
	}
	cs_aops_max = val;
	return 0;
}
int config_cs_aop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_sop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_aop_wipe = val;
	return 0;
}
int config_cs_aop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_sop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_aop_enable = val;
	return 0;
}
int config_cs_aop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_aop_disable = val;
	return 0;
}
int config_cs_autovop(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	cs_autovop = val;
	return 0;
}
int config_cs_expiry(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (val < 0) {
		cfg_error(cfg, CONF_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		return -1;
	}
	cs_expiry = val;
	return 0;
}
int config_cs_delay(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (val < 0) {
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		cfg_error(cfg, CONF_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		return -1;
	}
	cs_delay = val;
	return 0;
}
int config_cs_getpass(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line, opt->name,
				0, 6);
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	cs_gpass = val;
	return 0;
}
int config_cs_hop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_aop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_hop_add = val;
	return 0;
}
int config_cs_hop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_aop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_hop_del = val;
	return 0;
}
int config_cs_hop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_aop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_hop_list = val;
	return 0;
}
int config_cs_hop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 1000)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0,
				1000);
		addlog(2, CONF_LOG_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 1000);
		return -1;
	}
	cs_hops_max = val;
	return 0;
}
int config_cs_hop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_aop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	cs_hop_wipe = val;
	return 0;
}
int config_cs_hop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_aop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_hop_enable = val;
	return 0;
}
int config_cs_hop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_aop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_hop_disable = val;
	return 0;
}
int config_cs_keeptopic(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	cs_keeptopic = val;
	return 0;
}
int config_cs_leaveops(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	cs_leaveops = val;
	return 0;
}
int config_cs_maxlist(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (val < 0) {
		cfg_error(cfg, CONF_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		return -1;
	}
	cs_maxlist = val;
	return 0;
}
int config_cs_memolevel(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 7)) {
		cfg_error(cfg, CONF_ERR_INT, cfg->line, opt->name, 0, 7);
		return -1;
	}
	cs_memolevel = val;
	return 0;
}
int config_cs_operonly(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	cs_operonly = val;
	return 0;
}
int config_cs_opwatch(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	cs_opwatch = val;
	return 0;
}
int config_cs_regacc(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	cs_regaccess = val;
	return 0;
}
int config_cs_restricted(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	cs_restricted = val;
	return 0;
}
int config_cs_setpass(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	cs_spass = val;
	return 0;
}
int config_cs_mdeop(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if ((val < 1) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 1, 8);
		return -1;
	}
	cs_mdeop_access = val;
	return 0;
}
int config_cs_mkick(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if ((val < 1) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 1, 8);
		return -1;
	}
	cs_mkick_access = val;
	return 0;
}
int config_cs_set_opwatch(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_opwatch_access = val;
	return 0;
}
int config_cs_set_leaveops(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_leaveops_access = val;
	return 0;
}
int config_cs_set_keeptopic(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_keeptopic_access = val;
	return 0;
}
int config_cs_set_topiclock(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_topiclock_access = val;
	return 0;
}
int config_cs_set_memolevel(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_memolevel_access = val;
	return 0;
}
int config_cs_set_restricted(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_restricted_access = val;
	return 0;
}
int config_cs_set_desc(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_desc_access = val;
	return 0;
}
int config_cs_set_password(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_password_access = val;
	return 0;
}
int config_cs_set_successor(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_successor_access = val;
	return 0;
}
int config_cs_set_founder(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 6) || (val > 9)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
		return -1;
	}
	cs_set_opwatch_access = val;
	return 0;
}
int config_cs_set_bot(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
		if ((val < 6) || (val > 9)) {
			cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
			return -1;
		}
		cs_set_bot_access = val;
		return 0;
}
int config_cs_set_mlock(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
		if ((val < 6) || (val > 9)) {
			cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 6, 9);
			return -1;
		}
		cs_set_mlock_access = val;
		return 0;
}
int config_cs_sop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_sop_add = val;
	return 0;
}
int config_cs_sop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_sop_del = val;
	return 0;
}
int config_cs_sop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_sop_list = val;
	return 0;
}
int config_cs_sop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 1000)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0,
				1000);
		addlog(2, CONF_LOG_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 1000);
		return -1;
	}
	cs_sops_max = val;
	return 0;
}
int config_cs_sop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_sop_wipe = val;
	return 0;
}
int config_cs_sop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_sop_enable = val;
	return 0;
}
int config_cs_sop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	cs_sop_disable = val;
	return 0;
}
int config_cs_vop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_hop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_vop_add = val;
	return 0;
}
int config_cs_vop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_hop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_vop_del = val;
	return 0;
}
int config_cs_vop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_hop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_vop_list = val;
	return 0;
}
int config_cs_vop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 1000)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0,
				1000);
		addlog(2, CONF_LOG_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 1000);
		return -1;
	}
	cs_vops_max = val;
	return 0;
}
int config_cs_vop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_hop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_vop_wipe = val;
	return 0;
}
int config_cs_vop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_hop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_vop_enable = val;
	return 0;
}
int config_cs_vop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	if (val > cs_hop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_vop_disable = val;
	return 0;
}
int config_cs_uop_add(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_vop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_VOP_SECTION);
		return -1;
	}
	if (val > cs_hop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_add) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_uop_add = val;
	return 0;
}
int config_cs_uop_del(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_vop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_VOP_SECTION);
		return -1;
	}
	if (val > cs_hop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_del) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_uop_del = val;
	return 0;
}
int config_cs_uop_list(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 8)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 8);
		return -1;
	}
	if (val > cs_vop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_VOP_SECTION);
		return -1;
	}
	if (val > cs_hop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_list) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_uop_list = val;
	return 0;
}
int config_cs_uop_max(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 1000)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0,
				1000);
		addlog(2, CONF_LOG_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 1000);
		return -1;
	}
	cs_uops_max = val;
	return 0;
}
int config_cs_akick_max(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 1000)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0,
				1000);
		addlog(2, CONF_LOG_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 1000);
		return -1;
	}
	cs_akicks_max = val;
	return 0;
}
int config_cs_uop_wipe(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	if (val > cs_vop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_VOP_SECTION);
		return -1;
	}
	if (val > cs_hop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_wipe) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_uop_wipe = val;
	return 0;
}
int config_cs_uop_enable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	if (val > cs_vop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_VOP_SECTION);
		return -1;
	}
	if (val > cs_hop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_enable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_uop_enable = val;
	return 0;
}
int config_cs_uop_disable(cfg_t *cfg, cfg_opt_t *opt, const char *value,
		void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	if (val > cs_vop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_VOP_SECTION);
		return -1;
	}
	if (val > cs_hop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_HOP_SECTION);
		return -1;
	}
	if (val > cs_aop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_AOP_SECTION);
		return -1;
	}
	if (val > cs_sop_disable) {
		cfg_error(cfg, CONF_ERR_XOP_TOO_HIGH, CONFIG_FILE, cfg->line, opt->name,
				CONG_MSG_SOP_SECTION);
		return -1;
	}
	cs_uop_disable = val;
	return 0;
}
/* this is the configuration file parser, using libconfuse 2.6 by martin hedenfalk */
/* The Config is failsafe against NULL values. When an entry is missing, a default value is being set. */
int config_load(const char *file) {
	FILE *pFile;
	pFile = fopen(CONFIG_FILE, "r");
	if (!pFile) {
		printf(CONF_ERR_FILENOTFOUND"\x1b[0m");
		addlog(2, CONF_LOG_ERR_FILENOT);
		return -1;
	}
	printf("\n*** Loading Configuration: \x1b[35;1m%s\x1b[0m...\n",	CONFIG_FILE);
	cfg_t *cfg;
	static cfg_opt_t main_general_opts[] = {
			CFG_STR_CB("name","services.mynet.org",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("user","user",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("host","mynet.org",CFGF_NONE,(void*)&config_str32),
			CFG_INT_CB("port",7029,CFGF_NONE,(void*)&config_port),
			CFG_STR_CB("description","My Net",CFGF_NONE,(void*)&config_str128),
			CFG_STR_CB("help_channel","#help",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("address","localhost",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("irc","irc.mynet.org",CFGF_NONE,(void*)&config_str32),
			CFG_END()
	};
	static cfg_opt_t main_files_opts[] = {
			CFG_STR_CB("motd",0,CFGF_NONE,(void*)config_str128),
			CFG_STR_CB("log",0,CFGF_NONE,(void*)config_str32),
			CFG_STR_CB("error",0,CFGF_NONE,(void*)config_str32),
			CFG_STR_CB("pid",0,CFGF_NONE,(void*)config_str32),
			CFG_INT_CB("keeplogfiles",0,CFGF_NONE,(void*)config_s_keeplogs),
			CFG_END()
	};
	static cfg_opt_t main_cycle_opts[] = {
			CFG_INT_CB("global_on_cycle",0,CFGF_NONE,(void*)config_s_globaloncycle),
			CFG_STR_CB("cycle_message",0,CFGF_NONE,(void*)config_str64),
			CFG_END()
	};
	static cfg_opt_t main_password_opts[] = {
			CFG_INT_CB("PassLimit",3,CFGF_NONE,(void*)config_s_passlimit),
			CFG_INT_CB("PassAction",3,CFGF_NONE,(void*)config_passAction),
			CFG_INT_CB("PassTimeout",60,CFGF_NONE,(void*)config_uint32),
			CFG_STR_CB("password",0,CFGF_NONE,(void*)&config_str32), CFG_END()
	};
	static cfg_opt_t main_reg_opts[] = {
			CFG_INT("flag",0,CFGF_NONE),
			CFG_END()
	};
	static cfg_opt_t services_opts[] = {
			CFG_SEC("general",main_general_opts,CFGF_NONE),
			CFG_SEC("files",main_files_opts,CFGF_NONE),
			CFG_SEC("cycle",main_cycle_opts,CFGF_NONE),
			CFG_SEC("password",main_password_opts,CFGF_NONE),
			CFG_SEC("registration",main_reg_opts,CFGF_NONE), CFG_END()
	};
	static cfg_opt_t ns_general_opts[] = {
			CFG_INT_CB("enabled",1,CFGF_NONE,(void*)&config_bool_ns),
			CFG_STR_CB("name","Nickserv",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("realname","Nickname Services",CFGF_NONE,(void*)&config_str32),
			CFG_INT_CB("expiry",90,CFGF_NONE,(void*)&config_uint32),
			CFG_INT_CB("admin",6,CFGF_NONE,(void*)&config_ns_admin),
			CFG_END()
	};
	static cfg_opt_t ns_reg_opts[] = {
			CFG_INT_CB("delay",0,CFGF_NONE,(void*)&config_ns_delay),
			CFG_INT_CB("access",0,CFGF_NONE,(void*)&config_ns_regacc),
			CFG_INT_CB("autoaccess",1,CFGF_NONE,(void*)&config_ns_autoacc),
			CFG_INT_CB("sendmemo",1,CFGF_NONE,(void*)&config_bool), CFG_END()
	};
	static cfg_opt_t ns_list_opts[] = {
			CFG_INT_CB("maxlist",100,CFGF_NONE,(void*)&config_uint32),
			CFG_INT_CB("operonly",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("access_max",32,CFGF_NONE,(void*)&config_uint32),
			CFG_END()
	};
	static cfg_opt_t ns_password_opts[] = {
			CFG_INT_CB("setpass",4,CFGF_NONE,(void*)&config_ns_setpass),
			CFG_INT_CB("getpass",4,CFGF_NONE,(void*)&config_ns_getpass),
			CFG_STR_CB("enforcer","enforcer",CFGF_NONE,(void*)&config_str32),
			CFG_INT_CB("release",60,CFGF_NONE,(void*)config_uint32), CFG_END()
	};
	static cfg_opt_t ns_default_opts[] = {
			CFG_INT_CB("noop",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("high_protect",1,CFGF_NONE,(void*)&config_ns_protect),
			CFG_INT_CB("hide_email",1,CFGF_NONE,(void*)&config_ns_hidemail),
			CFG_INT_CB("no_memo",1,CFGF_NONE,(void*)&config_ns_nomemo),
			CFG_INT_CB("auth_channel",1,CFGF_NONE,(void*)&config_ns_authchan),
			CFG_INT_CB("auth_notify",1,CFGF_NONE,(void*)&config_ns_authnotify),
			CFG_INT_CB("mnotify",1,CFGF_NONE,(void*)&config_ns_mnotify),
			CFG_STR_CB("mlock","pix",CFGF_NONE,(void*)&config_str32),
			CFG_END()
	};
	static cfg_opt_t nickserv_opts[] = {
			CFG_SEC("general",ns_general_opts,CFGF_NONE),
			CFG_SEC("registration",ns_reg_opts,CFGF_NONE),
			CFG_SEC("list",ns_list_opts,CFGF_NONE),
			CFG_SEC("password",ns_password_opts,CFGF_NONE),
			CFG_SEC("default",ns_default_opts,CFGF_NONE), CFG_END()
	};
	static cfg_opt_t cs_general_opts[] = {
			CFG_INT_CB("enabled",1,CFGF_NONE,(void*)&config_bool_cs),
			CFG_STR_CB("name","Chanserv",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("realname","Channel Services",CFGF_NONE,(void*)&config_str32),
			CFG_INT_CB("expiry",90,CFGF_NONE,(void*)&config_cs_expiry),
			CFG_INT_CB("admin",6,CFGF_NONE,(void*)&config_cs_admin),
			CFG_END()
	};
	static cfg_opt_t cs_op_opts[] = {
			CFG_INT_CB("sop_max",1000,CFGF_NONE,(void*)&config_cs_sop_max),
			CFG_INT_CB("aop_max",1000,CFGF_NONE,(void*)&config_cs_aop_max),
			CFG_INT_CB("hop_max",1000,CFGF_NONE,(void*)&config_cs_hop_max),
			CFG_INT_CB("vop_max",1000,CFGF_NONE,(void*)&config_cs_vop_max),
			CFG_INT_CB("uop_max",1000,CFGF_NONE,(void*)&config_cs_uop_max),
			CFG_INT_CB("akick_max",1000,CFGF_NONE,(void*)&config_cs_akick_max),
			CFG_END() };
	static cfg_opt_t cs_acc_akick_opts[] = {
			CFG_INT_CB("add",4,CFGF_NONE,(void*)&config_cs_akick_add),
			CFG_INT_CB("del",4,CFGF_NONE,(void*)&config_cs_akick_del),
			CFG_INT_CB("list",4,CFGF_NONE,(void*)&config_cs_akick_list),
			CFG_INT_CB("wipe",4,CFGF_NONE,(void*)&config_cs_akick_wipe),
			CFG_INT_CB("enable",7,CFGF_NONE,(void*)&config_cs_akick_enable),
			CFG_INT_CB("disable",7,CFGF_NONE,(void*)&config_cs_akick_disable),
			CFG_END(),
	};
	static cfg_opt_t cs_acc_sop_opts[] = {
			CFG_INT_CB("add",7,CFGF_NONE,(void*)&config_cs_sop_add),
			CFG_INT_CB("del",7,CFGF_NONE,(void*)&config_cs_sop_del),
			CFG_INT_CB("list",7,CFGF_NONE,(void*)&config_cs_sop_list),
			CFG_INT_CB("wipe",7,CFGF_NONE,(void*)&config_cs_sop_wipe),
			CFG_INT_CB("enable",7,CFGF_NONE,(void*)&config_cs_sop_enable),
			CFG_INT_CB("disable",7,CFGF_NONE,(void*)&config_cs_sop_disable),
			CFG_END(),
	};
	static cfg_opt_t cs_acc_aop_opts[] = {
			CFG_INT_CB("add",7,CFGF_NONE,(void*)&config_cs_aop_add),
			CFG_INT_CB("del",7,CFGF_NONE,(void*)&config_cs_aop_del),
			CFG_INT_CB("list",7,CFGF_NONE,(void*)&config_cs_aop_list),
			CFG_INT_CB("wipe",7,CFGF_NONE,(void*)&config_cs_aop_wipe),
			CFG_INT_CB("enable",7,CFGF_NONE,(void*)&config_cs_aop_enable),
			CFG_INT_CB("disable",7,CFGF_NONE,(void*)&config_cs_aop_disable),
			CFG_END(),
	};
	static cfg_opt_t cs_acc_hop_opts[] = {
			CFG_INT_CB("add",7,CFGF_NONE,(void*)&config_cs_hop_add),
			CFG_INT_CB("del",7,CFGF_NONE,(void*)&config_cs_hop_del),
			CFG_INT_CB("list",7,CFGF_NONE,(void*)&config_cs_hop_list),
			CFG_INT_CB("wipe",7,CFGF_NONE,(void*)&config_cs_hop_wipe),
			CFG_INT_CB("enable",7,CFGF_NONE,(void*)&config_cs_hop_enable),
			CFG_INT_CB("disable",7,CFGF_NONE,(void*)&config_cs_hop_disable),
			CFG_END(),
	};
	static cfg_opt_t cs_acc_vop_opts[] = {
			CFG_INT_CB("add",7,CFGF_NONE,(void*)&config_cs_vop_add),
			CFG_INT_CB("del",7,CFGF_NONE,(void*)&config_cs_vop_del),
			CFG_INT_CB("list",7,CFGF_NONE,(void*)&config_cs_vop_list),
			CFG_INT_CB("wipe",7,CFGF_NONE,(void*)&config_cs_vop_wipe),
			CFG_INT_CB("enable",7,CFGF_NONE,(void*)&config_cs_vop_enable),
			CFG_INT_CB("disable",7,CFGF_NONE,(void*)&config_cs_vop_disable),
			CFG_END(),
	};
	static cfg_opt_t cs_acc_uop_opts[] = {
			CFG_INT_CB("add",7,CFGF_NONE,(void*)&config_cs_uop_add),
			CFG_INT_CB("del",7,CFGF_NONE,(void*)&config_cs_uop_del),
			CFG_INT_CB("list",7,CFGF_NONE,(void*)&config_cs_uop_list),
			CFG_INT_CB("wipe",7,CFGF_NONE,(void*)&config_cs_uop_wipe),
			CFG_INT_CB("enable",7,CFGF_NONE,(void*)&config_cs_uop_enable),
			CFG_INT_CB("disable",7,CFGF_NONE,(void*)&config_cs_uop_disable),
			CFG_END(),
	};
	static cfg_opt_t cs_acc_opts[] = {
			CFG_SEC("akick",cs_acc_akick_opts,CFGF_NONE),
			CFG_SEC("sop",cs_acc_sop_opts,CFGF_NONE),
			CFG_SEC("aop",cs_acc_aop_opts,CFGF_NONE),
			CFG_SEC("hop",cs_acc_hop_opts,CFGF_NONE),
			CFG_SEC("vop",cs_acc_vop_opts,CFGF_NONE),
			CFG_SEC("uop",cs_acc_uop_opts,CFGF_NONE),
			CFG_INT_CB("mkick",4,CFGF_NONE,(void*)&config_cs_mkick),
			CFG_INT_CB("mdeop",4,CFGF_NONE,(void*)&config_cs_mdeop),
			CFG_END()
	};
	static cfg_opt_t cs_settings_opts[] = {
			CFG_INT_CB("opwatch",8,CFGF_NONE,(void*)&config_cs_set_opwatch),
			CFG_INT_CB("leaveops",8,CFGF_NONE,(void*)&config_cs_set_leaveops),
			CFG_INT_CB("keeptopic",8,CFGF_NONE,(void*)&config_cs_set_keeptopic),
			CFG_INT_CB("topiclock",8,CFGF_NONE,(void*)&config_cs_set_topiclock),
			CFG_INT_CB("memolevel",8,CFGF_NONE,(void*)&config_cs_set_memolevel),
			CFG_INT_CB("restricted",8,CFGF_NONE,(void*)&config_cs_set_restricted),
			CFG_INT_CB("desc",8,CFGF_NONE,(void*)&config_cs_set_desc),
			CFG_INT_CB("password",8,CFGF_NONE,(void*)&config_cs_set_password),
			CFG_INT_CB("successor",8,CFGF_NONE,(void*)&config_cs_set_successor),
			CFG_INT_CB("founder",8,CFGF_NONE,(void*)&config_cs_set_founder),
			CFG_INT_CB("bot",8,CFGF_NONE,(void*)&config_cs_set_bot),
			CFG_INT_CB("mlock",8,CFGF_NONE,(void*)&config_cs_set_mlock),
			CFG_END()
	};
	static cfg_opt_t cs_list_opts[] = {
			CFG_INT_CB("maxlist",100,CFGF_NONE,(void*)&config_cs_maxlist),
			CFG_INT_CB("operonly",1,CFGF_NONE,(void*)&config_cs_operonly),
			CFG_END()
	};
	static cfg_opt_t cs_password_opts[] = {
			CFG_INT_CB("setpass",0,CFGF_NONE,(void*)&config_cs_setpass),
			CFG_INT_CB("getpass",0,CFGF_NONE,(void*)&config_cs_getpass),
			CFG_END()
	};
	static cfg_opt_t cs_reg_opts[] = {
			CFG_INT_CB("delay",0,CFGF_NONE,(void*)&config_cs_delay),
			CFG_INT_CB("access",0,CFGF_NONE,(void*)&config_cs_regacc),
			CFG_INT_CB("sendmemo",1,CFGF_NONE,(void*)&config_bool), CFG_END()
	};
	static cfg_opt_t cs_default_opts[] = {
			CFG_INT_CB("opwatch",1,CFGF_NONE,(void*)&config_cs_opwatch),
			CFG_INT_CB("autovop",1,CFGF_NONE,(void*)&config_cs_autovop),
			CFG_INT_CB("keeptopic",1,CFGF_NONE,(void*)&config_cs_keeptopic),
			CFG_INT_CB("leaveops",1,CFGF_NONE,(void*)&config_cs_leaveops),
			CFG_INT_CB("restricted",1,CFGF_NONE,(void*)&config_cs_restricted),
			CFG_INT_CB("topiclock",0,CFGF_NONE,(void*)&config_cs_tlock),
			CFG_INT_CB("memolevel",4,CFGF_NONE,(void*)&config_cs_memolevel),
			CFG_STR_CB("mlock","rnt-k",CFGF_NONE,(void*)&config_str32),
			CFG_END()
	};
	static cfg_opt_t cs_misc_opts[] = {
			CFG_INT("akick_max",0,CFGF_NONE),
			CFG_END()
	};
	static cfg_opt_t chanserv_opts[] = {
			CFG_SEC("access",cs_acc_opts,CFGF_NONE),
			CFG_SEC("general",cs_general_opts,CFGF_NONE),
			CFG_SEC("operators",cs_op_opts,CFGF_NONE),
			CFG_SEC("list",cs_list_opts,CFGF_NONE),
			CFG_SEC("password",cs_password_opts,CFGF_NONE),
			CFG_SEC("registration",cs_reg_opts,CFGF_NONE),
			CFG_SEC("default",cs_default_opts,CFGF_NONE),
			CFG_SEC("misc",cs_misc_opts,CFGF_NONE),
			CFG_SEC("settings",cs_settings_opts,CFGF_NONE),
			CFG_END()
	};
	static cfg_opt_t os_general_opts[] = {
			CFG_INT_CB("enabled",1,CFGF_NONE,(void*)&config_bool_os),
			CFG_STR_CB("name","Operserv",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("realname","Operator Service",CFGF_NONE,(void*)&config_str32),
			CFG_INT_CB("access_flag",2,CFGF_NONE,(void*)&config_os_access),
			CFG_END()
	};
	static cfg_opt_t os_default_opts[] = {
			CFG_INT_CB("can_akill",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_chghost",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_global",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_local",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_kick",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_kill",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_chatops",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_sgline",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_sqline",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_svsnick",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_skline",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("can_szline",1,CFGF_NONE,(void*)&config_bool),
			CFG_STR_CB("vhost","ircops.reefmaster.ch",CFGF_NONE,(void*)&config_str64),
			CFG_END()
	};
	static cfg_opt_t os_global_opts[] = {
			CFG_INT_CB("on_oper",0,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_mode",0,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_akill",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_sgline",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_skline",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_szline",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_sqline",1,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_kick",0,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_list",0,CFGF_NONE,(void*)&config_bool),
			CFG_INT_CB("on_kill",1,CFGF_NONE,(void*)&config_bool),
			CFG_END()
	};
	static cfg_opt_t os_expiry_opts[] = {
			CFG_INT_CB("akill",30,CFGF_NONE,(void*)&config_uint32),
			CFG_INT_CB("sgline",30,CFGF_NONE,(void*)&config_uint32),
			CFG_INT_CB("skline",30,CFGF_NONE,(void*)&config_uint32),
			CFG_INT_CB("szline",30,CFGF_NONE,(void*)&config_uint32),
			CFG_INT_CB("sqline",30,CFGF_NONE,(void*)&config_uint32),
			CFG_END()
	};
	static cfg_opt_t operserv_opts[] = {
			CFG_SEC("general",os_general_opts,CFGF_NONE),
			CFG_SEC("global",os_global_opts,CFGF_NONE),
			CFG_SEC("default",os_default_opts,CFGF_NONE),
			CFG_SEC("expiry",os_expiry_opts,CFGF_NONE),
			CFG_END()
	};
	static cfg_opt_t bs_general_opts[] = {
			CFG_INT_CB("enabled",1,CFGF_NONE,(void*)&config_bool_bs),
			CFG_STR_CB("name","Botserv",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("realname","Bot Service",CFGF_NONE,(void*)&config_str32),
			CFG_END()
	};
	static cfg_opt_t bs_access_opts[] = {
			CFG_INT_CB("add",2,CFGF_NONE,(void*)&config_bs_add),
			CFG_INT_CB("del",3,CFGF_NONE,(void*)&config_bs_del),
			CFG_INT_CB("list",3,CFGF_NONE,(void*)&config_bs_list),
			CFG_INT_CB("set",3,CFGF_NONE,(void*)&config_bs_set),
			CFG_INT_CB("setpass",3,CFGF_NONE,(void*)&config_bs_setpass),
			CFG_INT_CB("getpass",3,CFGF_NONE,(void*)&config_bs_getpass),
			CFG_END()
	};
	static cfg_opt_t botserv_opts[] = {
			CFG_SEC("general",bs_general_opts,CFGF_NONE),
			CFG_SEC("access",bs_access_opts,CFGF_NONE),
	};
	static cfg_opt_t as_general_opts[] = {
			CFG_INT_CB("enabled",0,CFGF_NONE,(void*)&config_bool_as),
			CFG_STR_CB("name","Adminserv",CFGF_NONE,(void*)&config_str32),
			CFG_STR_CB("realname","Administrator Service",CFGF_NONE,(void*)&config_str32),
			CFG_END()
	};
	static cfg_opt_t adminserv_opts[] = {
			CFG_SEC("general",as_general_opts,CFGF_NONE),
			CFG_END()
	};
	static cfg_opt_t opts[] = {
			CFG_SEC("services",services_opts,CFGF_NONE),
			CFG_SEC("nickserv",nickserv_opts,CFGF_NONE),
			CFG_SEC("chanserv",chanserv_opts,CFGF_NONE),
			CFG_SEC("operserv",operserv_opts,CFGF_NONE),
			CFG_SEC("botserv",botserv_opts,CFGF_NONE),
			CFG_SEC("adminserv",adminserv_opts,CFGF_NONE),
			CFG_END()
	};
	cfg = cfg_init(opts, CFGF_NOCASE);
	if (cfg_parse(cfg, file) == CFG_PARSE_ERROR) {
		return -1;
	} else {
		cfg_t *services;
		services = cfg_getsec(cfg, "services");
		cfg_t *general;
		cfg_t *files;
		cfg_t *cycle;
		cfg_t *reg;
		cfg_t *password;

		/* section services ***********************************************************************************************/
		/* section general */
		general = cfg_getsec(services, "general");
		if (general) {
			s_name = cfg_getstr(general, "name");
			s_description = cfg_getstr(general, "description");
			s__host = cfg_getstr(general, "host");
			s_help_channel = cfg_getstr(general, "help_channel");
			s_user = cfg_getstr(general, "user");
			s_address = cfg_getstr(general, "address");
			s_unreal = cfg_getstr(general, "irc");
		}
		/* section files */

		files = cfg_getsec(services, "files");
		if (files) {
			s_motd = cfg_getstr(files, "motd");
			s_log = cfg_getstr(files, "log");
			s_pid = cfg_getstr(files, "pid");
		}

		/* section cycle */
		cycle = cfg_getsec(services, "cycle");
		if (cycle) {
			s_global_on_cycle = cfg_getint(cycle, "global_on_cycle");
			s_cycle_message = cfg_getstr(cycle, "cycle_message");
		}

		/* section password */
		password = cfg_getsec(services, "password");
		if (password) {
			s_password = cfg_getstr(password, "password");
		}

		/* section registration */
		reg = cfg_getsec(services, "registration");
		if (reg)
			s_flag = cfg_getint(reg, "flag");

		/* end of section services */
		/* section nickserv ***********************************************************************************************/
		cfg_t *ns_general;
		cfg_t *ns_reg;
		cfg_t *ns_list;
		cfg_t *ns_password;
		cfg_t *ns_default;
		cfg_t *nickserv = cfg_getsec(cfg, "nickserv");

		/* section general */
		ns_general = cfg_getsec(nickserv, "general");
		ns_name = cfg_getstr(ns_general, "name");
		ns_realname = cfg_getstr(ns_general, "realname");
		ns_expiry = cfg_getint(ns_general, "expiry");

		/* section registration */
		ns_reg = cfg_getsec(nickserv, "registration");
		ns_autoaccess = cfg_getint(ns_reg, "autoaccess");

		/* section list */
		ns_list = cfg_getsec(nickserv, "list");
		ns_maxlist = cfg_getint(ns_list, "maxlist");
		ns_operonly = cfg_getint(ns_list, "operonly");
		ns_access_max = cfg_getint(ns_list, "access_max");

		/* section password */
		ns_password = cfg_getsec(nickserv, "password");
		ns_enforcer = cfg_getstr(ns_password, "enforcer");
		ns_release_time = cfg_getint(ns_password, "release");

		/* section default */
		ns_default = cfg_getsec(nickserv, "default");
		ns_mlock = cfg_getstr(ns_default, "mlock");

		/* end of section nickserv */
		/* section chanserv ***********************************************************************************************/
		cfg_t *chanserv;
		cfg_t *cs_general;
		cfg_t *cs_ops;
		cfg_t *cs_password;
		cfg_t *cs_default;
		cfg_t *cs_misc;
		cfg_t *cs_list;
		chanserv = cfg_getsec(cfg, "chanserv");

		/* section general */

		cs_general = cfg_getsec(chanserv, "general");
		cs_name = cfg_getstr(cs_general, "name");
		cs_realname = cfg_getstr(cs_general, "realname");

		/* section operators */
		cs_ops = cfg_getsec(chanserv, "operators");
		cs_sops_max = cfg_getint(cs_ops, "sop_max");
		cs_aops_max = cfg_getint(cs_ops, "aop_max");
		cs_hops_max = cfg_getint(cs_ops, "hop_max");
		cs_vops_max = cfg_getint(cs_ops, "vop_max");
		cs_uops_max = cfg_getint(cs_ops, "uop_max");

		/* section list */
		cs_list = cfg_getsec(chanserv, "list");
		cs_maxlist = cfg_getint(cs_list, "maxlist");
		cs_operonly = cfg_getint(cs_list, "operonly");

		/* section password */
		cs_password = cfg_getsec(chanserv, "password");
		cs_spass = cfg_getint(cs_password, "setpass");
		cs_gpass = cfg_getint(cs_password, "getpass");
		/* section default */
		cs_default = cfg_getsec(chanserv, "default");
		cs_mlock = cfg_getstr(cs_default, "mlock");

		/* section misc */
		cs_misc = cfg_getsec(chanserv, "misc");
		cs_akick_max = cfg_getint(cs_misc, "akick_max");

		/* end of section chanserv */

		/* section operserv ***********************************************************************************************/
		cfg_t *operserv;
		cfg_t *os_general;
		cfg_t *os_global_acc;
		cfg_t *os_default;
		cfg_t *os_expiry;
		operserv = cfg_getsec(cfg, "operserv");

		/* section general */
		os_general = cfg_getsec(operserv, "general");
		os_name = cfg_getstr(os_general, "name");
		os_realname = cfg_getstr(os_general, "realname");

		/* section global */
		os_global_acc = cfg_getsec(operserv, "global");
		os_on_oper = cfg_getint(os_global_acc, "on_oper");
		os_on_mode = cfg_getint(os_global_acc, "on_mode");
		os_on_akill = cfg_getint(os_global_acc, "on_akill");
		os_on_sgline = cfg_getint(os_global_acc, "on_sgline");
		os_on_skline = cfg_getint(os_global_acc, "on_skline");
		os_on_szline = cfg_getint(os_global_acc, "on_szline");
		os_on_sqline = cfg_getint(os_global_acc, "on_sqline");
		os_on_kick = cfg_getint(os_global_acc, "on_kick");
		os_on_list = cfg_getint(os_global_acc, "on_list");
		os_on_kill = cfg_getint(os_global_acc, "on_kill");

		/* section expiry */
		os_expiry = cfg_getsec(operserv, "expiry");
		os_akill_expiry = cfg_getint(os_expiry, "akill");
		os_sgline_expiry = cfg_getint(os_expiry, "sqline");
		os_skline_expiry = cfg_getint(os_expiry, "skline");
		os_szline_expiry = cfg_getint(os_expiry, "szline");
		os_sqline_expiry = cfg_getint(os_expiry, "sqline");

		/* section default */

		os_default = cfg_getsec(operserv, "default");
		os_can_akill = cfg_getint(os_default, "can_akill");
		os_can_chghost = cfg_getint(os_default, "can_chghost");
		os_can_global = cfg_getint(os_default, "can_global");
		os_can_local = cfg_getint(os_default, "can_local");
		os_can_kick = cfg_getint(os_default, "can_kick");
		os_can_kill = cfg_getint(os_default, "can_kill");
		os_can_chatops = cfg_getint(os_default, "can_chatops");
		os_can_sgline = cfg_getint(os_default, "can_sgline");
		os_can_sqline = cfg_getint(os_default, "can_sqline");
		os_can_svsnick = cfg_getint(os_default, "can_svsnick");
		os_can_skline = cfg_getint(os_default, "can_skline");
		os_can_szline = cfg_getint(os_default, "can_szline");
		os_vhost = cfg_getstr(os_default, "vhost");

		/* end of section operserv */
		/* section botserv ************************************************************************************************/
		cfg_t *botserv;
		cfg_t *bs_general;
		cfg_t *bs_access_conf;
		botserv = cfg_getsec(cfg, "botserv");

		/* section general */
		bs_general = cfg_getsec(botserv, "general");
		bs_name = cfg_getstr(bs_general, "name");
		bs_realname = cfg_getstr(bs_general, "realname");

		/* section access */

		bs_access_conf = cfg_getsec(botserv,"access");
		bs_access_add = cfg_getint(bs_access_conf,"add");
		bs_access_del = cfg_getint(bs_access_conf,"del");
		bs_access_list = cfg_getint(bs_access_conf,"list");
		bs_access_set = cfg_getint(bs_access_conf,"set");
		bs_access_getpass = cfg_getint(bs_access_conf,"getpass");
		bs_access_setpass = cfg_getint(bs_access_conf,"setpass");

		/* end of section botserv */

		/* section adminserv ************************************************************************************************/
		cfg_t *adminserv;
		cfg_t *as_general;
		adminserv = cfg_getsec(cfg, "adminserv");

		/* section general */
		as_general = cfg_getsec(adminserv, "general");
		as_name = cfg_getstr(as_general, "name");
		as_realname = cfg_getstr(as_general, "realname");
	}
	return 0;
}
int config_cs_admin(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	cs_admin_access = val;
	return 0;
}
int config_cs_cmd_kick(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	cs_cmd_kick = val;
	return 0;
}
int config_cs_cmd_ban(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	cs_cmd_ban = val;
	return 0;
}
int config_cs_cmd_op(cfg_t *cfg, cfg_opt_t *opt, const char *value,	void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	cs_cmd_op = val;
	return 0;
}
int config_cs_cmd_mkick(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	cs_cmd_mkick = val;
	return 0;
}
int config_cs_cmd_invite(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 13)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 13);
		return -1;
	}
	cs_cmd_invite = val;
	return 0;
}
int config_ns_admin(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	ns_admin = val;
	return 0;
}
int config_ns_authchan(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	ns_auth_channel = val;
	return 0;
}
int config_ns_authnotify(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	ns_auth_notify = val;
	return 0;
}
int config_ns_autoacc(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	ns_autoaccess = val;
	return 0;
}
int config_ns_delay(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if (val < 0) {
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		cfg_error(cfg, CONF_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		return -1;
	}
	ns_delay = val;
	return 0;
}
int config_ns_getpass(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	ns_gpass = val;
	return 0;
}
int config_ns_hidemail(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	ns_hide_email = val;
	return 0;
}
int config_ns_mnotify(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	ns_mnotify = val;
	return 0;
}
int config_ns_nomemo(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	ns_no_memo = val;
	return 0;
}
int config_ns_protect(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 2)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 2);
		return -1;
	}
	ns_high_protect = val;
	return 0;
}
int config_ns_regacc(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	ns_usage_access = val;
	return 0;
}
int config_ns_setpass(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	ns_spass = val;
	return 0;
}
int config_oper(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	*(const char **) result = (const char *) value;
	return 0;
}
int config_as_access_flag(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 6)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 6);
		return -1;
	}
	*(const char **) result = (const char *) value;
	as_access_flag = val;
	return 0;
}
int config_passAction(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if ((val < 0) || (val > 4)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 4);
		return -1;
	}
	s_PassAction = val;
	return 0;
}
int config_port(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int val = atoi(value);
	if ((val < 1) || (val > 65535)) {
		cfg_error(cfg, CONF_ERR_PORTOUTOFRANGE, CONFIG_FILE, cfg->line,
				opt->name);
		addlog(2, CONF_LOG_ERR_PORTOUTOFRANGE, CONFIG_FILE, cfg->line,
				opt->name);
		return -1;
	}
	s_port = val;
	return 0;
}
int config_s_globaloncycle(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (!isbool(val)) {
		cfg_error(cfg, CONF_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_MUSTBEBOOL, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	s_global_on_cycle = val;
	return 0;
}
int config_s_keeplogs(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int val = atoi(value);
	if (val < 0) {
		cfg_error(cfg, CONF_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line, opt->name);
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line, opt->name);
		return -1;
	}
	//s_keeplogfiles = val;
	return 0;
}
int config_s_passlimit(cfg_t *cfg, cfg_opt_t *opt, const char *value,void *result) {
	int var = atoi(value);
	if (var < 0) {
		cfg_error(cfg, CONF_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		return -1;
	}
	s_PassLimit = var;
	return 0;
}
int config_str32(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	const char *var = value;
	if ((var == NULL )|| (strcmp(var,"")==0)){
	addlog(2,CONF_LOG_ERR_MISSINGOPT,CONFIG_FILE,cfg->line,opt->name);
	cfg_error(cfg,CONF_ERR_MISSINGOPT,CONFIG_FILE,cfg->line,opt->name);
	return -1;
}
	if (strlen(value) > 33) {
		addlog(2, CONF_LOG_ERR_TOOMANYCHARS, CONFIG_FILE, cfg->line, opt->name,
				STRMAX);
		cfg_error(cfg, CONF_ERR_TOOMANYCHARS, CONFIG_FILE, cfg->line, opt->name,
				STRMAX);
		return -1;
	}
	*(const char**) result = (const char*) value;
	return 0;
}
int config_str64(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	const char *var = value;
	if ((var == NULL )|| (strcmp(var,"")==0)){
	addlog(2,CONF_LOG_ERR_MISSINGOPT,CONFIG_FILE,cfg->line,opt->name);
	cfg_error(cfg,CONF_ERR_MISSINGOPT,CONFIG_FILE,cfg->line,opt->name);
	return -1;
}
	if (strlen(value) > STRMAX2) {
		addlog(2, CONF_LOG_ERR_TOOMANYCHARS, CONFIG_FILE, cfg->line, opt->name,
				STRMAX2);
		cfg_error(cfg, CONF_ERR_TOOMANYCHARS, CONFIG_FILE, cfg->line, opt->name,
				STRMAX2);
		return -1;
	}
	*(const char**) result = (const char*) value;
	return 0;
}
int config_str128(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	const char *var = value;
	if ((var == NULL )|| (strcmp(var,"")==0)){
	addlog(2,CONF_LOG_ERR_MISSINGOPT,CONFIG_FILE,cfg->line,opt->name);
	cfg_error(cfg,CONF_ERR_MISSINGOPT,CONFIG_FILE,cfg->line,opt->name);
	return -1;
}
	if (strlen(value) > STRMAX3) {
		addlog(2, CONF_LOG_ERR_TOOMANYCHARS, CONFIG_FILE, cfg->line, opt->name,
				STRMAX3);
		cfg_error(cfg, CONF_ERR_TOOMANYCHARS, CONFIG_FILE, cfg->line, opt->name,
				STRMAX3);
		return -1;
	}
	*(const char**) result = (const char*) value;
	return 0;
}
int config_uint32(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int var = atoi(value);
	if (var < 0) {
		addlog(2, CONF_LOG_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		cfg_error(cfg, CONF_ERR_NEGVALUEFOUND, CONFIG_FILE, cfg->line,
				opt->name);
		return -1;
	}
	*(const char **) result = (const char *) value;
	return 0;
}
int config_cs_tlock(cfg_t *cfg, cfg_opt_t *opt, const char *value, void *result) {
	int var = atoi(value);
	if ((var < 0) || (var > 4)) {
		cfg_error(cfg, CONF_ERR_INT, CONFIG_FILE, cfg->line, opt->name, 0, 4);
		return -1;
	}
	*(const char **) result = (const char *) value;
	return 0;
}
/* EOF */
