#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "struct.h"
#include "functions.h"



int main()
{
	if (isFileFound("cfg.txt")) {
		c_page = SAVELOAD_PAGE;
	}
	student **all_students = malloc(MAX_STUDENTS *sizeof(student*));
	//loadData(all_students);
	bool is_running = true;
	//int menu_size = 6;
	int menu_size = EXIT_PAGE;
	char** MENU = malloc(sizeof(char*)* menu_size);
	if (MENU == NULL) {
		exit(-1);
	}

	while (is_running) {

		system("COLOR 10");
		system("CLS");
		PrintSRS(20,0,9);
		PrintSRS(20,10,9);
		PrintSRS(20,20,9);
		while (c_page == MENU_PAGE) {
			//system("COLOR B0");
			//system("CLS");
			for (int i = 0; i < menu_size; i++) {
				MENU[i] = malloc(sizeof(char) * 50);
				//MENU[i] = getMenuItem(i);
				if (MENU[i] != NULL) {
					strcpy(MENU[i], getMenuItem(i));
				}
			}
			if (current_active_item > EXIT || current_active_item < ADD) {
				current_active_item = ADD;
			}
			for (int i = 0; i <= EXIT; i++) {
				gotoxy(35, 5 + (i * 2));

				if (current_active_item == i) {

					SetColor2(0, 4);
					printf(" [");
					SetColor2(0, 11);

					SetColor2(14, 4);
					printf("%s", getMenuItemIcon(i));
					SetColor2(0, 11);

					SetColor2(0, 4);
					printf("] ");
					SetColor2(0, 11);


					SetColor2(15, 12);
					printf(" % s", MENU[i]);
					SetColor2(0, 11);

				}
				else {
					printf(" [ ]  %s", MENU[i]);
				}
				printf("\n");
			}

			current_active_item = setActiveMenuItem(current_active_item, menu_size, &c_page);
			//Sleep(10);


		}
		system("CLS");
		PAGE$ADD currAddP = PAGE_ADD_MENU;
		PAGE$EDIT currEditP = PAGE_EDIT_MENU;
		PAGE$EDIT currDisplayP = PAGE_DISPLAY_MENU;
		PAGE$CONFIG currConfigP = PAGE_CFG_MENU;
		int currentAddItem = 0;
		int currentEditItem = 1;
		int currentDisplayItem = 1;
		int currentConfigItem = 2;

		while (c_page == ADD_PAGE) {
			if (currAddP == PAGE_ADD_MENU) {
				system("cls");



				if (currentAddItem == 0) {
					SetColor2(14, 4);
					gotoxy(40, 10);
					printf("[ > ] Add Student To The System.");
					SetColor2(0, 11);
					gotoxy(40, 12);
					printf("[   ] Add/Edit Subject To Existed Student.");
					gotoxy(40, 14);
					printf("[   ] Back.");
				}
				else if (currentAddItem == 1) {
					gotoxy(40, 10);
					printf("[   ] Add Student To The System.");
					SetColor2(14, 4);
					gotoxy(40, 12);
					printf("[ > ] Add/Edit Subject To Existed Student.");
					SetColor2(0, 11);
					gotoxy(40, 14);
					printf("[   ] Back.");
				}
				else if (currentAddItem == 2) {
					gotoxy(40, 10);
					printf("[   ] Add Student To The System.");

					gotoxy(40, 12);
					printf("[   ] Add/Edit Subject To Existed Student.");
					SetColor2(0, 11);

					gotoxy(40, 14);
					SetColor2(14, 4);
					printf("[ > ] Back.");
					SetColor2(0, 11);
				}


				int hotAddPHotKey = getHotKey();
				if (hotAddPHotKey == KEY_UP) {
					currentAddItem = (currentAddItem - 1 + 3) % 3;
				}
				else if (hotAddPHotKey == KEY_DOWN) {
					currentAddItem = (currentAddItem + 1 + 3) % 3;
				}
				else if (hotAddPHotKey == KEY_ENTER) {

					currAddP = (PAGE$ADD)(currentAddItem + 1);

				}
				else if (hotAddPHotKey == KEY_ESC) {
					currAddP = PAGE_ADD_BACK;
				}

				system("CLS");
			}
			else if (currAddP == PAGE_ADD_STUDENT) {
				int st_id;
				char* st_name[50];
				char* first_name[25];
				char* second_name[25];
				printf("\n\n\n\n\n\n");
				printf("\t\t\t\tADD STUDENT:\n");
				printf("\t\t\t\tWrite his id: ");
				scanf("%i", &st_id);
				printf("\n");
				printf("\t\t\t\tWrite his First [or] Full Name: ");
				scanf_s("%s", &first_name);
				printf("\t\t\t\tWrite his Second Name: ");
				scanf_s("%s", &second_name);
				strcpy(st_name, first_name);
				strcat(st_name, " ");
				strcat(st_name, second_name);
				printf("\n");
				if (AddStudent(all_students, st_id, st_name)) {
					SetColor2(15,1);
					printf("\t\t\t\tYOU ADDED THE STUDENT NUMBER (%i)", next_student_index);
					SetColor2(0,11);
				}
				else {
					SetColor2(15, 4);
					printf("\n\t\t\t\tFailed To Add STUDENT - ID is already existed.\n");
					SetColor2(0, 11);
				}
				Sleep(2000);
				system("CLS");
				//c_page = MENU_PAGE;
				currAddP = PAGE_ADD_MENU;
			}
			else if (currAddP == PAGE_ADD_SUBJECT) {
				int st_id;
				printf("\nAdd Subject(s) To Student:\n");
				printf("[*] Write The Student ID: ");
				scanf("%d", &st_id);
				if (getStudentByID(all_students, st_id) == NULL) {
					SetColor2(15, 4);
					printf("You Wrote Wrong Student's ID !\n");
					SetColor2(0, 11);
					Sleep(1000);
					//c_page = MENU_PAGE;
					currAddP = PAGE_ADD_MENU;

				}
				else {
					int sub_choose = -1;
					while (sub_choose < 0 || sub_choose > MAX_SUBJECTS - 1) {
						system("cls");
						printf("\n");
						printf("Choose the subject to which you want to add the student with ID (%i): ", st_id);
						printf("\n");
						for (int i = 0; i <= LINUX_SUB; i++) {
							if (getStudentByID(all_students, st_id)->subjects[i].score < 0) {
								SetColor2(15, 0);
								printf("[%i] %s\n", i, getSubNameById(i));
								SetColor2(0, 11);
							}
							else {
								SetColor2(8, 11);
								printf("[%i] %s. (already added with score %f) [choose to re-edit]\n", i, getSubNameById(i), getStudentByID(all_students, st_id)->subjects[i].score);
								SetColor2(0, 11);
							}
						}
						//printf("0. English\n");
						//printf("1. Arabic\n");
						//printf("2. French\n");
						//printf("3. C-Langauge\n");
						//printf("4. Linux\n");
						sub_choose = getche() - '0';
					}
					float sub_score;
					printf("\nWrite The Score of %s's Subject for Student's ID(%i): ", getSubNameById(sub_choose), st_id);
					scanf("%f", &sub_score);
					if (sub_score >= 0.0 && sub_score <= 100.0) {
						UpdateSubject(getStudentByID(all_students, st_id), (SUB)sub_choose, sub_score);
						SetColor2(15, 2);
						printf("\nSubject (%s) is added successfuly to student's ID(%i).", getSubNameById(sub_choose), st_id);
						SetColor2(0, 11);
						Sleep(2000);
						currAddP = PAGE_ADD_MENU;
					}
					else {
						SetColor2(15, 12);
						printf("Sorry The Subject's Score Can't Be %f is starting form Zero & Up-To 100.", sub_score);
						SetColor2(0, 11);
						Sleep(2000);
						currAddP = PAGE_ADD_MENU;
					}
				}
				//////////

			}
			else if (currAddP == PAGE_ADD_BACK) {
				c_page = MENU_PAGE;
			}


		}
		while (c_page == EDIT_PAGE) {







			if (currEditP == PAGE_EDIT_MENU) {
				system("cls");

				for (int i = PAGE_EDIT_STUDENT_ID; i <= PAGE_EDIT_BACK; i++) {
					gotoxy(40, 10 + (i * 2));
					if (currentEditItem == i) {
						SetColor2(14, 4);
						printf("[ > ] %s.", getMenuEditPageItem(i));
						SetColor2(0, 11);
					}
					else {
						SetColor2(0, 11);
						printf("[   ] %s.", getMenuEditPageItem(i));
					}
				}


				int hotAddPHotKey = getHotKey();
				if (hotAddPHotKey == KEY_UP) {
					currentEditItem = (currentEditItem - 1 + (PAGE_EDIT_BACK + 1)) % (PAGE_EDIT_BACK + 1);
					if (currentEditItem == 0) {
						currentEditItem = PAGE_EDIT_BACK;
					}
				}
				else if (hotAddPHotKey == KEY_DOWN) {
					currentEditItem = (currentEditItem + 1 + (PAGE_EDIT_BACK + 1)) % (PAGE_EDIT_BACK + 1);
					if (currentEditItem == 0) {
						currentEditItem = PAGE_EDIT_STUDENT_ID;
					}
				}
				else if (hotAddPHotKey == KEY_ENTER) {

					currEditP = (PAGE$EDIT)(currentEditItem);

				}
				else if (hotAddPHotKey == KEY_ESC) {
					currEditP = PAGE_EDIT_BACK;
				}

				system("CLS");
			}


			else if (currEditP == PAGE_EDIT_STUDENT_ID) {
				int st_id;
				int NEW_st_id;


				printf("\nEDIT Id Of Existed Student:\n");
				printf("[*] Write The Current Student ID: ");
				scanf("%d", &st_id);
				if (getStudentByID(all_students, st_id) == NULL) {
					SetColor2(15, 4);
					printf("You Wrote Wrong Student's ID !\n");
					SetColor2(0, 11);
					Sleep(1000);
					//c_page = MENU_PAGE;
					currEditP = PAGE_EDIT_MENU;

				}
				else {
					printf("\n[!] Write THE New ID For The Student (%s) With Old ID (%i) :", getStudentByID(all_students, st_id)->name, getStudentByID(all_students, st_id)->id);
					scanf("%d", &NEW_st_id);
					int updateStuID = UpdateStudentId(all_students, st_id, NEW_st_id);
					if (updateStuID == 1) {
						printf("Updated Successfuly");
					}
					else if (updateStuID == -1) {
						printf("ERROR -> This New Id is Already owned By Another Student.");
					}
					else if (updateStuID == -2) {
						printf("ERROR -> This Current ID isn't Found in our System.");
					}
					Sleep(2000);
					currEditP = PAGE_EDIT_MENU;
				}

			}

			else if (currEditP == PAGE_EDIT_STUDENT_NAME) {
				int st_id;
				char* st_name[50];
				char* first_name[25];
				char* second_name[25];



				printf("\nEDIT Name Of Existed Student:\n");
				printf("[*] Write The Current Student ID: ");
				scanf("%d", &st_id);
				if (getStudentByID(all_students, st_id) == NULL) {
					SetColor2(15, 4);
					printf("You Wrote Wrong Student's ID !\n");
					SetColor2(0, 11);
					Sleep(1000);
					//c_page = MENU_PAGE;
					currEditP = PAGE_EDIT_MENU;

				}
				else {
					printf("\n[!] Write THE New Name For The Student (%s) With ID (%i) :\n", getStudentByID(all_students, st_id)->name, getStudentByID(all_students, st_id)->id);

					printf("Write his First [or] Full Name: ");
					scanf_s("%s", &first_name);
					printf("Write his Second Name: ");
					scanf_s("%s", &second_name);
					strcpy(st_name, first_name);
					strcat(st_name, " ");
					strcat(st_name, second_name);
					printf("\n");
					int updateStdName = UpdateStudentName(all_students, st_id, st_name);
					if (updateStdName == 1) {
						printf("The Name Is Updated Successfuly.\n");
					}
					else if (updateStdName == -1) {
						printf("ERROR -> This Current ID isn't Found in our System.\n");
					}
					Sleep(2000);
					currEditP = PAGE_EDIT_MENU;
				}


			}




			else if (currEditP == PAGE_EDIT_SUBJECT) {
				int st_id;
				printf("\nEDIT Subject(s) To Student:\n");
				printf("[*] Write The Student ID: ");
				scanf("%d", &st_id);
				if (getStudentByID(all_students, st_id) == NULL) {
					SetColor2(15, 4);
					printf("You Wrote Wrong Student's ID !\n");
					SetColor2(0, 11);
					Sleep(1000);
					//c_page = MENU_PAGE;
					currEditP = PAGE_EDIT_MENU;

				}
				else {
					int sub_choose = -1;
					while (sub_choose < 0 || sub_choose > MAX_SUBJECTS - 1) {
						system("cls");
						printf("\n");
						printf("Choose the subject to which you want to add the student with ID (%i): ", st_id);
						printf("\n");
						for (int i = 0; i <= LINUX_SUB; i++) {
							if (getStudentByID(all_students, st_id)->subjects[i].score < 0) {
								SetColor2(15, 0);
								printf("[%i] %s\n", i, getSubNameById(i));
								SetColor2(0, 11);
							}
							else {
								SetColor2(8, 11);
								printf("[%i] %s. (already added with score %f) [choose to re-edit]\n", i, getSubNameById(i), getStudentByID(all_students, st_id)->subjects[i].score);
								SetColor2(0, 11);
							}
						}
						//printf("0. English\n");
						//printf("1. Arabic\n");
						//printf("2. French\n");
						//printf("3. C-Langauge\n");
						//printf("4. Linux\n");
						sub_choose = getche() - '0';
					}
					float sub_score;
					printf("\nWrite The Score of %s's Subject for Student's ID(%i): ", getSubNameById(sub_choose), st_id);
					scanf("%f", &sub_score);
					if (sub_score >= 0.0 && sub_score <= 100.0) {
						UpdateSubject(getStudentByID(all_students, st_id), (SUB)sub_choose, sub_score);
						SetColor2(15, 2);
						printf("\nSubject (%s) is added successfuly to student's ID(%i).", getSubNameById(sub_choose), st_id);
						SetColor2(0, 11);
						Sleep(2000);
						currEditP = PAGE_EDIT_MENU;
					}
					else {
						SetColor2(15, 12);
						printf("Sorry The Subject's Score Can't Be %f is starting form Zero & Up-To 100.", sub_score);
						SetColor2(0, 11);
						Sleep(2000);
						currEditP = PAGE_EDIT_MENU;
					}
				}
				//////////

			}
			else if (currEditP == PAGE_EDIT_BACK) {
				c_page = MENU_PAGE;
			}











		}
		while (c_page == REMOVE_PAGE) {
			int st_id;
			//SetColor2(0, 12);
			system("COLOR 04");
			gotoxy(1, 10);
			printf("\t\t[!] Remove Student By ID !\n");

			printf("\t\t[+] Write The ID OF THE Student : ");
			scanf("%d", &st_id);
			if (getStudentByID(all_students, st_id) == NULL) {
				printf("\n\t\tSorrY ! This Student's ID isn't Found in our System .\n");
			}
			else {
				printf("\n\t\tARE YOU SURE ?\n");
				printf("\t\tDo You want Really Remove (%s) with Student's ID(%i) from our System ?\n", getStudentByID(all_students, st_id)->name, getStudentByID(all_students, st_id)->id);
				printf("\t\t[Write 9 To confirm , Else means Cancel ]\t");
				char delConfirm = getche();
				if (delConfirm - '0' == 9) {
					printf("\n\t\tRemoving %s with ID(%i) from our system ... \n", getStudentByID(all_students, st_id)->name, getStudentByID(all_students, st_id)->id);
					Sleep(1000);
					int rmStd = RemoveStudent(all_students, st_id);
					if (rmStd == -1) {
						printf("\n\t\tCan't Remove This Student because he is already NOT Existed in out system.\n");
					}
					else if (rmStd == 1) {
						printf("\n\t\tThe student is Removed Successfuly from our system.\n");
					}
				}
				else {
					printf("\n\t\tRemove Operation Just Canceled !");
					Sleep(1000);
				}
			}
			Sleep(3000);
			c_page = MENU_PAGE;
		}

		while (c_page == DISPLAY_PAGE) {
			//printf("ALL CURRENT STUDENTS:\n");
			//SetColor(1,9);
			//DisplayAllStudents(all_students);
			//SetColor(2, 1);
			//DisplayHighestScores(all_students);
			//Sleep(1000);
			//SetColor2(13, 14);
			//printf("[Press Any Key To Back To The Menu.]");
			//SetColor2(0, 11);
			//getch();
			//c_page = MENU_PAGE;

			while (currDisplayP == PAGE_DISPLAY_MENU) {
				system("cls");

				for (int i = PAGE_DISPLAY_SEARCH; i <= PAGE_DISPLAY_BACK; i++) {
					gotoxy(40, 5 + (i * 2));
					if (currentDisplayItem == i) {
						SetColor2(14, 4);
						printf("[>] %s", getMenuDisplayPageItem(i));
						SetColor2(0, 11);
					}
					else {
						SetColor2(0, 11);
						printf("[ ] %s", getMenuDisplayPageItem(i));
					}
				}


				int hotAddPHotKey = getHotKey();
				if (hotAddPHotKey == KEY_UP) {
					currentDisplayItem = (currentDisplayItem - 1 + (PAGE_DISPLAY_BACK + 1)) % (PAGE_DISPLAY_BACK + 1);
					if (currentDisplayItem == 0) {
						currentDisplayItem = PAGE_DISPLAY_BACK;
					}
				}
				else if (hotAddPHotKey == KEY_DOWN) {
					currentDisplayItem = (currentDisplayItem + 1 + (PAGE_DISPLAY_BACK + 1)) % (PAGE_DISPLAY_BACK + 1);
					if (currentDisplayItem == 0) {
						currentDisplayItem = PAGE_DISPLAY_SEARCH;
					}
				}
				else if (hotAddPHotKey == KEY_ENTER) {

					currDisplayP = (PAGE$DISPLAY)(currentDisplayItem);

				}
				else if (hotAddPHotKey == KEY_ESC) {
					currDisplayP = PAGE_DISPLAY_BACK;
				}

				system("CLS");

			}

			while (currDisplayP == PAGE_DISPLAY_SEARCH) {

				int StudentID;
				printf("\n\t====================\n");
				printf("\tSearch For Student By ID :");
				scanf("%d",&StudentID);

				system("CLS");
				printf("\n\t====================\n");
				printf("\tSearch For Student By ID :\n");
				DisplayOneStudent(all_students, StudentID);
				printf("\n\t====================\n");
				Sleep(1000);
				printf("\n\n");
				SetColor2(13, 14);
				printf("\t[Press Any Key To Back To The Menu.]");
				SetColor2(0, 11);
				printf("\n");
				getch();
				currDisplayP = PAGE_DISPLAY_MENU;

			}
			while (currDisplayP == PAGE_DISPLAY_HIGH_AVG) {
				DisplayHighestScores(all_students);
				Sleep(1000);
				SetColor2(13, 14);
				printf("\n\n\t[Press Any Key To Back To The Menu.]\n");
				SetColor2(0, 11);
				getch();
				currDisplayP = PAGE_DISPLAY_MENU;
				//c_page = MENU_PAGE;
			}
			while (currDisplayP == PAGE_DISPLAY_PASS) {
				printf("\n\t====================\n");
				printf("\tTHE PASS LIST FOR ALL STUDENTS & SUBJECTS\n");
				DisplayAllPassStudents(all_students);
				printf("\n\t====================\n");
				Sleep(1000);
				printf("\n\n");
				SetColor2(13, 14);
				printf("\t[Press Any Key To Back To The Menu.]");
				SetColor2(0, 11);
				printf("\n");
				getch();
				currDisplayP = PAGE_DISPLAY_MENU;
			}
			while (currDisplayP == PAGE_DISPLAY_FAIL) {
				printf("\n\t====================\n");
				printf("\tTHE FAIL LIST FOR ALL STUDENTS & SUBJECTS\n");
				DisplayAllFailStudents(all_students);
				printf("\n\t====================\n");
				Sleep(1000);
				printf("\n\n");
				SetColor2(13, 14);
				printf("\t[Press Any Key To Back To The Menu.]");
				SetColor2(0, 11);
				printf("\n");
				getch();
				currDisplayP = PAGE_DISPLAY_MENU;
			}
			while (currDisplayP == PAGE_DISPLAY_ALL) {
				printf("\n\n\tALL CURRENT STUDENTS:\n");
				SetColor2(0, 11);
				DisplayAllStudents(all_students);
				SetColor2(0, 11);

				Sleep(1000);
				printf("\n\n");
				SetColor2(13, 14);
				printf("\t[Press Any Key To Back To The Menu.]");
				SetColor2(0, 11);
				printf("\n");
				getch();
				currDisplayP = PAGE_DISPLAY_MENU;
				//c_page = MENU_PAGE;
			}

			while (currDisplayP == PAGE_DISPLAY_BACK) {
				currDisplayP = PAGE_DISPLAY_MENU;
				c_page = MENU_PAGE;
			}












		}
		while (c_page == SAVELOAD_PAGE) {
			while (currConfigP == PAGE_CFG_MENU) {
				system("cls");
				printf("\n\n\n\n\n\n\t\t================================================================================\n");
				printf("\t\t[CONFIGS] :");
				printf("\n\t\t-SAVE/LOAD STUDENTS/SUBJECTS DATA FROM/TO FILE :\n");
				for (int i = PAGE_CFG_SAVE; i <= PAGE_CFG_BACK; i++) {
					//gotoxy(40, 5 + (i * 2));
					gotoxy( (i*25+ i ), 10);
					if (currentConfigItem == i) {
						SetColor2(14, 4);
						printf("[>] %s", getMenuConfigPageItem(i));
						SetColor2(0, 11);
					}
					else {
						SetColor2(0, 11);
						printf("[ ] %s", getMenuConfigPageItem(i));
					}
				}
				printf("\n\n\n\t\t================================================================================\n");

				int hotCfgPHotKey = getHotKey();
				if (hotCfgPHotKey == KEY_UP || hotCfgPHotKey == KEY_LEFT) {
					currentConfigItem = (currentConfigItem - 1 + (PAGE_CFG_BACK + 1)) % (PAGE_CFG_BACK + 1);
					if (currentConfigItem == 0) {
						currentConfigItem = PAGE_CFG_BACK;
					}
				}
				else if (hotCfgPHotKey == KEY_DOWN || hotCfgPHotKey == KEY_RIGHT) {
					currentConfigItem = (currentConfigItem + 1 + (PAGE_CFG_BACK + 1)) % (PAGE_CFG_BACK + 1);
					if (currentConfigItem == 0) {
						currentConfigItem = PAGE_CFG_SAVE;
					}
				}
				else if (hotCfgPHotKey == KEY_ENTER) {

					currConfigP = (PAGE$CONFIG)(currentConfigItem);

				}
				else if (hotCfgPHotKey == KEY_ESC) {
					currConfigP = PAGE_CFG_BACK;
				}

				system("CLS");

			}

			while (currConfigP == PAGE_CFG_SAVE) {
				saveData(all_students);


				Sleep(2000);
				currConfigP = PAGE_CFG_MENU;
			}
			while (currConfigP == PAGE_CFG_LOAD) {
				if (isFileFound("cfg.txt")) {
					loadData(all_students);
				}
				else {
					gotoxy(10,10);
					printf("\n\t\t\t");
					SetColor2(15,4);
					printf("Sorry I couldn't find the cfg.txt file !");
					SetColor2(0,11);
				}

				Sleep(2000);
				currConfigP = PAGE_CFG_MENU;
			}
			

			while (currConfigP == PAGE_CFG_BACK) {
				currConfigP = PAGE_CFG_MENU;
				c_page = MENU_PAGE;
			}
		}
		while (c_page == EXIT_PAGE) {
			//printf("bye bye");
			PrintByeBye();
			Sleep(2000);
			c_page = BYE_PAGE;
			is_running = false;
		}
	}







	for (int i = 0; i < menu_size; i++) {
		free(MENU[i]);
	}
	free(MENU);


}
