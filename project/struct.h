#pragma once
//#define MAX_STUDENTS 100
static int MAX_STUDENTS = 100;
static int MAX_SUBJECTS = 5;
typedef struct subject subject;
typedef struct student student;
typedef enum menu menu;
typedef enum KEYS KEYS;
typedef enum bool bool;
typedef enum PAGE PAGE;
typedef enum PAGE$ADD PAGE$ADD;
typedef enum PAGE$EDIT PAGE$EDIT;
typedef enum PAGE$DISPLAY PAGE$DISPLAY;
typedef enum PAGE$CONFIG PAGE$CONFIG;
typedef enum SUB SUB;
struct subject {
	SUB id;
	//char* name;
	float score;
};
struct student {
	int id;
	char name[50];
	subject* subjects;
};
enum menu {
	ADD,
	EDIT,
	REMOVE,
	DISPLAY,
	SAVELOAD,
	EXIT
};
enum KEYS {
	NOT_KEY,
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_END = 79,
	KEY_ESC = 27,
	KEY_ENTER = 13,

};
enum bool{
false,
true,
};
enum PAGE
 {
	MENU_PAGE,
	ADD_PAGE,
	EDIT_PAGE,
	REMOVE_PAGE,
	DISPLAY_PAGE,
	SAVELOAD_PAGE,
	EXIT_PAGE,
	BYE_PAGE,
};
enum PAGE$ADD {
	PAGE_ADD_MENU,
	PAGE_ADD_STUDENT,
	PAGE_ADD_SUBJECT,
	PAGE_ADD_BACK,
};
enum PAGE$EDIT {
	PAGE_EDIT_MENU,
	PAGE_EDIT_STUDENT_ID,
	PAGE_EDIT_STUDENT_NAME,
	PAGE_EDIT_SUBJECT,
	PAGE_EDIT_BACK,
};
enum PAGE$DISPLAY {
	PAGE_DISPLAY_MENU,
	PAGE_DISPLAY_SEARCH,
	PAGE_DISPLAY_HIGH_AVG,
	PAGE_DISPLAY_PASS,
	PAGE_DISPLAY_FAIL,
	PAGE_DISPLAY_ALL,
	PAGE_DISPLAY_BACK
};
enum PAGE$CONFIG {
	PAGE_CFG_MENU,
	PAGE_CFG_SAVE,
	PAGE_CFG_LOAD,
	PAGE_CFG_BACK
};
enum SUB{
	EN_SUB,
	AR_SUB,
	FR_SUB,
	C_SUB,
	LINUX_SUB,
};

static menu current_active_item = ADD;
static PAGE c_page = MENU_PAGE;
static int next_student_index = 0;
