#ifndef _EVENT_H
#define _EVENT_H

/*struct event {
	struct tm * start_time;
	struct tm * end_time;
//	char name[255];
//	char desc[1000];
//	char * id;
	double length;
};*/

enum status { TENTATIVE, CONFIRMED, CANCELLED };

// char * members = { "DTSTART", "DTEND", "UID", "SUMMARY", ... }
// use address + offset to get size of fixed-length elements (dtstart, dtend)
// first : fixed length
// last : variables length array

/* struct vevent {
 * 	char * uid;
 *	char dtstart[25];
 *	char dtend[25];
 *	char * content[] = 0:summary, 1:location, 2:desc
 *	char * cat[] = a..b..c
 *	enum status s;
 *	int is_transp;
 * }

 // uid (with 999999 max, padded with 0) : 19970901T130000Z-000001@host.com
 
struct vevent {
	char * uid;  // creation timestamp(fixed)-id(variable)[@host.com](fixed)
	char dtstart[25];
	char dtend[25];
	char * summary;
	char * location;
	// char * status; // enum : TENTATIVE, CONFIRMED, CANCELLED
	enum status s;
	char * desc;
	int is_transp; // OPAQUE, TRANSPARENT
	int sequence;
	char * cat;
};

//typedef struct event t_event;
typedef struct vevent t_vevent; // icalendar

void create_event(char * start, char * end, char * sum, char * loc, char * cat, char * desc, t_vevent * ev);
//void duplicate_event();
char * fmtvcard(t_vevent * ev);
double duration(struct tm * end, struct tm * start);

#endif
