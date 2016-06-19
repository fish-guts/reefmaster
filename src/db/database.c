/*
 *      database.c - severin
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
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "main.h"

/****************************************************************************************/
/**
 * load the module tables
 */
void load_database(void) {
	addlog(1, LOG_DBG_ENTRY, "load_database");
	if (bs_enabled) {
		load_botserv();
	}
	if (ns_enabled) {
		load_nickserv();
	}
	if (cs_enabled) {
		//load_chanserv();
	}
	if (os_enabled) {
		//load_opers();
	}
	addlog(1, LOG_DBG_EXIT, "load_database");
}


/****************************************************************************************/
/**
 * save the database (this is for the external call,
 * e.g. from adminserv)
 */
void save_database(void) {
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	double start_mill = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
	//save_botserv_db();
	save_nickserv_db();
	//save_chanserv_db();
	gettimeofday(&stop, NULL);
	double end_mill = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000;
	double time = end_mill - start_mill;

	globops(s_name, "Database written to disk (%.2f s)", time / 1000.0);
}
/* EOF */
