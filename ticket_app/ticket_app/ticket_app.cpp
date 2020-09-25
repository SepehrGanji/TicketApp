#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <string>
#include <ctime>
#include <math.h>

using namespace std;
void mainpage();
void checkfiles();
void signup(char);
void signin();
void edit_info(int);
void allusers();
void editvehicles();
void newtravel(char[16], char);
void alltravels();
void travellist();
void ticket();
void tickethist();
void cancleticket();
void travel_passengers(int);
void edit_trip(int);

string user = "guest";
//username password account fullname phone type
// type -> (a : admin) (u : user) (p : airplane) (t : train) (b : bus)
struct person{
	char username[16];
	char password[32];
	long int account;
	char fullname[32];
	char phone[12];
	char type;
};
person cur;

struct tim {
	int tm_sec;   // seconds of minutes from 0 to 61
	int tm_min;   // minutes of hour from 0 to 59
	int tm_hour;  // hours of day from 0 to 24
	int tm_mday;  // day of month from 1 to 31
	int tm_mon;   // month of year from 0 to 11
	int tm_year;  // year since 1900
	int tm_wday;  // days since sunday
	int tm_yday;  // days since January 1st
	int tm_isdst; // hours of daylight savings time
};

int main(){
	system("Color 5F");
	printf("Welcome to ticket app!\n");
	checkfiles();
	cur.type = 'g';
	mainpage();
	return 0;
}

void mainpage() {
	system("Color 5F");
	int boo = 1;
	while (boo) {
		if (boo == 1) {
			cout << "Dear " << user << endl;
			printf("What do you want to do?");
			printf("\t sign up -> u");
			printf("\t sign in -> i");
			printf("\t buy ticket -> t");
			if (user != "guest") {
				printf("\n editinfo -> f");
				if (cur.type == 'u') {
					//user
					printf("\t cancle ticket -> c");
					printf("\t ticket history -> h");
				}else if (cur.type == 'a') {
					//admin
					printf("\t all users -> a");
					printf("\t all travels -> A");
					printf("\t add driver -> d");
					printf("\n edit driver -> D");
					printf("\t edit travel -> E");
					printf("\t edit prices and vehicles -> p");
				}else {
					//driver
					printf("\t new travel -> r");
					printf("\t edit travel -> R");
					printf("\t travel history -> H");
					printf("\t travel list of passengers -> G");
				}
				printf("\t logout -> o");
			}
			printf("\t exit -> e");
			printf("\n");
		}
		boo = 0;
		char c;
		scanf("%c", &c);
		if (c == 'u') {
			signup('u');
		}else if (c == 'i') {
			signin();
		}else if (c == 't') {
			ticket();
		}else if (c == 'o') {
			user = "guest";
			char uu[6] = "guest";
			strcpy(cur.username, uu);
			cur.type = 'g';
			mainpage();
		}else if ((c == 'f')&&(user != "guest")) {
			edit_info(0);
		}else if (c == 'e') {
			exit(0);
		}else if (c == 'c' && cur.type == 'u') {
			cancleticket();
		}else if (c == 'h' && cur.type == 'u') {
			tickethist();
		}else if (c == 'r' && (cur.type == 'p' || cur.type == 'b' || cur.type == 't')) {
			newtravel(cur.username, cur.type);
		}else if (c == 'R' && (cur.type == 'p' || cur.type == 'b' || cur.type == 't')) {
			printf("Enter travel id : ");
			int tid = 0;
			scanf("%d", &tid);
			FILE *taid = fopen("files/travels.dat", "r");
			int tid2, tmp;
			char driver[16], temp[16];
			for (int i = 1000; i <= tid; i++) {
				fscanf(taid, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%s\t%s", &tid2, &tmp, &tmp, &tmp, &tmp, &driver, &tmp, &tmp, &temp, &temp);
			}
			fclose(taid);
			if (tid == tid2 && strcmp(cur.username, driver) == 0) {
				edit_trip(tid);
			}else {
				printf("Not found!\n");
				mainpage();
			}
		}else if (c == 'H' && (cur.type == 'p' || cur.type == 'b' || cur.type == 't')) {
			travellist();
		}
		else if (c == 'G' && (cur.type == 'p' || cur.type == 'b' || cur.type == 't')) {
			int id = 0;
			printf("Enter travel id : ");
			scanf("%d", &id);
			travel_passengers(id);
		}
		else if (c == 'a' && cur.type == 'a') {
			allusers();
		}
		else if (c == 'A' && cur.type == 'a') {
			alltravels();
		}
		else if (c == 'd' && cur.type == 'a') {
			char ty = 'u';
			while(ty != 'p' && ty != 't' && ty != 'b'){
				printf("Enter Driver Type (p : airplane) (t : train) (b : bus) : ");
				scanf("%c", &ty);
				scanf("%c", &ty);
			}
			signup(ty);
		}
		else if (c == 'D' && cur.type == 'a') {
			//edit driver
			bool b = true;
			person newp;
			while (b) {
				printf("Driver UserName : ");
				scanf("%s", &newp.username);
				char current[16] = "";
				char last[16] = "";
				int stat = 0;
				FILE *fp = fopen("files/users.dat", "r");
				fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &current, &newp.password, &newp.account, &newp.fullname, &newp.phone, &newp.type);
				while (strcmp(current, last) != 0) {
					if (strcmp(current, newp.username) == 0) {
						stat = 1;
						break;
					}
					strcpy(last, current);
					fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &current, &newp.password, &newp.account, &newp.fullname, &newp.phone, &newp.type);
				}
				fclose(fp);
				if (stat == 0) {
					printf("User not found!\n");
				}
				else if (stat == 1) {
					if (newp.type == 'u') {
						printf("You can't edit users!\n");
					}else {
						strcpy(newp.username, current);
						cur = newp;
						b = false;
					}
				}
			}
			edit_info(1);
		}
		else if (c == 'E' && cur.type == 'a') {
			printf("Enter travel id : ");
			int tid = 0;
			scanf("%d", &tid);
			FILE *taid = fopen("files/travels.dat", "r");
			int tid2, tmp;
			char driver[16], temp[16];
			for (int i = 1000; i <= tid; i++) {
				fscanf(taid, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%s\t%s", &tid2, &tmp, &tmp, &tmp, &tmp, &driver, &tmp, &tmp, &temp, &temp);
			}
			fclose(taid);
			if (tid == tid2) {
				edit_trip(tid);
			}
			else {
				printf("Not found!\n");
				mainpage();
			}
		}
		else if (c == 'p' && cur.type == 'a') {
			editvehicles();
		}else {
			if (int(c) != 10) {
				printf("%c is an unknown command!\n", c);
				boo = 1;
			}
			else {
				boo = 2;
			}
		}
	}
}

int cfileexists(const char* filename) {
	struct stat buffer;
	int exist = stat(filename, &buffer);
	if (exist == 0)
		return 1;
	else
		return 0;
}

void checkfiles() {
	//users.dat -> username password account fullname phone type
	if (!cfileexists("files/users.dat")) {
		FILE *fp = fopen("files/users.dat", "w");
		FILE *fpa = fopen("files/accounts.txt", "r");
		long int account = 0;
		fscanf(fpa, "%d", &account);
		char adpass[6] = "admin";
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\ta\n", "admin", adpass, account, "systemadmin", "09140461271");
		fclose(fpa);
		fclose(fp);
	}
	if (!cfileexists("files/vehicle.dat")) {
		//bus -> p v c
		//train -> p v c
		//plane -> p v c
		FILE *v = fopen("files/vehicle.dat", "w");
		fprintf(v, "50\t100\t50\n");
		fprintf(v, "70\t200\t200\n");
		fprintf(v, "100\t300\t100");
		fclose(v);
	}
	if (!cfileexists("files/travels.dat")) {
		FILE *tr = fopen("files/travels.dat", "w");
		fclose(tr);
	}
	if (!cfileexists("files/records.dat")) {
		FILE *tr = fopen("files/records.dat", "w");
		fclose(tr);
	}
}

void signup(char types) {
	person curr = cur;
	system("cls");
	system("Color 1B");
	bool boo = true;
	while (boo) {
		printf("UserName : ");
		scanf("%s", &cur.username);
		char current[16] = "";
		char last[16] = "";
		char temp[32] = "";
		int exist = 0;
		FILE *fp = fopen("files/users.dat", "r");
		fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s", &current, &temp, &temp, &temp, &temp, &temp);
		while (strcmp(current, last) != 0) {
			if (strcmp(current, cur.username) == 0) {
				exist = 1;
				break;
			}
			strcpy(last, current);
			fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s", &current, &temp, &temp, &temp, &temp, &temp);
		}
		fclose(fp);
		if (exist || strcmp(cur.username, "guest") == 0)printf("Username already exists!\n");
		else boo = false;
	}
	printf("PassWord : ");
	scanf("%s", &cur.password);
	bool b = true;
	while (b) {
		printf("Account Number : ");
		scanf("%d", &cur.account);
		int passw = 0;
		printf("Account Password : ");
		scanf("%d", &passw);
		FILE *fp = fopen("files/accounts.txt", "r");
		int status = 0;
		for (int i = 0; i < 100000; i++) {
			long int numb; int pa, mo;
			fscanf(fp, "%d\t%d\t%d", &numb, &pa, &mo);
			if (numb == cur.account) {
				if (pa == passw) {
					b = false;
					status = 1;
					break;
				}
				else {
					status = 2;
					break;
				}
			}
		}
		fclose(fp);
		if (status == 0) {
			printf("Account not found!\n");
		}
		else if (status == 2) {
			printf("Wrong Password!\n");
		}
	}
	printf("Full Name : (no spaces)");
	scanf("%s", &cur.fullname);
	printf("Phone Number : ");
	scanf("%s", &cur.phone);
	FILE *fpp = fopen("files/users.dat", "a");
	if (fpp != NULL) {
		fprintf(fpp, "%s\t%s\t%d\t%s\t%s\t%c\n", cur.username, cur.password, cur.account, cur.fullname, cur.phone, types);
		cur.type = 'u';
		fclose(fpp);
		system("cls");
		if (types != 'u') {
			cur = curr;
			printf("Driver added Successfully\n");
		}else {
			user = cur.username;
			printf("SignedUp Successfully\n");
		}
		mainpage();
	}else {
		cout << "NULL";
	}
}

void signin() {
	system("cls");
	system("Color 1B");
	bool b = true;
	person newp;
	while(b){
		printf("UserName : ");
		scanf("%s", &newp.username);
		printf("PassWord : ");
		scanf("%s", &newp.password);
		char current[16] = "";
		char last[16] = "";
		char passw[32] = "";
		int stat = 0;
		FILE *fp = fopen("files/users.dat", "r");
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &current, &passw, &newp.account, &newp.fullname, &newp.phone, &newp.type);
		while (strcmp(current, last) != 0) {
			if (strcmp(current, newp.username) == 0) {
				if (strcmp(newp.password, passw) == 0)stat = 1;
				else stat = 2;
				break;
			}
			strcpy(last, current);
			fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &current, &passw, &newp.account, &newp.fullname, &newp.phone, &newp.type);
		}
		fclose(fp);
		if (stat == 0) {
			printf("User not found!\n");
		}else if (stat == 1) {
			user = newp.username;
			cur = newp;
			//TODO -> type check
			b = false;
		}else if (stat == 2) {
			printf("Wrong password!\n");
		}
	}
	system("cls");
	mainpage();
}

void edit_info(int n) {
	person ad;
	system("cls");
	system("Color 1B");
	person newp = cur;
	printf("Enter new password(enter 0 to not change) : ");
	scanf("%s", &newp.password);
	char a[2] = "0";
	if (!strcmp(newp.password, a)) {
		strcpy(newp.password, cur.password);
	}
	bool b = true;
	while (b) {
		printf("Enter new account number(enter 0 to not change) : ");
		scanf("%d", &newp.account);
		if (!newp.account) {
			newp.account = cur.account;
			b = false;
			break;
		}
		int passw = 0;
		printf("Account Password : ");
		scanf("%d", &passw);
		FILE *fp = fopen("files/accounts.txt", "r");
		int status = 0;
		for (int i = 0; i < 100000; i++) {
			long int numb; int pa, mo;
			fscanf(fp, "%d\t%d\t%d", &numb, &pa, &mo);
			if (numb == newp.account) {
				if (pa == passw) {
					b = false;
					status = 1;
					break;
				}
				else {
					status = 2;
					break;
				}
			}
		}
		fclose(fp);
		if (status == 0) {
			printf("Account not found!\n");
		}
		else if (status == 2) {
			printf("Wrong Password!\n");
		}
	}
	printf("Enter new fullname(enter 0 to not change) : ");
	scanf("%s", &newp.fullname);
	if (!strcmp(newp.fullname, a))strcpy(newp.fullname, cur.fullname);
	printf("Enter new phone(enter 0 to not change) : ");
	scanf("%s", &newp.phone);
	if (!strcmp(newp.phone, a))strcpy(newp.phone, cur.phone);
	cur = newp;
	FILE *fp = fopen("files/users.dat", "r");
	char last[16] = "";
	fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &newp.username, &newp.password, &newp.account, &newp.fullname, &newp.phone, &newp.type);
	ad = newp;
	FILE *fpp = fopen("files/tmp.dat", "w");
	while (strcmp(newp.username, last) != 0) {
		if (!strcmp(newp.username, cur.username)) {
			fprintf(fpp, "%s\t%s\t%d\t%s\t%s\t%c\n", cur.username, cur.password, cur.account, cur.fullname, cur.phone, cur.type);
		}
		else {
			fprintf(fpp, "%s\t%s\t%d\t%s\t%s\t%c\n", newp.username, newp.password, newp.account, newp.fullname, newp.phone, newp.type);
		}
		strcpy(last, newp.username);
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &newp.username, &newp.password, &newp.account, &newp.fullname, &newp.phone, &newp.type);
	}
	fclose(fp);
	fclose(fpp);
	remove("files/users.dat");
	rename("files/tmp.dat", "files/users.dat");
	system("cls");
	printf("Done!\n");
	if (n) {
		cur = ad;
		user = cur.username;
	}
	mainpage();
}

void allusers() {
	system("cls");
	system("color 2E");
	FILE *fp = fopen("files/users.dat", "r");
	person newp;
	fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &newp.username, &newp.password, &newp.account, &newp.fullname, &newp.phone, &newp.type);
	char last[16] = "";
	while (strcmp(newp.username, last) != 0) {
		//print
		printf("%s(%s) | account : %d | phone : %s | type : %c \n\n", newp.fullname, newp.username, newp.account, newp.phone, newp.type);
		strcpy(last, newp.username);
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%c", &newp.username, &newp.password, &newp.account, &newp.fullname, &newp.phone, &newp.type);
	}
	fclose(fp);
	char c;
	printf("Press enter to go back ...");
	scanf("%c", &c);
	scanf("%c", &c);
	system("cls");
	mainpage();
}

void editvehicles() {
	system("cls");
	system("color 2E");
	int a = -1;
	while(a < 0){
		printf("Which one of the vehicles you want to edit ? (b : bus) (t : train) (p : plain)  ");
		char c;
		scanf("%c", &c);
		scanf("%c", &c);
		if (c == 'b') {
			a = 0;
		}else if (c == 't') {
			a = 1;
		}else if (c == 'p') {
			a = 2;
		}else {
			printf("Unknown vehicle!\n");
		}
	}
	FILE *fp = fopen("files/vehicle.dat","r");
	FILE *fpp = fopen("files/vtemp.dat", "w");
	int p, v, c;
	for (int i = 0; i < 3; i++) {
		if (i == a) {
			fscanf(fp, "%d\t%d\t%d", &p, &v, &c);
			int p2, v2, c2;
			printf("Enter new price (current is %d , enter 0 for not change) ", p);
			scanf("%d", &p2);
			if (p2 > 0)p = p2;
			printf("Enter new speed (current is %d , enter 0 for not change) ", v);
			scanf("%d", &v2);
			if (v2 > 0)v = v2;
			printf("Enter new capacity (current is %d , enter 0 for not change) ", c);
			scanf("%d", &c2);
			if (c2 > 0 && c2 <= 400)c = c2;
			fprintf(fpp, "%d\t%d\t%d\t\n", p, v, c);
		}else {
			fscanf(fp, "%d\t%d\t%d", &p, &v, &c);
			fprintf(fpp, "%d\t%d\t%d\n", p, v, c);
		}
	}
	fclose(fp);
	fclose(fpp);
	remove("files/vehicle.dat");
	rename("files/vtemp.dat", "files/vehicle.dat");
	system("cls");
	printf("Done!");
	mainpage();
}

int round_price(int p) {
	int r = p % 100;
	int q = p / 100;
	if (r >= 50)
		q = (q + 1) * 100;
	else
		q = q * 100;
	return q;
}

float time_duration(float distance, int velocity) {
	float time = distance / velocity;
	int s = int(time);
	float d = time - s;
	d = d * 60;
	if (d >= 0 && d <= 15)
		d = 0;
	else if (d > 15 && d < 45)
		d = 30;
	else {
		d = 0;
		s++;
	}
	return float(s) + d / 60;
}

void newtravel(char driver[16], char type) {
	system("cls");
	system("color 2E");
	int travelid = 1000;
	FILE *fp = fopen("files/travels.dat", "r");
	char tmp[32]; int temp = 0; int id; int lastid = -1; char cc; char dat[16];
	fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s",&id, &temp, &temp, &temp, &temp, &tmp, &temp, &temp, &cc, &dat);
	if (temp > 0) {
		while (lastid != id) {
			travelid++;
			lastid = id;
			fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &id, &temp, &temp, &temp, &temp, &tmp, &temp, &temp, &cc, &dat);
		}
	}
	//travelid = lastid + 1;
	fclose(fp);
	int start = 0, dest = 0;
	printf("Enter start city number : ");
	scanf("%d", &start);
	dest = start;
	while (start == dest) {
		printf("Enter destination city number(different from start) : ");
		scanf("%d", &dest);
	}
	int year = 0, month = 0, day = 0;
	int cyear, cmonth, cday;
	time_t now = time(NULL);
	struct tim *ltm = (tim*)localtime(&now);
	cyear = 1900 + ltm->tm_year;
	cmonth = 1 + ltm->tm_mon;
	cday = ltm->tm_mday;
	bool today = false;
	while (year < cyear) {
		printf("Enter Year (current year is %d): ", cyear);
		scanf("%d", &year);
	}
	while (month > 12 || month < 1) {
		printf("Enter Month (current month is %d): ", cmonth);
		scanf("%d", &month);
	}
	while (day > 31 || day < 1) {
		printf("Enter Day (current day is %d): ", cday);
		scanf("%d", &day);
	}
	if (cyear == year) {
		if (cmonth == month) {
			if (cday == day) {
				today = true;
			}
			else if (cday > day) {
				printf("Wrong date!");
				return;
			}
		}
		else if (cmonth > month) {
			printf("Wrong date!");
			return;
		}
	}
	int h = -1;
	while (h > 23 || h < 0) {
		printf("Enter travel hour (0 - 23) : ");
		scanf("%d", &h);
	}
	int m = -1;
	while (m > 59 || m < 0) {
		printf("Enter travel minute (0 - 59) : ");
		scanf("%d", &m);
	}
	if (today) {
		if (ltm->tm_hour > h) {
			printf("Wrong date!");
			return;
		}
		else if (ltm->tm_hour == h && ltm->tm_min > m) {
			printf("Wrong date!");
			return;
		}
	}
	int k = 0;
	if (type == 'b')k = 0;
	else if (type == 't')k = 1;
	else if (type == 'p')k = 2;
	else return;
	FILE *tr = fopen("files/vehicle.dat", "r");
	int p = 0, v = 0, c = 0;
	for (int j = 0; j <= k; j++) {
		fscanf(tr, "%d\t%d\t%d", &p, &v, &c);
	}
	fclose(tr);
	int x1, x2, y1, y2;
	bool one = true, two = true;
	FILE *city = fopen("files/cities.txt", "r");
	int cnum, cx, cy;
	while (one || two) {
		fscanf(city, "%d\t%d\t%d", &cnum, &cx, &cy);
		if (cnum == start) {
			x1 = cx;
			y1 = cy;
			one = false;
		}else if (cnum == dest) {
			x2 = cx;
			y2 = cy;
			two = false;
		}
		if (cnum == 300 && (one || two)) {
			printf("city not found!");
			fclose(city);
			return;
		}
	}
	fclose(city);
	float dist = float(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2) * (y1 - y2)));
	int pr = int(dist * p);
	int price = round_price(pr);
	float long2 = time_duration(dist, v);
	int long1 = int(60 * long2);
	FILE *trav = fopen("files/travels.dat", "a");
	fprintf(trav, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d\n", travelid, start, dest, h * 60 + m, c, driver, price, long1, type, year, month, day);
	fclose(trav);
	system("cls");
	printf("Travel Added!\n");
	mainpage();
}

void alltravels() {
	system("cls");
	system("color 2E");
	FILE *fp = fopen("files/travels.dat", "r");
	int travelid = 0, start, dest, saat, cap, price, long1; char type;
	char driver[16], tar[16];
	fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &travelid, &start, &dest, &saat, &cap, &driver, &price, &long1, &type, &tar);
	int h = 0, m = 0;
	int lastid = 0;
	while (lastid != travelid) {
		h = saat / 60;
		m = saat % 60;
		if(type != 'c')printf("Travel number %d | From city%d to city%d with %s as driver and type %c \n Travel price is %d tooman and travel is in %s %d:%d \n\n", travelid, start, dest, driver, type, price, tar, h, m);
		lastid = travelid;
		fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &travelid, &start, &dest, &saat, &cap, &driver, &price, &long1, &type, &tar);
	}
	fclose(fp);
	char c;
	printf("Press enter to go back ...");
	scanf("%c", &c);
	scanf("%c", &c);
	system("cls");
	mainpage();
}

void travellist() {
	system("cls");
	system("color 2E");
	FILE *fp = fopen("files/travels.dat", "r");
	int travelid = 0, start, dest, saat, cap, price, long1; char type;
	char driver[16], tar[16];
	fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &travelid, &start, &dest, &saat, &cap, &driver, &price, &long1, &type, &tar);
	int h = 0, m = 0;
	int lastid = 0;
	while (lastid != travelid) {
		h = saat / 60;
		m = saat % 60;
		if(strcmp(driver, cur.username) == 0)printf("Travel number %d | From city%d to city%d with you as driver and capacity is : %d \n Travel price is %d tooman and travel is in %s %d:%d \n\n", travelid, start, dest, cap, price, tar, h, m);
		lastid = travelid;
		fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &travelid, &start, &dest, &saat, &cap, &driver, &price, &long1, &type, &tar);
	}
	fclose(fp);
	char c;
	printf("Press enter to go back ...");
	scanf("%c", &c);
	scanf("%c", &c);
	system("cls");
	mainpage();
}

void travel_passengers(int id) {
	system("cls");
	system("color 2E");
	FILE *fp = fopen("files/travels.dat", "r");
	int travelid = 0, start, dest, saat, cap, price, long1; char type;
	char driver[16], tar[16];
	fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &travelid, &start, &dest, &saat, &cap, &driver, &price, &long1, &type, &tar);
	int h = 0, m = 0;
	int lastid = 0;
	while (lastid != travelid) {
		h = saat / 60;
		m = saat % 60;
		if (strcmp(driver, cur.username) == 0 && travelid == id) {
			break;
		}
		lastid = travelid;
		fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &travelid, &start, &dest, &saat, &cap, &driver, &price, &long1, &type, &tar);
	}
	fclose(fp);
	if (travelid != id) {
		printf("Nothing found ! \n");
		mainpage();
		return;
	}
	
	//

	FILE *oo = fopen("files/records.dat", "r");
	char un1[16], fullname1[32];
	int travid1, seat1, peyg1, acco1;
	fscanf(oo, "%s\t%s\t%d\t%d\t%d\t%d", &un1, &fullname1, &travid1, &seat1, &peyg1, &acco1);
	int lastpe1 = 0;
	while (lastpe1 != peyg1) {
		if (travid1 == id) {
			printf("%s(%s) in seat %d and code %d\n", fullname1, un1, seat1, peyg1);
		}
		lastpe1 = peyg1;
		fscanf(oo, "%s\t%s\t%d\t%d\t%d\t%d", &un1, &fullname1, &travid1, &seat1, &peyg1, &acco1);
	}
	fclose(oo);
	//

	char c;
	printf("Press enter to go back ...");
	scanf("%c", &c);
	scanf("%c", &c);
	system("cls");
	mainpage();
}

int rahghiri(int n, int b) {
	int c = 0, m = 0; int bb = b; int nn = n, rah = 0, v = 0;
	for (int i = 0; i < 6; i++) {
		if ((nn % 10) % 2 == 0 && (nn % 10) % 3 == 0) {
			v += nn % 10; nn /= 10;
		}
		m += bb % 10; bb /= 10; if (m % 2 == 0) {
			c += m;
		} if (m > 9) m /= 10; if (c > 9) c /= 10;

	} rah += m; rah *= 10; rah += c; rah *= 10; m = 0; c = 0; bb = b; rah += v; rah *= 10; v = 0;

	for (int i = 1; i < 7; i++) {
		v += n % 10; n /= 10;
		if (i % 2 == 0) {
			m += bb % 10; bb /= 10;
		}
		else {
			c += bb % 10; bb /= 10;
		}
	}
	rah += m; rah *= 10; rah += c; rah *= 10; m = 0; c = 0; bb = b; rah += v;
	return rah;
}

void ticket() {
	bool guest;
	if (cur.type == 'u') {
		guest = false;
	}else if (cur.type == 'g') {
		guest = true;
	}else {
		printf("You can't buy a ticket!");
		mainpage();
	}
	system("cls");
	system("color 2E");
	char type;
	int start = 0, dest = 0;
	int year, month, day;
	printf("Enter type of travel you want : (p : plain) (t : train) (b : bus) ");
	scanf("%c", &type);
	scanf("%c", &type);
	while (type != 'p' && type != 't' && type != 'b') {
		printf("Enter type of travel you want : (p : plain) (t : train) (b : bus) ");
		scanf("%c", &type);
		scanf("%c", &type);
	}
	printf("Enter start city number : ");
	scanf("%d", &start);
	printf("Enter destination city number : ");
	scanf("%d", &dest);
	printf("Enter date (yy/mm/dd) : ");
	scanf("%d/%d/%d", &year, &month, &day);
	FILE *fp = fopen("files/travels.dat", "r");
	int travelid = 0, startt, destt, saat, cap = 0, price, long1; char typet;
	int year1, month1, day1;
	char driver[16];
	fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d", &travelid, &startt, &destt, &saat, &cap, &driver, &price, &long1, &typet, &year1, &month1, &day1);
	int h = 0, m = 0;
	int lastidd = 0;
	int recordds = 0;
	while (lastidd != travelid) {
		h = saat / 60;
		m = saat % 60;
		if (start == startt && dest == destt && year == year1 && month == month1 && day == day1 && typet == type) {
			int hh = long1 / 60;
			int mm = long1 % 60;
			printf("travel number %d | time %d : %d | %d tooman | duration  %d : %d | driver : %s\n\n", travelid, h, m, price, hh, mm, driver);
			recordds++;
		}
		lastidd = travelid;
		fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d", &travelid, &startt, &destt, &saat, &cap, &driver, &price, &long1, &typet, &year1, &month1, &day1);
	}
	fclose(fp);
	if (recordds == 0) {
		printf("No record found!\n\n");
		mainpage();
	}
	printf("Enter travel id for buy ticket : (enter 0 to cancle) ");
	int travid = 0;
	scanf("%d", &travid);
	if (travid == 0) {
		mainpage();
		return;
	}
	bool found = false;
	FILE * fpp = fopen("files/travels.dat", "r");
	fscanf(fpp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d", &travelid, &startt, &destt, &saat, &cap, &driver, &price, &long1, &typet, &year1, &month1, &day1);
	int lastid = 0;
	int records = 0;
	while (lastid != travelid) {
		h = saat / 60;
		m = saat % 60;
		if (travid == travelid) {
			found = true;
			break;
		}
		lastid = travelid;
		fscanf(fpp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d", &travelid, &startt, &destt, &saat, &cap, &driver, &price, &long1, &typet, &year1, &month1, &day1);
	}
	fclose(fpp);
	if (!found) {
		printf("Not found!\n");
		mainpage();
		return;
	}
	//
	int cyear, cmonth, cday;
	time_t now = time(NULL);
	struct tim *ltm = (tim*)localtime(&now);
	cyear = 1900 + ltm->tm_year;
	cmonth = 1 + ltm->tm_mon;
	cday = ltm->tm_mday;
	bool today = false;
	if (cyear == year) {
		if (cmonth == month) {
			if (cday == day) {
				today = true;
			}
			else if (cday > day) {
				printf("Past date!");
				mainpage();
				return;
			}
		}
		else if (cmonth > month) {
			printf("Past date!");
			mainpage();
			return;
		}
	}
	if (today) {
		if (ltm->tm_hour > h) {
			printf("Past date!");
			mainpage();
			return;
		}
		else if (ltm->tm_hour == h && ltm->tm_min > m) {
			printf("Wrong date!");
			mainpage();
			return;
		}
	}
	//saat
	int arr[401];
	arr[0] = 0;
	for (int i = 1; i <= cap; i++) {
		arr[i] = 1;
	}
	char uname[16], funame[32];int useat, upey, uac, tid;
	FILE *rec = fopen("files/records.dat", "r");
	int lastpey = 0;
	fscanf(rec, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &funame, &tid, &useat, &upey, &uac);
	while (lastpey != upey) {
		if (travid == tid) {
			arr[useat] = 0;
		}
		lastpey = upey;
		fscanf(rec, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &funame, &tid, &useat, &upey, &uac);
	}
	fclose(rec);
	printf("\n");
	for (int i = 1; i <= cap; i++) {
		if (arr[i] == 0) {
			printf("X ");
		}
		else {
			printf("O ");
		}
		if (i % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	int seat = 0;
	while (true) {
		printf("Enter your seat number:(Enter 0 to cancle) ");
		scanf("%d", &seat);
		if (arr[seat] == 1 || seat == 0) {
			break;
		}
	}
	if (seat == 0 || seat > cap) {
		printf("wrong seat!\n");
		mainpage();
		return;
	}
	person newp;
	strcpy(newp.username, "guest");
	if (guest) {
		printf("Enter your fullname : (Enter CAN to cancle)");
		scanf("%s", &newp.fullname);
		if (strcmp(newp.fullname, "CAN") == 0) {
			mainpage();
			return;
		}
		bool b = true;
		while (b) {
			printf("Account Number : ");
			scanf("%d", &newp.account);
			int passw = 0;
			printf("Account Password : ");
			scanf("%d", &passw);
			FILE *fp = fopen("files/accounts.txt", "r");
			int status = 0;
			for (int i = 0; i < 100000; i++) {
				long int numb; int pa, mo;
				fscanf(fp, "%d\t%d\t%d", &numb, &pa, &mo);
				if (numb == newp.account) {
					if (pa == passw) {
						b = false;
						status = 1;
						break;
					}
					else {
						status = 2;
						break;
					}
				}
			}
			fclose(fp);
			if (status == 0) {
				printf("Account not found!\n");
			}
			else if (status == 2) {
				printf("Wrong Password!\n");
			}
		}
	}else {
		newp = cur;
	}
	//
	printf("Please wait...\n");
	FILE *fpa = fopen("files/accounts.txt", "r");
	FILE *ff = fopen("files/actmp", "w");
	int status = 0;
	for (int i = 0; i < 100000; i++) {
		long int numb; int pa, mo;
		fscanf(fpa, "%d\t%d\t%d", &numb, &pa, &mo);
		if (numb == newp.account) {
			if (mo >= price) {
				status = 1;
				mo -= price;
			}else {
				status = -1;
			}
			fprintf(ff, "%d\t%d\t%d\n", numb, pa, mo);
		}
		else {
			fprintf(ff, "%d\t%d\t%d\n", numb, pa, mo);
		}
	}
	fclose(fpa);
	fclose(ff);
	remove("files/accounts.txt");
	rename("files/actmp", "files/accounts.txt");
	if (status < 0) {
		printf("You don't have enough money !\n");
		mainpage();
		return;
	}
	int drivercc = 0, admincc = 0;
	char cur0[16], last0[16] = ""; int cc;
	int tmp; char tmpc; char tmpcc[32];
	FILE *pay = fopen("files/users.dat", "r");
	fscanf(pay, "%s\t%d\t%d\t%s\t%d\t%c", &cur0, &tmp, &cc, &tmpcc, &tmp, &tmpc);
	int ccc = 0;
	while (strcmp(last0, cur0) != 0 && ccc < 2) {
		if (strcmp(cur0, "admin") == 0) {
			admincc = cc;
			ccc++;
		}
		else if (strcmp(cur0, driver) == 0) {
			drivercc = cc;
			ccc++;
		}
		strcpy(last0, cur0);
		fscanf(pay, "%s\t%d\t%d\t%s\t%d\t%c", &cur0, &tmp, &cc, &tmpcc, &tmp, &tmpc);
	}
	fclose(pay);
	FILE *fpa2 = fopen("files/accounts.txt", "r");
	FILE *ff2 = fopen("files/actmp", "w");
	for (int i = 0; i < 100000; i++) {
		long int numb; int pa, mo;
		fscanf(fpa2, "%d\t%d\t%d", &numb, &pa, &mo);
		if (numb == admincc) {
			float f = float(0.1 * price);
			mo += int(f);
		}
		else if (numb == drivercc) {
			float f = float(0.9 * price);
			mo += int(f);
		}
		fprintf(ff2, "%d\t%d\t%d\n", numb, pa, mo);
	}
	fclose(fpa2);
	fclose(ff2);
	remove("files/accounts.txt");
	rename("files/actmp", "files/accounts.txt");
	/////
	//
	int rahg;
	rahg = rahghiri(ltm->tm_hour * 60 + ltm->tm_min, travelid + int(newp.fullname[2]) + newp.account % 10);
	FILE *newrec = fopen("files/records.dat", "a");
	fprintf(newrec, "%s\t%s\t%d\t%d\t%d\t%d\n", newp.username, newp.fullname, travid, seat, rahg, newp.account);
	printf("Ticket bought successfully!\n");
	printf("Code : %d\n", rahg);
	fclose(newrec);
	char c;
	printf("Press enter to go back ...");
	scanf("%c", &c);
	scanf("%c", &c);
	system("cls");
	mainpage();
}

void tickethist() {
	system("cls");
	int ted = 0;
	char uname[16], funame[32]; int useat, upey, uac, tid;
	FILE *rec = fopen("files/records.dat", "r");
	int lastpey = 0;
	fscanf(rec, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &funame, &tid, &useat, &upey, &uac);
	while (lastpey != upey) {
		if (strcmp(uname, cur.username) == 0) {
			//fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &id, &temp, &temp, &temp, &temp, &tmp, &temp, &temp, &cc, &dat);
			FILE *trav = fopen("files/travels.dat", "r");
			int temp; char tmp[16];
			int start, dest, time;
			char date[12]; char cc;
			for (int i = 1000; i <= tid; i++) {
				fscanf(trav, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%s", &temp, &start, &dest, &time, &temp, &tmp, &temp, &temp, &cc, &date);
			}
			fclose(trav);
			int h = 0, m = 0;
			h = time / 60;
			m = time % 60;
			printf("Travel number %d from city%d to city%d at %d : %d in %s | Code : %d\n\n", tid, start, dest, h, m, date, upey);
			ted++;
		}
		lastpey = upey;
		fscanf(rec, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &funame, &tid, &useat, &upey, &uac);
	}
	fclose(rec);
	if (ted == 0)printf("Nothing found !\n");
	char c;
	printf("Press enter to go back ...");
	scanf("%c", &c);
	scanf("%c", &c);
	system("cls");
	mainpage();
}

void cancleticket() {
	printf("Enter ticket code : ");
	int code = 0;
	scanf("%d", &code);
	FILE *fp = fopen("files/records.dat", "r");
	char uname[16], fullname[32];
	int travid, seat, peyg = 0, account;
	fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &fullname, &travid, &seat, &peyg, &account);
	int lastpey = 0;
	int stat = 0;
	while (lastpey != peyg) {
		if (peyg == code) {
			if (strcmp(cur.username, uname) == 0) {
				stat = 1;
				break;
			}
			else {
				stat = -1;
				break;
			}
		}
		lastpey = peyg;
		fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &fullname, &travid, &seat, &peyg, &account);
	}
	fclose(fp);
	if (stat <= 0) {
		printf("Not found!\n");
		mainpage();
		return;
	}
	printf("Please wait...\n");
	FILE *fp2 = fopen("files/travels.dat", "r");
	char driver[16]; int price = 0;
	int tmp; char cy;
	int timee; int year, month, day;
	for (int i = 1000; i <= travid; i++) {
		fscanf(fp2, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d", &tmp, &tmp, &tmp, &timee, &tmp, &driver, &price, &tmp, &cy, &year, &month, &day);
	}
	fclose(fp2);
	int h = timee / 60;
	int m = timee % 60;
	int cyear, cmonth, cday;
	time_t now = time(NULL);
	struct tim *ltm = (tim*)localtime(&now);
	cyear = 1900 + ltm->tm_year;
	cmonth = 1 + ltm->tm_mon;
	cday = ltm->tm_mday;
	bool today = false;
	if (cyear == year) {
		if (cmonth == month) {
			if (cday == day) {
				today = true;
			}
			else if (cday > day) {
				printf("Past date!");
				mainpage();
				return;
			}
		}
		else if (cmonth > month) {
			printf("Past date!");
			mainpage();
			return;
		}
	}
	if (today) {
		if (ltm->tm_hour > h) {
			printf("Past date!");
			mainpage();
			return;
		}
		else if (ltm->tm_hour == h && ltm->tm_min > m) {
			printf("Wrong date!");
			mainpage();
			return;
		}
		int curtimee = ltm->tm_hour * 60 + ltm->tm_min;
		int diff = timee - curtimee;
		if (diff >= 60) {
			price *= 0.9;
		}else{
			price /= 2;
		}
	}
	else {
		price *= 0.9;
	}
	int drivercc = 0, admincc = 0;
	char cur0[16], last0[16] = ""; int cc;
	char tmpc; char tmpcc[32];
	FILE *pay = fopen("files/users.dat", "r");
	fscanf(pay, "%s\t%d\t%d\t%s\t%d\t%c", &cur0, &tmp, &cc, &tmpcc, &tmp, &tmpc);
	int ccc = 0;
	while (strcmp(last0, cur0) != 0 && ccc < 2) {
		if (strcmp(cur0, "admin") == 0) {
			admincc = cc;
			ccc++;
		}
		else if (strcmp(cur0, driver) == 0) {
			drivercc = cc;
			ccc++;
		}
		strcpy(last0, cur0);
		fscanf(pay, "%s\t%d\t%d\t%s\t%d\t%c", &cur0, &tmp, &cc, &tmpcc, &tmp, &tmpc);
	}
	fclose(pay);
	FILE *fpa2 = fopen("files/accounts.txt", "r");
	FILE *ff2 = fopen("files/actmp", "w");
	for (int i = 0; i < 100000; i++) {
		long int numb; int pa, mo;
		fscanf(fpa2, "%d\t%d\t%d", &numb, &pa, &mo);
		if (numb == admincc) {
			float f = float(0.1 * price);
			mo -= int(f);
		}
		else if (numb == drivercc) {
			float f = float(0.9 * price);
			mo -= int(f);
		}
		else if (numb == account) {
			mo += price;
		}
		fprintf(ff2, "%d\t%d\t%d\n", numb, pa, mo);
	}
	fclose(fpa2);
	fclose(ff2);
	remove("files/accounts.txt");
	rename("files/actmp", "files/accounts.txt");
	FILE *oo = fopen("files/records.dat", "r");
	FILE *oo2 = fopen("files/rect", "w");
	char un1[16], fullname1[32];
	int travid1, seat1, peyg1, acco1;
	fscanf(oo, "%s\t%s\t%d\t%d\t%d\t%d", &un1, &fullname1, &travid1, &seat1, &peyg1, &acco1);
	int lastpe1 = 0;
	while (lastpe1 != peyg1) {
		if (peyg1 != code) {
			fprintf(oo2, "%s\t%s\t%d\t%d\t%d\t%d\n", un1, fullname1, travid1, seat1, peyg1, acco1);
		}
		lastpe1 = peyg1;
		fscanf(oo, "%s\t%s\t%d\t%d\t%d\t%d", &un1, &fullname1, &travid1, &seat1, &peyg1, &acco1);
	}
	fclose(oo);
	fclose(oo2);
	remove("files/records.dat");
	rename("files/rect", "files/records.dat");
	printf("Cancled successfully !\n");
	mainpage();
}

void edit_trip(int id) {
	printf("What do you want to do ? (c : cancle , d : delay) ");
	char action;
	scanf("%c", &action);
	scanf("%c", &action);
	float zarib = 0;
	int ho = 0;
	if (action == 'c') {
		zarib = 1;
	}
	else if (action == 'd') {
		do {
			printf("Enter hours of delay : (1 to 19) ");
			scanf("%d", &ho);
		} while (ho > 19 || ho < 1);
		zarib = 0.05 * ho;
	}
	else {
		printf("Unknown action!\n");
		mainpage();
		return;
	}
	printf("Please wait...\n");
	//edit travels file
	FILE *tv = fopen("files/travels.dat", "r");
	FILE *tv2 = fopen("files/traveltmp", "w");
	int travid, start, dest, saat, cap; char driver[16]; int price, long1; char typ; int year, month, day;
	int tprice = 0; char cdriver[16];
	int lastid = 0;
	fscanf(tv, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d", &travid, &start, &dest, &saat, &cap, &driver, &price, &long1, &typ, &year, &month, &day);
	while (travid != lastid) {
		if (travid == id) {
			tprice = price;
			strcpy(cdriver, driver);
			if (action == 'd') {
				saat += (60 * ho);
				if (saat >= 1440) {
					saat -= 1440;
					day++;
					if (day > 31) {
						day -= 31;
						month++;
						if (month > 12) {
							month -= 12;
							year++;
						}
					}
				}
				fprintf(tv2, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d\n", travid, start, dest, saat, cap, driver, price, long1, typ, year, month, day);
			}
			else {
				fprintf(tv2, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d\n", travid, start, dest, saat, cap, "cancled", price, long1, 'c', year, month, day);
			}
		}
		else {
			fprintf(tv2, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d\n", travid, start, dest, saat, cap, driver, price, long1, typ, year, month, day);
		}
		lastid = travid;
		fscanf(tv, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%c\t%d/%d/%d", &travid, &start, &dest, &saat, &cap, &driver, &price, &long1, &typ, &year, &month, &day);
	}
	fclose(tv);
	fclose(tv2);
	remove("files/travels.dat");
	rename("files/traveltmp", "files/travels.dat");
	//edit record file
	int arac[400] = { -1 };
	FILE *re = fopen("files/records.dat", "r");
	FILE *re2 = fopen("files/retmp", "w");
	char uname[16], funame[32];
	int k = 0;
	int traveli, seat, peyg, accou;
	int lastp = 0;
	fscanf(re, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &funame, &traveli, &seat, &peyg, &accou);
	while (lastp != peyg) {
		if (traveli == id) {
			arac[k++] = accou;
			if (action == 'd') {
				fprintf(re2, "%s\t%s\t%d\t%d\t%d\t%d\n", uname, funame, traveli, seat, peyg, accou);
			}
		}
		else {
			fprintf(re2, "%s\t%s\t%d\t%d\t%d\t%d\n", uname, funame, traveli, seat, peyg, accou);
		}
		lastp = peyg;
		fscanf(re, "%s\t%s\t%d\t%d\t%d\t%d", &uname, &funame, &traveli, &seat, &peyg, &accou);
	}
	fclose(re);
	fclose(re2);
	remove("files/records.dat");
	rename("files/retmp", "files/records.dat");
	///
	int drivercc = 0, admincc = 0;
	char cur0[16], last0[16] = ""; int cc;
	int tmp; char tmpc; char tmpcc[32];
	FILE *pay = fopen("files/users.dat", "r");
	fscanf(pay, "%s\t%d\t%d\t%s\t%d\t%c", &cur0, &tmp, &cc, &tmpcc, &tmp, &tmpc);
	int ccc = 0;
	while (strcmp(last0, cur0) != 0 && ccc < 2) {
		if (strcmp(cur0, "admin") == 0) {
			admincc = cc;
			ccc++;
		}
		else if (strcmp(cur0, cdriver) == 0) {
			drivercc = cc;
			ccc++;
		}
		strcpy(last0, cur0);
		fscanf(pay, "%s\t%d\t%d\t%s\t%d\t%c", &cur0, &tmp, &cc, &tmpcc, &tmp, &tmpc);
	}
	fclose(pay);
	//driver account found
	int mablagh = int(tprice * zarib * k);
	FILE *fpa2 = fopen("files/accounts.txt", "r");
	FILE *ff2 = fopen("files/actmp", "w");
	for (int i = 0; i < 100000; i++) {
		long int numb; int pa, mo;
		fscanf(fpa2, "%d\t%d\t%d", &numb, &pa, &mo);
		if (numb == admincc) {
			float f = float(0.1 * mablagh);
			mo -= int(f);
		}
		else if (numb == drivercc) {
			float f = float(0.9 * mablagh);
			mo -= int(f);
		}
		else {
			for (int j = 0; j < k; j++) {
				if (numb == arac[j]) {
					arac[j] = 0;
					mo += (tprice * zarib);
					break;
				}
			}
		}
		fprintf(ff2, "%d\t%d\t%d\n", numb, pa, mo);
	}
	fclose(fpa2);
	fclose(ff2);
	remove("files/accounts.txt");
	rename("files/actmp", "files/accounts.txt");
	/////
	printf("Done!\n");
	mainpage();
}
