/*
 *      log.c - severin
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
 
 void addlog(short type,char *msg,...)
 {
 	FILE *pFile;
 	char *buf = (char*)malloc(sizeof(char*)*2048);
 	char buff[2048];
 	char *logfile = s_log;
 	struct tm *ptr;
 	time_t cur;
 	char str[128];
	va_list va;
	va_start(va,msg);
	vsprintf(buff,msg,va); 	
	cur = time(NULL);
	ptr = localtime(&cur);
	strftime(str,100,"[%d/%m/%y %T]",ptr); 	
 	if((!logfile) || (logfile==NULL))
 		logfile = "log/server.log";
 	pFile = fopen(logfile,"a+");
  	switch(type)
 	{
 		case 1:
 			sprintf(buf,"%s [DEBUG] %s\n",str,buff);
 			break;
 		case 2:
 			sprintf(buf,"%s [ERROR] %s\n",str,buff);
 			break; 			
 	}
 	if(pFile)
 	{
 		fputs(buf,pFile);
 		fclose(pFile);
 		return;
 	}
 }
 
char *logline(char **av,int ac)
{	
 	char line[128]= "";
 	char *buf;
 	int x;
	for(x = 0;x<ac;x++)
	{
		strcat(line,av[x]);
		strcat(line," ");
	}
	buf = line;
	return buf;
}
