/* 2. Розробка програми для предметної області «Відомості про пам'ятки історії та архітектури».
*  Завдання. Розробити програму, що дозволяє збирати і накопичувати відомості про пам'ятки історії та архітектури,
*  що представляють історичну і державну цінність.Інформаційно - пошукова система повинна забезпечувати можливість
*  введення, редагування, видалення, пошуку, фільтрації даних, а так само виведення звітів за заданими критеріями(не менше 3 - х звітів).
*/

#include <conio.h>
#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

struct Remembrance {
	string Name;
	int TimeConstrVid;
	int TimeConstrDo;
	bool Ukraine;
	string Oblast;
	string Type;
	int Deleted;
	Remembrance() {
		Name = "---";
		TimeConstrVid = 0;
		TimeConstrDo = 0;
		Ukraine = 0;
		Oblast = "---";
		Type = "---";
	}
	void Print() {
		cout << "--------------------------------\n";
		cout << "Назва пам'ятки: " << Name << endl;

		cout << "Дата побудови: ";
		if (TimeConstrVid == 0) {
			cout << "Даних немає!" << endl;
		}
		else if (TimeConstrVid != 0 && TimeConstrDo == 0) {
			cout << TimeConstrVid << " рік.\n";
		}
		else if ((TimeConstrVid != 0) && (TimeConstrVid % 100 == 0) && (TimeConstrDo == 0) && (TimeConstrDo % 100 == 0)) {
			cout << TimeConstrDo / 100 << " століття\n";
		}
		else {
			cout << TimeConstrVid << " - " << TimeConstrDo << " роки\n";
		}

		cout << "Місце знаходження: ";
		if (!Ukraine && Oblast == "---") {
			cout << "Даних немає!\n";
		}
		else if (Ukraine && Oblast == "---") {
			cout << "Україна.\n";
		}
		else if (Ukraine && Oblast != "---") {
			cout << "Україна, " << Oblast << " область.\n";
		}
		else {
			cout << Oblast << ".\n"; //Іноземна держава
		}

		cout << "Тип пам'ятки: ";
		if (Type == "---") {
			cout << "Даних немає!\n";
		}
		else {
			cout << Type << ".\n"; //Іноземна держава
		}
		cout << "--------------------------------\n";

	}
} newrem, pnt, foredit;

void MainMenu();

void MenuNewData();
void MenuNewDataClear();
void MenuEditingClear();
void MenuNewDataName(int);
void MenuNewDataTime(int);
void MenuNewDataTime1(int);
void MenuNewDataTime2(int);
void MenuNewDataTime3(int);
void MenuNewDataPlace(int);
void MenuNewDataType(int);
bool MenuNewDataCheckingName(string temp);

void MenuFinding();
void MenuFindingName();
void MenuEditing();
void MenuFindingStart(int);
void MenuAfterStart(int);

void MenuNewDataTime();
void InFile();
void OutFile();
void Deleting(vector<vector<string>>&, int*);

bool AreYouSure(string str2) {
	string str;
	cout << str2;
	cin >> str;
	if (str == "Так" || str == "так" || str == "nfr" || str == "Nfr") {
		return true;
	}
	else if (str == "Ні" || str == "ні" || str == "Ys" || str == "ys") {
		return false;
	}
	else {
		system("cls");
		cout << "Помилка вводу, спробуйте знову\n";
		return AreYouSure(str);
	}

}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	cout << "Вас вітає програма для роботи з даними для предметної області «Відомості про пам'ятки історії та архітектури»!\n";
	Sleep(2000);
	cout << "(Натисніть любу клавішу щоб почати роботу)\n";
	_getch();
	system("cls");
	MainMenu();
	return 0;
}

void MainMenu() {

	int choise;
	string str, str2;
	cout << "1. Ввести дані\n";
	cout << "2. Пошук, видалення, редагування даних\n";
	cout << "3. Вийти з програми\n";
	cin >> str2;
	choise = str2[0];
	switch (choise) {
	case '1':
		system("cls");
		MenuNewData();
		break;
	case '2':
		system("cls");
		MenuFinding();
		break;
	case '3':
		str = "Ви впевнені що хочете вийти з програми?(Так/Ні)\n";
		if (AreYouSure(str)) {
			exit(0);
		}
		else {
			system("cls");
			MainMenu();
		}
		break;
	default:
		system("cls");
		cout << "Помилка вводу спробуйте знову!\n";
		MainMenu();
	}
	return;
}

void MenuNewData() {
	int neworedit;
	string str, str2;
	char choise;
	cout << "* Обов'язковий пункт\n";
	cout << "1. Назва*";
	if (newrem.Name != "---") {
		cout << " (" << newrem.Name << ")\n";
	}
	else {
		cout << "\n";
	}
	cout << "2. Рік побудови";
	if (newrem.TimeConstrVid != 0) {
		if (newrem.TimeConstrDo != 0) {
			cout << " (" << newrem.TimeConstrVid << " - " << newrem.TimeConstrDo << " роки)\n";
		}
		else {
			cout << " (" << newrem.TimeConstrVid << ")\n";
		}

	}
	else {
		cout << "\n";
	}
	cout << "3. Місце знаходження";
	if (newrem.Oblast != "---") {
		if (newrem.Ukraine) {
			cout << " (Україна, " << newrem.Oblast << " область)\n";
		}
		else {
			cout << " (" << newrem.Oblast << ")\n";
		}

	}
	else {
		cout << "\n";
	}
	cout << "4. Тип";
	if (newrem.Type != "---") {
		cout << " (" << newrem.Type << ")\n";
	}
	else {
		cout << "\n";
	}
	cout << "5. Готово\n";
	cout << "6. Очистити введені дані\n\n";
	cout << "7. Назад\n";
	cin >> str2;
	choise = str2[0];
	switch (choise) {
	case '1':
		system("cls");
		cin.ignore();
		neworedit = 0;
		MenuNewDataName(neworedit);
		MenuNewData();
		break;
	case '2':
		system("cls");
		neworedit = 0;
		MenuNewDataTime(neworedit);
		MenuNewData();
		break;
	case '3':
		neworedit = 0;
		MenuNewDataPlace(neworedit);
		MenuNewData();
		break;
	case '4':
		system("cls");
		cin.ignore();
		neworedit = 0;
		MenuNewDataType(neworedit);
		MenuNewData();
		break;
	case '5':
		system("cls");
		if (newrem.Name == "---") {
			cout << "Помилка, не введене ім'я пам'ятки!\nСпробуйте знову!\n";
			MenuNewData();
		}
		else {
			InFile();
		}
		break;
	case '6':
		MenuNewDataClear();
		system("cls");
		cout << "Дані очищені\n";
		MenuNewData();
		break;
	case '7':
		str = "Ви впевнені що хочете вийти, це видалить всі введені дані?(Так/Ні)\n";
		if (AreYouSure(str)) {
			MenuNewDataClear();
			system("cls");
			MainMenu();
			break;
		}
		else {
			system("cls");
			MenuNewData();
			break;
		}
	default: {
		system("cls");
		cout << "Помилка вводу спробуйте знову!\n";
		MenuNewData();
	}
	}
	return;
}

void MenuNewDataClear() {
	newrem.Name = "---";
	newrem.TimeConstrVid = 0;
	newrem.TimeConstrDo = 0;
	newrem.Ukraine = 0;
	newrem.Oblast = "---";
	newrem.Type = "---";
}
void MenuEditingClear() {
	foredit.Name = "---";
	foredit.TimeConstrVid = 0;
	foredit.TimeConstrDo = 0;
	foredit.Ukraine = 0;
	foredit.Oblast = "---";
	foredit.Type = "---";
}

void InFile() {
	ofstream fout;
	fout.open("myFile.txt", ofstream::app | ofstream::binary);
	fout.write((char*)&newrem, sizeof(newrem));
	fout.close();
	system("cls");
	MenuNewDataClear();
	MainMenu();
	return;
}
void OutFile() {
	ifstream fin;
	fin.open("myFile.txt", ifstream::binary);
	while (fin.read((char*)&pnt, sizeof(pnt))) {
		if (pnt.Deleted == 1) {
			pnt.Print();
		}
	}
	fin.close();
}

void MenuNewDataName(int neworedit) {
	string temp;
	cout << "Введіть назву пам'ятки: \n";
	cout << "(Якщо хочете вийти введіть 0)\n";

	getline(cin, temp);
	if (temp == "0") {
		system("cls");
		return;
	}
	else {
		if (MenuNewDataCheckingName(temp)) {
			if (neworedit == 0) {
				newrem.Name = temp;
			}
			else {
				foredit.Name = temp;
			}
			system("cls");
			return;
		}
		else {
			system("cls");
			cout << "Пам'ятка з таким іменем існує, спробуйте знову!\n";
			MenuNewDataName(neworedit);
		}

	}
}

void MenuNewDataTime(int neworedit) {
	string str, str2;
	char choise;
	cout << "Оберіть спосіб задання: \n";
	cout << "1. Вказати сторіччя\n";
	cout << "2. Вказати період\n";
	cout << "3. Вказати точний рік\n";
	cout << "4. Повернутися назад\n";
	cin.ignore();
	cin >> str2;
	choise = str2[0];
	switch (choise) {
	case '1':
		MenuNewDataTime1(neworedit);
		break;
	case '2':
		MenuNewDataTime2(neworedit);
		break;
	case '3':
		MenuNewDataTime3(neworedit);
		break;
	case '4':
		str = "Ви впевнені що хочете вийти?(Так/Ні)\n";
		if (AreYouSure(str)) {
			system("cls");
			break;
		}
		else {
			system("cls");
			MenuNewDataTime(neworedit);
			break;
		}
	default:
		system("cls");
		cout << "Помилка вводу спробуйте знову!\n";
		MenuNewDataTime(neworedit);
	}
	return;
}


void MenuNewDataTime1(int neworedit) { //Строліття
	system("cls");
	int temp;
	cout << "Введіть сторіччя: \n";
	cout << "(Якщо хочете вийти введіть 0)\n";
	cin.ignore();
	cin >> temp;
	if (temp == 0) {
		system("cls");
		MenuNewDataTime(neworedit);
	}
	else {
		if (neworedit == 0) {
			newrem.TimeConstrVid = (temp * 100) - 100;
			newrem.TimeConstrDo = (temp * 100);
		}
		else {
			foredit.TimeConstrVid = (temp * 100) - 100;
			foredit.TimeConstrDo = (temp * 100);
		}

		system("cls");
	}
	return;
}

void MenuNewDataTime2(int neworedit) { //Період
	system("cls");
	bool haveproblem;
	int temp, temp2;
	do {
		haveproblem = false;
		cout << "Введіть період: \n";
		cout << "(Якщо хочете вийти введіть 0)\n";
		cout << "Від = ";
		cin.ignore();
		cin >> temp;
		if (temp == 0) {
			system("cls");
			MenuNewDataTime(neworedit);
		}
		cout << "До = ";
		cin.ignore();
		cin >> temp2;
		if (temp2 == 0) {
			system("cls");
			MenuNewDataTime(neworedit);
		}
		else if (temp2 <= temp) {
			system("cls");
			cout << "Помилка! Друга дата менше/дорівнює першій.\nСпробуйте ще раз!\n";
			haveproblem = true;
		}
		else {
			if (neworedit == 0) {
				newrem.TimeConstrVid = temp;
				newrem.TimeConstrDo = temp2;
			}
			else {
				foredit.TimeConstrVid = temp;
				foredit.TimeConstrDo = temp2;
			}
			system("cls");
			return;
		}
	} while (haveproblem);

}

void MenuNewDataTime3(int neworedit) { //Точна дата
	system("cls");
	int temp;
	cout << "Введіть дату: \n";
	cout << "(Якщо хочете вийти введіть 0)\n";
	cin.ignore();
	cin >> temp;
	if (temp == 0) {
		system("cls");
		MenuNewDataTime(neworedit);
	}
	else {
		if (neworedit == 0) {
			newrem.TimeConstrVid = temp;
		}
		else {
			foredit.TimeConstrVid = temp;
		}
		system("cls");
		return;
	}
}

void MenuNewDataPlace(int neworedit) {
	system("cls");
	string temp, temp2;
	cout << "Введіть країну, в якій знаходиться пам'ятка: \n";
	cout << "(Якщо хочете вийти введіть 0)\n";
	cin.ignore();
	getline(cin, temp);
	if (temp == "0") {
		system("cls");
	}
	else if (temp == "Україна") {
		cout << "Введіть область: \n";
		getline(cin, temp2);
		if (neworedit == 0) {
			newrem.Ukraine = 1;
			newrem.Oblast = temp2;
		}
		else {
			foredit.Ukraine = 1;
			foredit.Oblast = temp2;
		}
		system("cls");
	}
	else {
		if (neworedit == 0) {
			newrem.Ukraine = false;
			newrem.Oblast = temp;
		}
		else {
			foredit.Ukraine = false;
			foredit.Oblast = temp;
		}
		system("cls");
	}
	return;
}

void MenuNewDataType(int neworedit) {

	string temp;
	cout << "Введіть тип пам'ятки(Заповідник, Будівля, Замок): \n";
	cout << "(Якщо хочете вийти введіть 0)\n";

	cin >> temp;
	if (temp == "0") {
		system("cls");
	}
	else if (temp != "Заповідник" && temp != "Будівля" && temp != "Замок") {
		system("cls");
		cout << "Помилка вводу спробуйте знову!\n";
		cin.ignore();
		MenuNewDataType(neworedit);
	}
	else {
		if (neworedit == 0) {
			newrem.Type = temp;
		}
		else {
			foredit.Type = temp;
		}
		system("cls");
	}
	return;
}

bool MenuNewDataCheckingName(string temp) {
	ifstream file;
	file.open("myFile.txt", ifstream::binary);
	while (file.read((char*)&pnt, sizeof(pnt))) {
		if (pnt.Name == temp) {
			file.close();
			return false;
		}
	}
	file.close();
	return true;
}


void MenuFinding() {
	int poisdeledit; //0, 1 або 2 відповідно;
	int neworedit;
	string str, str2, str3;
	char choise;
	cout << "Критерії пошуку: \n";
	cout << "1. Назва";
	if (newrem.Name != "---") {
		cout << " (" << newrem.Name << ")\n";
	}
	else {
		cout << "\n";
	}
	cout << "2. Рік побудови";
	if (newrem.TimeConstrVid != 0) {
		if (newrem.TimeConstrDo != 0) {
			cout << " (" << newrem.TimeConstrVid << " - " << newrem.TimeConstrDo << " роки)\n";
		}
		else {
			cout << " (" << newrem.TimeConstrVid << ")\n";
		}

	}
	else {
		cout << "\n";
	}
	cout << "3. Місце знаходження";
	if (newrem.Oblast != "---") {
		if (newrem.Ukraine) {
			cout << " (Україна, " << newrem.Oblast << " область)\n";
		}
		else {
			cout << " (" << newrem.Oblast << ")\n";
		}

	}
	else {
		cout << "\n";
	}
	cout << "4. Тип";
	if (newrem.Type != "---") {
		cout << " (" << newrem.Type << ")\n";
	}
	else {
		cout << "\n";
	}
	cout << "5. Пошук\n";
	cout << "6. Очистити введені дані\n\n";
	cout << "7. Видалити всі дані\n\n";
	cout << "8. Назад\n";
	cin >> str2;
	choise = str2[0];
	switch (choise) {
	case '1':
		system("cls");
		MenuFindingName();
		MenuFinding();
		break;
	case '2':
		system("cls");
		neworedit = 0;
		MenuNewDataTime(neworedit);
		MenuFinding();
		break;
	case '3':
		neworedit = 0;
		MenuNewDataPlace(neworedit);
		MenuFinding();
		break;
	case '4':
		system("cls");
		cin.ignore();
		neworedit = 0;
		MenuNewDataType(neworedit);
		MenuFinding();
		break;
	case '5':
		system("cls");
		poisdeledit = 0;
		MenuFindingStart(poisdeledit);
		break;
	case '6':
		MenuNewDataClear();
		system("cls");
		cout << "Введені дані успішно очищені!\n";
		MenuFinding();
		break;
	case '7':
		system("cls");
		str = "Ви впевнені що хочете видалити всі дані?(Так/Ні)\n";
		if (AreYouSure(str)) {
			MenuNewDataClear();
			fstream file;
			file.open("myFile.txt", fstream::out);
			file.close();
			system("cls");
			cout << "Всі дані успішно видалені!\n";
			MainMenu();
			break;
		}
		else {
			system("cls");
			MenuFinding();
			break;
		}
	case '8':
		str = "Ви впевнені що хочете вийти, це видалить всі введені дані?(Так/Ні)\n";
		if (AreYouSure(str)) {
			MenuNewDataClear();
			system("cls");
			MainMenu();
			break;
		}
		else {
			system("cls");
			MenuFinding();
			break;
		}
	default: {
		system("cls");
		cout << "Помилка вводу спробуйте знову!\n";
		MenuFinding();
	}
	}
	return;
}

void MenuFindingName() {
	string temp = "*";
	cout << "Введіть назву пам'ятки: \n";
	cout << "(Якщо хочете вийти введіть 0)\n";
	cin.ignore();
	getline(cin, temp);
	if (temp == "0") {
		system("cls");
		return;
	}
	else {
		newrem.Name = temp;
		system("cls");
		return;
	}
}

void MenuEditing() {
	int poisdeledit, neworedit;
	string str, str2;
	char choise;
	cout << "Введіть дані які хочете замінити:\n";
	cout << "1. Назва";
	if (foredit.Name != "---") {
		cout << " (" << foredit.Name << ")\n";
	}
	else {
		cout << "\n";
	}
	cout << "2. Рік побудови";
	if (foredit.TimeConstrVid != 0) {
		if (foredit.TimeConstrDo != 0) {
			cout << " (" << foredit.TimeConstrVid << " - " << foredit.TimeConstrDo << " роки)\n";
		}
		else {
			cout << " (" << foredit.TimeConstrVid << ")\n";
		}

	}
	else {
		cout << "\n";
	}
	cout << "3. Місце знаходження";
	if (foredit.Oblast != "---") {
		if (foredit.Ukraine) {
			cout << " (Україна, " << foredit.Oblast << " область)\n";
		}
		else {
			cout << " (" << foredit.Oblast << ")\n";
		}

	}
	else {
		cout << "\n";
	}
	cout << "4. Тип";
	if (foredit.Type != "---") {
		cout << " (" << foredit.Type << ")\n";
	}
	else {
		cout << "\n";
	}
	cout << "5. Редагувати обрані дані\n";
	cout << "6. Очистити введені дані\n";
	cout << "7. Назад\n";
	cin >> str2;
	choise = str2[0];
	switch (choise) {
	case '1':
		system("cls");
		neworedit = 1;
		cin.ignore();
		MenuNewDataName(neworedit);
		MenuEditing();
		break;
	case '2':
		system("cls");
		neworedit = 1;
		MenuNewDataTime(neworedit);
		MenuEditing();
		break;
	case '3':
		neworedit = 1;
		MenuNewDataPlace(neworedit);
		MenuEditing();
		break;
	case '4':
		system("cls");
		cin.ignore();
		neworedit = 1;
		MenuNewDataType(neworedit);
		MenuEditing();
		break;
	case '5':
		system("cls");
		poisdeledit = 2;
		MenuFindingStart(poisdeledit);
		break;
	case '6':
		MenuEditingClear();
		system("cls");
		cout << "Введені дані успішно очищені!\n";
		MenuEditing();
		break;
	case '7':
		str = "Ви впевнені що хочете повернутися назад, це видалить всі введені дані?(Так/Ні)\n";
		if (AreYouSure(str)) {
			MenuEditingClear();
			system("cls");
			poisdeledit = 0;
			MenuFindingStart(poisdeledit);
			break;
		}
		else {
			system("cls");
			MenuEditing();
			break;
		}
	default: {
		system("cls");
		cout << "Помилка вводу спробуйте знову!\n";
		MenuEditing();
	}
	}
	return;
}

void MenuFindingStart(int poisdeledit) {
	vector<vector<string>> data;
	int fordeleting = 0;
	int Number = 0;
	string str;
	fstream file;
	file.open("myFile.txt", fstream::in | fstream::out | fstream::app | fstream::binary);
	while (file.read((char*)&pnt, sizeof(pnt))) {
		if (newrem.Name == "---" || newrem.Name == pnt.Name) {
			//Перевірка імені, якщо воно задавалось
		}
		else {
			if (poisdeledit == 1 || poisdeledit == 2) {
				Deleting(data, &fordeleting);
			}
			continue;
		}

		if ((newrem.TimeConstrVid == 0) || (pnt.TimeConstrVid != 0 && pnt.TimeConstrDo == 0 && newrem.TimeConstrVid != 0 && newrem.TimeConstrDo == 0 && pnt.TimeConstrVid == newrem.TimeConstrVid) ||
			(pnt.TimeConstrVid != 0 && pnt.TimeConstrDo != 0 && newrem.TimeConstrVid != 0 && newrem.TimeConstrDo != 0 && ((newrem.TimeConstrVid >= pnt.TimeConstrVid) && (newrem.TimeConstrDo <= pnt.TimeConstrDo)) ||
				(pnt.TimeConstrVid != 0 && pnt.TimeConstrDo != 0 && newrem.TimeConstrVid != 0 && newrem.TimeConstrDo == 0 && ((newrem.TimeConstrVid >= pnt.TimeConstrVid) && (newrem.TimeConstrVid <= pnt.TimeConstrDo))))) {
			//Перевірка дати
		}
		else {
			if (poisdeledit == 1 || poisdeledit == 2) {
				Deleting(data, &fordeleting);
			}
			continue;
		}

		if ((newrem.Ukraine == pnt.Ukraine && newrem.Oblast == pnt.Oblast) || (!newrem.Ukraine && newrem.Oblast == "---")) {
			//Перевірка місця побудови
		}
		else {
			if (poisdeledit == 1 || poisdeledit == 2) {
				Deleting(data, &fordeleting);
			}
			continue;
		}

		if (newrem.Type == "---" || newrem.Type == pnt.Type) {
			//Перевірка типу, якщо воно задавалось
		}
		else {
			if (poisdeledit == 1 || poisdeledit == 2) {
				Deleting(data, &fordeleting);
			}
			continue;
		}
		Number++;
		//Якщо всі перевірки пройдено то виконується щось з наступного
		if (poisdeledit == 0) {
			pnt.Print();
		}
		else if (poisdeledit == 2) {
			data.resize(fordeleting + 1);
			for (auto& it : data) {
				it.resize(6);
			}
			if (foredit.Name == "---") {
				data[fordeleting][0] = pnt.Name;
			}
			else {
				data[fordeleting][0] = foredit.Name;
			}

			if (foredit.TimeConstrVid == 0) {
				data[fordeleting][1] = to_string(pnt.TimeConstrVid);
				data[fordeleting][2] = to_string(pnt.TimeConstrDo);
			}
			else {
				data[fordeleting][1] = to_string(foredit.TimeConstrVid);
				data[fordeleting][2] = to_string(foredit.TimeConstrDo);
			}

			if (foredit.Oblast == "---") {
				data[fordeleting][3] = to_string(pnt.Ukraine);
				data[fordeleting][4] = pnt.Oblast;
			}
			else {
				data[fordeleting][3] = to_string(foredit.Ukraine);
				data[fordeleting][4] = foredit.Oblast;
			}

			if (foredit.Type == "---") {
				data[fordeleting][5] = pnt.Type;
			}
			else {
				data[fordeleting][5] = foredit.Type;
			}
			fordeleting++;
		}
	}
	file.close();
	if (poisdeledit == 1 || poisdeledit == 2) {
		ofstream fout;
		fout.open("myFile.txt", ofstream::binary);
		for (int i = 0; i < fordeleting; i++) {
			pnt.Name = data[i][0];
			cout << data[i][1];
			pnt.TimeConstrVid = stoi(data[i][1]);
			pnt.TimeConstrDo = stoi(data[i][2]);
			pnt.Ukraine = stoi(data[i][3]);
			pnt.Oblast = data[i][4];
			pnt.Type = data[i][5];
			fout.write((char*)&pnt, sizeof(newrem));
		}
		fout.close();
		system("cls");
		MenuNewDataClear();
		if (poisdeledit == 1) {
			cout << "Дані успішно видалені!\n";
		}
		else if (poisdeledit == 2) {
			cout << "Дані успішно редаговані!\n";
		}
		MainMenu();
		return;
	}
	if (poisdeledit == 0) {
		MenuAfterStart(Number);
	}
	else {
		system("cls");
		MenuNewDataClear();
		MainMenu();
	}

}

void MenuAfterStart(int Number) {
	int poisdeledit;
	string str, str2;
	char choise;
	if (Number == 0) {
		cout << "Даних по введеним критеріям не знайдено!\n\n";
		cout << "1. Видалення неможливе!\n";
		cout << "2. Редагування неможливе!\n";
	}
	else {
		cout << "1. Видалити дані\n";
		cout << "2. Редагувати дані ";
		if (Number == 1) {
			cout << "\n";
		}
		else {
			cout << "(Неможливо: обрано більше однієї пам'ятки)\n";
		}
	}

	cout << "3. Змінити критерії пошуку\n\n";
	cout << "4. Вийти в головне меню\n";
	cin >> str2;
	choise = str2[0];
	switch (choise) {
	case '1':
		if (Number == 0) {
			system("cls");
			cout << "Операція неможлива!\n";
			MenuAfterStart(Number);
			break;
		}
		else {
			system("cls");
			poisdeledit = 1;
			MenuFindingStart(poisdeledit);
			break;
		}
	case '2':
		if (Number != 1) {
			system("cls");
			cout << "Операція неможлива!\n";
			MenuAfterStart(Number);
			break;
		}
		else {
			system("cls");
			MenuEditing();
			break;
		}
	case '3':
		system("cls");
		MenuFinding();
		break;
	case '4':
		str = "Ви впевнені що хочете вийти в головне меню?(Так/Ні)\n";
		if (AreYouSure(str)) {
			MenuNewDataClear();
			system("cls");
			MainMenu();
			break;
		}
		else {
			MenuAfterStart(Number);
			break;
		}
	default: {
		system("cls");
		cout << "Помилка вводу спробуйте знову!\n";
		MenuAfterStart(Number);
	}
	}
	return;
}

void Deleting(vector<vector<string>>& data, int* fordeleting) {
	data.resize(*fordeleting + 1);
	for (auto& it : data)
	{
		it.resize(6);
	}
	data[*fordeleting][0] = pnt.Name;
	data[*fordeleting][1] = to_string(pnt.TimeConstrVid);
	data[*fordeleting][2] = to_string(pnt.TimeConstrDo);
	data[*fordeleting][3] = to_string(pnt.Ukraine);
	data[*fordeleting][4] = pnt.Oblast;
	data[*fordeleting][5] = pnt.Type;
	(*fordeleting)++;
	return;
}