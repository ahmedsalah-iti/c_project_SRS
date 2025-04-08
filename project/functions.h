#pragma once
COORD coord = { 0,0 };                   // this is global variable

char* cfg = "cfg.txt";

bool isFileFound(const char* file_name) {
	FILE* f = fopen(file_name, "r");
	if (f) {
		fclose(f);
		return true;//found
	}
	else {
		return false;//not found
	}

}
bool createFile(const char* file_name) {
	FILE* f = fopen(file_name, "w");
	if (f != NULL) {
		fclose(f);
		return true;
	}
	else { return false; }
}
bool createIfNotFound(const char* file_name) {
	if (isFileFound(file_name)) {
		return true;
	}
	else {
		if (createFile(file_name)) {
			return true;
		}
		else {
			return false;
		}
	}
}
void appendText(const char* fn) {
	FILE* f = fopen(fn, "a");
	if (f) {
		fprintf(f, "test\n");
		fclose(f);
	}
}


//center of axis is set to the top left cornor of the screen
void gotoxy(int x, int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}
void SetColor2(int ForgC, int BackC)
{
	if (BackC == 11) {
		BackC = 3;
	}
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		// Combine the foreground and background colors
		wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

char* getMenuItem(menu Menu) {
	switch (Menu) {
	case ADD:
		return "Add New Student [OR] Add Subject";
		break;
	case EDIT:
		return "Edit Old Student";
		break;
	case REMOVE:
		return "Remove Old Student";
		break;
	case DISPLAY:
		return "Display Students";
		break;
	case SAVELOAD:
		return "Config (Save/Load) to/from FILE.";
		break;
	case EXIT:
		return "EXIT";
		break;
	}
}
char *getMenuItemIcon(menu Menu) {
	switch (Menu) {
	case ADD:
		return "+";
		break;
	case EDIT:
		return ">";
		break;
	case REMOVE:
		return "-";
		break;
	case DISPLAY:
		return "#";
		break;
	case SAVELOAD:
		return "÷";
		break;
	case EXIT:
		return "X";
		break;
	}
}

char* getMenuEditPageItem(PAGE$EDIT p) {
	switch (p) {
	case PAGE_EDIT_STUDENT_ID:
		return "Edit ID of Existed Student";
		break;
	case PAGE_EDIT_STUDENT_NAME:
		return "Edit Name of Existed Student";
		break;
	case PAGE_EDIT_SUBJECT:
		return "Edit Subject(s) of Existed Student";
		break;
	case PAGE_EDIT_BACK:
		return "Go Back";
		break;

	}

}
char* getMenuDisplayPageItem(PAGE$DISPLAY p) {
	switch (p) {
	case PAGE_DISPLAY_SEARCH:
		return "Search For Student By ID.";
		break;
	case PAGE_DISPLAY_HIGH_AVG:
		return "Display All Details About Highests & Averages.";
		break;
	case PAGE_DISPLAY_PASS:
		return "Display Pass List.";
		break;
	case PAGE_DISPLAY_FAIL:
		return "Display Fail List.";
		break;
	case PAGE_DISPLAY_ALL:
		return "Display Everything in the system.";
		break;
	case PAGE_DISPLAY_BACK:
		return "Go Back";
		break;

	}

}

char* getMenuConfigPageItem(PAGE$CONFIG p) {
	switch (p) {
	case PAGE_CFG_SAVE:
		return "[SAVE Data]";
		break;
	case PAGE_CFG_LOAD:
		return "[LOAD Data]";
		break;
	case PAGE_CFG_BACK:
		return "Go Back";
		break;

	}

}

int getHotKey() {
	int ch = getch();
	if (ch == -32 || ch == 224) {
	//////////HOTKEY
		ch = getch();
		return ch;
	}
	else if (ch == KEY_ENTER) {
		return KEY_ENTER;
	}
	else if (ch == KEY_ESC) {
		return KEY_ESC;
	}
	else {
		return NOT_KEY;
	}
}
PAGE menuToPage(menu m) {
	switch (m) {
	case ADD:
		return ADD_PAGE;
		break;
	case EDIT:
		return EDIT_PAGE;
		break;
	case REMOVE:
		return REMOVE_PAGE;
		break;
	case DISPLAY:
		return DISPLAY_PAGE;
		break;
	case SAVELOAD:
		return SAVELOAD_PAGE;
		break;
	case EXIT:
		return EXIT_PAGE;
		break;
	}
}
KEYS setActiveMenuItem(menu current_active_item,int size,PAGE*c_page) {
	int hotkey = getHotKey();
	switch (hotkey) {
	case KEY_UP:
		return current_active_item = (KEYS)(((int)current_active_item - 1 + size) % size);
		break;
	case KEY_DOWN:
		return current_active_item = (KEYS)(((int)current_active_item + 1 + size) % size);
		break;
	case KEY_ENTER:
		*c_page = menuToPage(current_active_item);
		break;
	default:
		if (current_active_item > -1 || current_active_item < size) {
			return current_active_item;
		}
		else {
		return ADD;
		}
		
	}


}
char* getSubNameById(SUB id) {
	switch (id) {
	case EN_SUB:
		return  "English";
		break;
	case AR_SUB:
		return  "Arabic";
		break;
	case FR_SUB:
		return  "French";
		break;
	case C_SUB:
		return  "C-Lang";
		break;
	case LINUX_SUB:
		return  "Linux";
		break;
	}

}
student* getStudentByID(student** sts, int id) {
	for (int i = 0; i < next_student_index; i++) {
		if (sts[i]->id == id) {
			return sts[i];
		}
	}
	return NULL;
}
student* getStudentByID2(student** sts, int id, int* new_next_student_index) {
	for (int i = 0; i < *new_next_student_index; i++) {
		if (sts[i]->id == id) {
			return sts[i];
		}
	}
	return NULL;
}
bool AddStudent(student **st,int id,char *name) {
	if (getStudentByID(st,id) == NULL) {
		st[next_student_index] = malloc(sizeof(student));
		st[next_student_index]->id = id;
		strcpy(st[next_student_index]->name, name);
		st[next_student_index]->subjects = malloc(sizeof(subject) * MAX_SUBJECTS);
		for (int i = 0; i < MAX_SUBJECTS; i++) {
			st[next_student_index]->subjects[i].id = (SUB)i;
			st[next_student_index]->subjects[i].score = -1.0;
		}
		next_student_index++;
		return true;
	}
	else {
		return false;
	}
}
bool AddStudent2(student** st, int id, char* name,int *new_next_student_index) {
	if (getStudentByID2(st, id, &new_next_student_index) == NULL) {
		st[*new_next_student_index] = malloc(sizeof(student));
		st[*new_next_student_index]->id = id;
		strcpy(st[*new_next_student_index]->name, name);
		st[*new_next_student_index]->subjects = malloc(sizeof(subject) * MAX_SUBJECTS);
		for (int i = 0; i < MAX_SUBJECTS; i++) {
			st[*new_next_student_index]->subjects[i].id = (SUB)i;
			st[*new_next_student_index]->subjects[i].score = -1.0;
		}
		*new_next_student_index++;
		return true;
	}
	else {
		return false;
	}
}
int UpdateStudentId(student** sts, int oldID,int newID) {
	if (getStudentByID(sts, newID) != NULL) {
		return -1;//ERROR -> This New Id is Already owned By Another Student.
	}
	if (getStudentByID(sts, oldID) == NULL) {
		return -2;//ERROR -> This Current ID isn't Found in our System.
	}
	getStudentByID(sts, oldID)->id = newID;
	return 1;//SUCCESS -> The Id is updated .
}
int UpdateStudentName(student** sts, int ID,char newName[]) {
	if (getStudentByID(sts, ID) == NULL) {
		return -1;//ERROR -> This Current ID isn't Found in our System.
	}
	else {
		strcpy(getStudentByID(sts, ID)->name, newName);
		return 1;//SUCCESS -> name is updated.
	}
}

void UpdateSubject(student *st,SUB sub,float score) {
	st->subjects[(int)sub].score = score;
}
/*
int RemoveStudent(student** sts, int ID) {
	if (getStudentByID(sts, ID) == NULL) {
		return -1;//ERROR -> This Current ID isn't Found in our System.
	}
	else {
		student* theStudent = getStudentByID(sts, ID);
		student** sts_NEW = malloc(MAX_STUDENTS * sizeof(student*));
		if (sts_NEW == NULL) {
			return -2;//failed
		}
		int newNextIndex = 0;
		for (int i = 0; i < next_student_index;i++) {
			if (sts[i] != theStudent) {
				if (AddStudent2(sts_NEW, sts[i]->id, sts[i]->name, &newNextIndex)) {
					for (int x = EN_SUB; x <= LINUX_SUB; x++) {
						UpdateSubject(sts_NEW[newNextIndex - 1], x, sts[i]->subjects[x].score);
					}
				}
				else {
				//failed and cancel
					for (int j = 0; j < newNextIndex; j++) {
						free(sts_NEW[j]->subjects);
						free(sts_NEW[j]);
					}
					free(sts_NEW);
					return -3;//failed
				}
				
			}
		}
		for (int i = 0; i < next_student_index; i++) {
			//free(&sts[i]->subjects);
			free(sts[i]->subjects);
			free(sts[i]);
		}
		free(sts);
		sts = sts_NEW;
		next_student_index = newNextIndex;
		return 1;//Removed Successfuly.
	}
}
*/


int RemoveStudent(student** sts, int ID) {
	student* currentStudent = getStudentByID(sts, ID);
	if (currentStudent == NULL) {
		return -1;
	}
	int skipIndex;
	student** newAllStudents = malloc(MAX_STUDENTS * sizeof(student*));
	if (newAllStudents == NULL) { return -1; }
	for (int i = 0; i < next_student_index; i++) {
		if (sts[i]->id != ID) {
			newAllStudents[i] = malloc(sizeof(student));
			if (newAllStudents[i] == NULL) { return -1; }
			newAllStudents[i]->id = sts[i]->id;
			strcpy(newAllStudents[i]->name, sts[i]->name);
			newAllStudents[i]->subjects = malloc(sizeof(subject) * MAX_SUBJECTS);
			if (newAllStudents[i]->subjects == NULL) { return -1; }
			for (int x = 0; x < MAX_SUBJECTS; x++) {
				newAllStudents[i]->subjects[x].id = sts[i]->subjects[x].id;
				newAllStudents[i]->subjects[x].score = sts[i]->subjects[x].score;
			}
		}
		else {
			skipIndex = i;
			newAllStudents[i] = malloc(sizeof(student));

			if (newAllStudents[i] == NULL) { return -1; }
			newAllStudents[i]->id = sts[i]->id;
			strcpy(newAllStudents[i]->name, sts[i]->name);
			newAllStudents[i]->subjects = malloc(sizeof(subject) * MAX_SUBJECTS);
			if (newAllStudents[i]->subjects == NULL) { return -1; }
			for (int x = 0; x < MAX_SUBJECTS; x++) {
				newAllStudents[i]->subjects[x].id = sts[i]->subjects[x].id;
				newAllStudents[i]->subjects[x].score = sts[i]->subjects[x].score;
			}
		}
	}
	bool isSkipIndexFound = false;
	bool isNextIndexDecreased = false;
	for (int i = 0; i < next_student_index; i++) {
		free(sts[i]->subjects);
		free(sts[i]);
		if (skipIndex != i && !isSkipIndexFound) {
			sts[i] = malloc(sizeof(student));
			sts[i]->id = newAllStudents[i]->id;
			strcpy(sts[i]->name, newAllStudents[i]->name);
			sts[i]->subjects = malloc(sizeof(subject) * MAX_SUBJECTS);
			for (int x = 0; x < MAX_SUBJECTS; x++) {
				sts[i]->subjects[x].id = newAllStudents[i]->subjects[x].id;
				sts[i]->subjects[x].score = newAllStudents[i]->subjects[x].score;
			}
		}
		else {
			if (next_student_index > 1) {
				sts[i] = malloc(sizeof(student));
				sts[i]->id = newAllStudents[i + 1]->id;
				strcpy(sts[i]->name, newAllStudents[i + 1]->name);
				sts[i]->subjects = malloc(sizeof(subject) * MAX_SUBJECTS);
				for (int x = 0; x < MAX_SUBJECTS; x++) {
					sts[i]->subjects[x].id = newAllStudents[i + 1]->subjects[x].id;
					sts[i]->subjects[x].score = newAllStudents[i + 1]->subjects[x].score;
				}
				if (!isNextIndexDecreased) {
					next_student_index--;
				}
			}
			else {
				next_student_index--;
			}
		}
	}
	for (int i = 0; i <= next_student_index; i++) {
		free(newAllStudents[i]->subjects);
		newAllStudents[i];
	}
	free(newAllStudents);

	return 1;
}



char getGradeByScore(float score) {

	if (score >= 90 ) {
		return 'A';
	}
	else if (score >= 80 && score < 90) {
		return 'B';
	}else if (score >= 70 && score < 80){
		return 'C';
	}
	else if (score >= 60 && score < 70) {
		return 'D';
	}
	else if (score < 60) {
		return 'F';
	}
	else {
		return 'U';//unknwon !
	}
}
bool getPassStateByScore(float score) {
	if (score >= 60.0) {
		return true;
	}
	else {
		return false;
	}
}

float compare(const float *a,const float *b){
	return memcmp(a, b, sizeof(float));
}
int compare_desc(const void* a, const void* b) {
	return memcmp(b, a, sizeof(float));  // Reverse order for descending
}
int getRankInSubByID(student** sts,int ID,SUB sub) {
	float* ScoresList = malloc(sizeof(float)*next_student_index);
	int rank = -1;
	for (int i = 0; i < next_student_index;i++) {
		ScoresList[i] = sts[i]->subjects[sub].score;
	}
	qsort(ScoresList, next_student_index, sizeof(float), compare_desc);
	float score = getStudentByID(sts, ID)->subjects[sub].score;
	for (int i = 0; i < next_student_index && rank == -1; i++) {
		if (score == ScoresList[i]) {
			rank = i + 1;
	   }
	}
	return rank;
}
student* getTopOne_NOTwoRK(student** sts,SUB sub) {

	float* ScoresList = malloc(sizeof(float) * next_student_index);
	int rank = -1;
	for (int i = 0; i < next_student_index; i++) {
		ScoresList[i] = sts[i]->subjects[sub].score;
	}
	qsort(ScoresList, next_student_index, sizeof(float), compare_desc);
	for (int i = 0; i < next_student_index && rank == -1; i++) {
		for (int x = 0; x < next_student_index; x++) {

			if (sts[i]->subjects[sub].score == ScoresList[x] && ScoresList[x] >=0) {
				return sts[i];
			}
		}

	}
	return NULL;
}

student* getTopOne(student **sts,SUB sub) {
	student* top = NULL;
	float highestScore = -1.0f;
	for (int i = 0; i < next_student_index;i++) {
		float currentScore = sts[i]->subjects[sub].score;
		if (currentScore >=0 && currentScore > highestScore) {
			highestScore = currentScore;
			top = sts[i];
		}
	}
	return top;
}

float getAvgOfSub(student** sts,SUB sub) {
	int total_students = 0;
	float total_score = 0.0;

	for (int i = 0; i < next_student_index; i++) {
		if (sts[i]->subjects[sub].score >= 0 && sts[i]->subjects[sub].score <=100.0) {
			total_students++;
			total_score += sts[i]->subjects[sub].score;
		}
	}
	if (total_students > 0) {
	 	return (float)	(total_score / (float)total_students);
	}
	else {
		return 0.0;
	}
}
float getAvgOfStudent(student *stu) {
	int total_subjects = 0;
	float total_score = 0;
	for (int i = 0; i <= LINUX_SUB; i++) {
		if (stu->subjects[i].score > ((float)-1.0)) {
			total_subjects++;
			total_score += stu->subjects[i].score;
		}
	}
	if (total_subjects > 0) {
		return (float)(total_score / (float) total_subjects);
	}
	else {
		return -1.0;//he didn't join any sub.
	}
}
void DisplayAllStudents(student** st) {
	
	int counter = 0;	

	for (int i = 0; i < next_student_index; i++) {
		counter++;
		printf("\t====================\n");
		SetColor2(1, 9);
		printf("\tStudent.ID: %i.", st[i]->id);
		SetColor2(0, 11);

		printf("\n");
		SetColor2(1, 3);
		printf("\tStudent.Name: %s.", st[i]->name);

		SetColor2(0, 11);
		printf("\n\n");
		for (int x = 0; x < MAX_SUBJECTS; x++) {
			if (st[i]->subjects[x].score > 0) {

				SetColor2(14, 0);
				printf("\tSubject: %s", getSubNameById(st[i]->subjects[x].id));
				SetColor2(0, 11);
				printf("\n");
				SetColor2(5, 11);
				printf("\tScore: %.2f\n\tGrade: (%c)\n", st[i]->subjects[x].score, getGradeByScore(st[i]->subjects[x].score));
				SetColor2(0, 11);
				if (getPassStateByScore(st[i]->subjects[x].score) == true) {
					SetColor2(2, 11);
					printf("\tPass Statue : Passed");
					SetColor2(0, 11);
					printf("\n\n\tRANK : (TOP %i)\n", getRankInSubByID(st, st[i]->id, st[i]->subjects[x].id));




				}
				else {
					SetColor2(4, 11);
					printf("\tPass Statue : Failed");
					SetColor2(0, 11);
					printf("\n");
				}
				printf("\t[NOTE]: The AvG Score for %s Subject is %.1f .\n", getSubNameById(st[i]->subjects[x].id), getAvgOfSub(st, st[i]->subjects[x].id));
				student* top = getTopOne(st, st[i]->subjects[x].id);
				printf("\t[NOTE]: Highest Score in %s Subject is %0.1f By (%s) ID(%i) .\n",
					getSubNameById(st[i]->subjects[x].id), top->subjects[x].score, top->name, top->id);



				printf("\n");
			}


		}

		if (getAvgOfStudent(st[i]) > -1.0) {
			SetColor2(0, 15);
			printf("\t[NOTE]:The AVG SCORE FOR The Student %s id(%i) in his all subjects: %0.1f"
				, st[i]->name, st[i]->id, getAvgOfStudent(st[i]));
			SetColor2(0, 11);
		}
		else {
			SetColor2(15, 4);
			printf("\t[NOTE]: The Student %s id(%i) didn't Join Any Subjects Yet !."
				, st[i]->name, st[i]->id, getAvgOfStudent(st[i]));
			SetColor2(0, 11);
		}

		SetColor2(0, 11);
		printf("\n\t====================\n");
	}
	if (counter == 0) {
		SetColor2(15, 4);
		printf("\n\tSorry There is no any student registered in our system yet !");
		SetColor2(0, 11);
	}

}
void DisplayOneStudent(student** st,int studentID) {
	student *SearchStudent = getStudentByID(st, studentID);
	if (SearchStudent == NULL) {

		SetColor2(15, 4);
		printf("\n\tSorry There is no student With This ID !");
		SetColor2(0, 11); printf("");
		return;
	}
	//for (int i = 0; i < next_student_index; i++) {
		
		printf("\t====================\n");
		SetColor2(1, 9);
		printf("\tStudent.ID: %i.", SearchStudent->id);
		SetColor2(0, 11);

		printf("\n");
		SetColor2(1, 3);
		printf("\tStudent.Name: %s.", SearchStudent->name);
		SetColor2(0, 11);
		printf("\n\n");
		for (int x = 0; x < MAX_SUBJECTS; x++) {
			if (SearchStudent->subjects[x].score > 0) {

				SetColor2(14, 0);
				printf("\tSubject: %s", getSubNameById(SearchStudent->subjects[x].id));
				SetColor2(0, 11);
				printf("\n");
				SetColor2(5, 11);
				printf("\tScore: %.2f\n\tGrade: (%c)\n", SearchStudent->subjects[x].score, getGradeByScore(SearchStudent->subjects[x].score));
				SetColor2(0, 11);
				if (getPassStateByScore(SearchStudent->subjects[x].score) == true) {
					SetColor2(2, 11);
					printf("\tPass Statue : Passed");
					SetColor2(0, 11);
					printf("\n\n\tRANK : (TOP %i)\n", getRankInSubByID(st, SearchStudent->id, SearchStudent->subjects[x].id));




				}
				else {
					SetColor2(4, 11);
					printf("\tPass Statue : Failed");
					SetColor2(0, 11);
					printf("\n");
				}
				printf("\t[NOTE]: The AvG Score for %s Subject is %.1f .\n", getSubNameById(SearchStudent->subjects[x].id), getAvgOfSub(st, SearchStudent->subjects[x].id));
				student* top = getTopOne(st, SearchStudent->subjects[x].id);
				printf("\t[NOTE]: Highest Score in %s Subject is %0.1f By (%s) ID(%i) .\n",
					getSubNameById(SearchStudent->subjects[x].id), top->subjects[x].score, top->name, top->id);



				printf("\n");
			}


		}

		if (getAvgOfStudent(SearchStudent) > -1.0) {
			SetColor2(0, 15);
			printf("\t[NOTE]:The AVG SCORE FOR The Student %s id(%i) in his all subjects: %0.1f"
				, SearchStudent->name, SearchStudent->id, getAvgOfStudent(SearchStudent));
			SetColor2(0, 11);
		}
		else {
			SetColor2(15, 4);
			printf("\t[NOTE]: The Student %s id(%i) didn't Join Any Subjects Yet !."
				, SearchStudent->name, SearchStudent->id, getAvgOfStudent(SearchStudent));
			SetColor2(0, 11);
		}

		SetColor2(0, 11);
		printf("\n\t====================\n");
	//}


}

void DisplayAllPassStudents(student** st) {
	int counter = 0;
	for (int i = 0; i < next_student_index; i++) {
		printf("\t====================\n");
		for (int x = 0; x < MAX_SUBJECTS; x++) {
			if (st[i]->subjects[x].score > 0 && getPassStateByScore(st[i]->subjects[x].score) == true) {
				counter++;
				SetColor2(1, 3);
				printf("\tStudent: %s id(%i) .", st[i]->name, st[i]->id);
				SetColor2(0, 11);
				printf("\n");
				SetColor2(14, 0);
				printf("\tSubject: %s", getSubNameById(st[i]->subjects[x].id));
				SetColor2(0, 11);
				printf("\n");
				SetColor2(5, 11);
				printf("\tScore: %.2f\n\tGrade: (%c)\n", st[i]->subjects[x].score, getGradeByScore(st[i]->subjects[x].score));
				SetColor2(0, 11);
				printf("\t[NOTE]: The AvG Score for %s Subject is %.1f .\n", getSubNameById(st[i]->subjects[x].id), getAvgOfSub(st, st[i]->subjects[x].id));
				student* top = getTopOne(st, st[i]->subjects[x].id);
				printf("\t[NOTE]: Highest Score in %s Subject is %0.1f By (%s) ID(%i) .\n",
					getSubNameById(st[i]->subjects[x].id), top->subjects[x].score, top->name, top->id);

			}


		}

		SetColor2(0, 11);
		//printf("\n\t====================\n");
	}
	if (counter == 0) {
		SetColor2(15, 4);
		printf("\n\tSorry There is no student passed any subject(s).");
		SetColor2(0, 11);
	}
}

void DisplayAllFailStudents(student** st) {

	int counter = 0;
	for (int i = 0; i < next_student_index; i++) {
		printf("\t====================\n");
		for (int x = 0; x < MAX_SUBJECTS; x++) {
			if (st[i]->subjects[x].score > 0 && getPassStateByScore(st[i]->subjects[x].score) == false) {
				counter++;
				SetColor2(1, 3);
				printf("\tStudent: %s id(%i) .", st[i]->name, st[i]->id);
				
				
				SetColor2(0, 11);
				printf("\n");
				SetColor2(14, 0);
				printf("\tSubject: %s", getSubNameById(st[i]->subjects[x].id));
				SetColor2(0, 11);
				printf("\n");
				SetColor2(5, 11);
				printf("\tScore: %.2f\n\tGrade: (%c)\n", st[i]->subjects[x].score, getGradeByScore(st[i]->subjects[x].score));
				SetColor2(0, 11);
				printf("\t[NOTE]: The AvG Score for %s Subject is %.1f .\n", getSubNameById(st[i]->subjects[x].id), getAvgOfSub(st, st[i]->subjects[x].id));
				student* top = getTopOne(st, st[i]->subjects[x].id);
				printf("\t[NOTE]: Highest Score in %s Subject is %0.1f By (%s) ID(%i) .\n",
					getSubNameById(st[i]->subjects[x].id), top->subjects[x].score, top->name, top->id);

			}


		}

		SetColor2(0, 11);
		//printf("\n\t====================\n");
	}
	if (counter == 0) {
		SetColor2(15, 2);
		printf("\n\tGood Job ! There is no any Student Failed in Any Subject Yet !.");
		SetColor2(0, 11);
	}

}



void DisplayHighestScores(student** st){
	printf("\n\tThe currently registered subjects and their joined students in our system:\n\n");
	int counter = 0;
		for (int x = EN_SUB; x <= LINUX_SUB; x++) {
			student* top = getTopOne(st, x);
			if (top != NULL) {
				counter++;
				printf("\n=========================================================\n");
				SetColor2(0,10);
				printf("[$]%s ",getSubNameById(x));
				SetColor2(0, 11);
				printf("\n");

				printf("\tThe AvG Score For %s Subject is : %0.1f\n", getSubNameById(x), getAvgOfSub(st,x));
				printf("\tHighest Score is %0.1f By (%s) ID(%i)\n",
					top->subjects[x].score, top->name,top->id);
				printf("\n=========================================================\n");
			}
		}
		if (counter == 0) {

			SetColor2(15, 4);
			printf("\n\tSorry There is no student registered in our system yet !.");
			SetColor2(0, 11);
		}
	
}



void PrintSRS(int x,int y, int col)
{
	//SetColor2(4, 11);
	SetColor(col);
gotoxy(x, y+2);
printf(" ######  ########   ######          ########  ##    ##            ###     ###### ");
gotoxy(x, y + 3);
printf("##    ## ##     ## ##    ##         ##     ##  ##  ##            ## ##   ##    ##");
gotoxy(x, y + 4);
printf("##       ##     ## ##               ##     ##   ####            ##   ##  ##      ");
gotoxy(x, y + 5);
printf(" ######  ########   ######  ####### ########     ##    ####### ##     ##  ###### ");
gotoxy(x, y + 6);
printf("      ## ##   ##         ##         ##     ##    ##            #########       ##");
gotoxy(x, y + 7);
printf("##    ## ##    ##  ##    ##         ##     ##    ##            ##     ## ##    ##");
gotoxy(x, y + 8);
printf(" ######  ##     ##  ######          ########     ##            ##     ##  ###### ");


}
void PrintByeBye() {
	system("COLOR C4");
	gotoxy(10, 10);
	SetColor2(15, 12);
	printf("########  ##    ## ########    ########  ##    ## ########\n");
	gotoxy(10, 11);
	printf("##     ##  ##  ##  ##          ##     ##  ##  ##  ##	  \n");
	gotoxy(10, 12);
	printf("##     ##   ####   ##          ##     ##   ####   ##	  \n");
	gotoxy(10, 13);
	printf("########     ##    ######      ########     ##    ######  \n");
	gotoxy(10, 14);
	printf("##     ##    ##    ##          ##     ##    ##    ##	  \n");
	gotoxy(10, 15);
	printf("##     ##    ##    ##          ##     ##    ##    ##	  \n");
	gotoxy(10, 16);
	printf("########     ##    ########    ########     ##    ########\n");
}

void loadData(student **st){
	if (createIfNotFound(cfg)) {
		FILE* f = fopen(cfg,"r");
		int total_students = 0;
		fscanf(f,"[total_students]:%d\n",&total_students);
		if (total_students < 1) {
			gotoxy(10, 10);
			printf("\n\t\t\t");
			SetColor2(15, 4);
			printf("Sorry Something went wrong There is No data to load it !.");
			SetColor2(0, 11);
			fclose(f);
			return;
		}
		for (int i = 0; i < total_students; i++) {
			int id;
			char firstName[25];
			char lastName[25];
			char fullName[50];
			fscanf(f,"%d:%s %s\n",&id,firstName,lastName);
			strcpy(fullName,firstName);
			strcat(fullName, " ");
			strcat(fullName, lastName);

			if (AddStudent(st, id, fullName)) {
				fscanf(f,"[subjects]\n");
				for (int x = 0; x < MAX_SUBJECTS; x++) {
					float subValu;
					fscanf(f,"%f:",&subValu);
					if (subValu > 0) {
						student *theStudent = getStudentByID(st, id);
						UpdateSubject(theStudent, x, subValu);
					}
				}
			}
		}


		gotoxy(10, 10);
		SetColor2(15, 2);
		printf("\n\t\t\tData Loaded Successfuly !\n");
		SetColor2(0, 11);
		fclose(f);
	}
}

void saveData(student** st) {
	remove(cfg);
	if (createIfNotFound(cfg)) {
		FILE* f = fopen(cfg, "w");
		fprintf(f, "[total_students]:%i\n", next_student_index);
		for (int i = 0; i < next_student_index; i++) {
			fprintf(f, "%i:%s\n", st[i]->id, st[i]->name);
			fprintf(f, "[subjects]\n");
			for (int x = 0; x < MAX_SUBJECTS; x++) {
				if (x != MAX_SUBJECTS - 1) {
					fprintf(f, "%f:", st[i]->subjects[x].score);
				}
				else {
					fprintf(f, "%f\n", st[i]->subjects[x].score);
				}
			}
		}
		fclose(f);
		gotoxy(10, 10);
		SetColor2(15, 2);
		printf("\n\t\t\tData IS Saved Successfuly in cfg.txt !\n");
		SetColor2(0, 11);
	}
	else {
		gotoxy(10, 10);
		SetColor2(15, 4);
		printf("\n\t\t\tSomething went wrong i couldn't create the cfg.txt file !\n");
		SetColor2(0, 11);
	}
}