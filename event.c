#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "event.h"

/* Date format : 03/10/2024 08h00 - 17 chars */

void create_event(char * start, 
		  char * end, 
		  char * sum, 
		  char * loc, 
		  char * cat,
		  char * desc, 
		  t_vevent * ev) {

	char * event;

	char * fmt = "%m/%d/%Y %H:%M";
	char * calFmt = "%Y%m%dT%H%M%SZ";

	struct tm * ev_start = malloc(sizeof(struct tm));
        struct tm * ev_end = malloc(sizeof(struct tm));

	// convert datetime to tm struct
	strptime(start, fmt, ev_start);
        strptime(end, fmt, ev_end);


	// format datetime YYYYMMDDTHHMMSSZ
	strftime(ev->dtstart, 25, calFmt, ev_start);
	strftime(ev->dtend, 25, calFmt, ev_end);

	// copy summary, desc, location ...
	ev->summary = malloc(sizeof(char) * strlen(sum) + 1);
	ev->location = malloc(sizeof(char) * strlen(loc) + 1);
	ev->desc = malloc(sizeof(char) * strlen(desc) + 1);
	ev->cat = malloc(sizeof(char) * strlen(cat) + 1);

	strncpy(ev->summary, sum, strlen(sum));
	strncpy(ev->location, loc, strlen(loc));
	strncpy(ev->desc, desc, strlen(desc));
	strncpy(ev->cat, cat, strlen(cat));
}

char * fmtvcard(t_vevent * ev) {
	int i;
	int vcard_len;

	// sizeof(members) + 'x' * ':'
	//
	char * strvcard = malloc(sizeof(char) * 15
				+ sizeof(char) * 5
				+ sizeof(ev->uid)
				+ sizeof(char) * 9
				+ sizeof(ev->dtstart)
				+ sizeof(char) * 7
				+ sizeof(ev->dtend)
				+ sizeof(char) * 10
				+ sizeof(ev->summary)
				+ sizeof(char) * 10
				+ sizeof(ev->location)
				+ sizeof(char) * 12
				+ sizeof(ev->cat)
				+ sizeof(char) * 13
				+ sizeof(ev->desc)
				+ sizeof(char) * 11);
	// exclude begin and end 
	/* (while members) {
	 * 
	 * char * p = malloc(sizeof(member)) ...
	 * strncat(strvcard, member, strlen(member));
	 * 
	 */
	strncpy(strvcard, "BEGIN:VEVENT\n", strlen("BEGIN:VEVENT\n"));
	strncat(strvcard, "DTSTART:", strlen("DTSTART:") +1 );
	strncat(strvcard, ev->dtstart, strlen(strvcard) + strlen(ev->dtstart) + 1);
	strncat(strvcard, "\n", strlen(strvcard) + +1);
	strncat(strvcard, "DTEND:", strlen("DTEND:") + 1);
	strncat(strvcard, ev->dtend, strlen(strvcard) + strlen(ev->dtend) + 1);
	strncat(strvcard, "\n", strlen(strvcard) + +1);
	strncat(strvcard, "SUMMARY:", strlen("SUMMARY:") + 1);
	strncat(strvcard, ev->summary, strlen(ev->summary) + strlen(ev->summary) + 1);	
	strncat(strvcard, "\n", strlen(strvcard) + +1);
	strncat(strvcard, "LOCATION:", strlen("LOCATION:") + 1);
	strncat(strvcard, ev->location, strlen(ev->location) + strlen(ev->location) + 1);
	strncat(strvcard, "\n", strlen(strvcard) + +1);
	strncat(strvcard, "CATEGORIES:", strlen("CATEGORIES:") + 1);
	strncat(strvcard, ev->cat, strlen(ev->cat) + strlen(ev->cat) + 1);
	strncat(strvcard, "\n", strlen(strvcard) + +1);
	strncat(strvcard, "END:VEVENT\n", strlen("END:VEVENT\n") + 1);

	return strvcard;
	
}

/* double duration(struct tm * end, struct tm * start) {

	time_t * st;
	time_t * e;
	double dur;

	st = mktime(start);
	e = mktime(end);

	dur = difftime(e, st);

	return dur;
}*/


