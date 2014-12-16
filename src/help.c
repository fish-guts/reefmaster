/*
 * ns_help.c
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

/**
 * ns_help handle the Nickserv HELP commands
 * Displays the usage of the specified Nickserv command
 */

void help_message(const char *service,char *src, const char *helpfile) {
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	fp = fopen(helpfile, "r");
	notice(as_name,src,"Help :%s",helpfile);
	if (fp == NULL)
		notice(service,src,"Error getting help");

	while ((read = getline(&line, &len, fp)) != -1) {
		char *fline = str_replace(line,"<b>","\2");
		char *gline = str_replace(fline,"</b>","\2");
		notice(service,src,"%s",gline);
	}
	fclose(fp);
	if (line)
		free(line);
}

int file_exists(const char *file) {
	FILE *fp;
	fp = fopen(file, "r");
		if (fp == NULL)
			return 0;
	fclose(fp);
	return 1;
}
