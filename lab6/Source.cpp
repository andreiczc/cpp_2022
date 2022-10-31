#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

class Student {
public:
	Student(const string& name, float age) : id(sequence) {
		this->name = name;
		this->age = age;

		++Student::sequence;
	}

	void print() {
		cout << "Id: " << this->id
			<< ". Student " << this->name
			<< " is aged " << this->age << endl;
	}

	string getName() const {
		return this->name;
	}

	float getAge() const {
		return this->age;
	}

private:
	const int id;
	string name;
	float age;

	static int sequence;
};

int Student::sequence = 1;

enum class SubjectEnum {
	OOP,
	JAVA
};

class Grade {
public:
	Grade(float value, const char* subject) {
		this->value = value;
		
		this->subject = new char[strlen(subject) + 1];
		strcpy(this->subject, subject);
	}

	Grade(const Grade& grade) {
		this->value = grade.getValue();
		this->subject = new char[strlen(grade.getSubject()) + 1];
		strcpy(this->subject, grade.getSubject());
	}

	float getValue() const {
		return this->value;
	}

	char* getSubject() const {
		char* result = new char[strlen(subject) + 1];
		strcpy(result, this->subject);

		return result;
	}

	void setSubject(const char* otherString) {
		delete[] this->subject;
		this->subject = new char[strlen(otherString) + 1];
		strcpy(this->subject, otherString);
	}

	void print() {
		cout << "Grade for " << subject
			<< " is " << value << endl;
	}

	~Grade() {
		delete[] subject;
	}

private:
	float value;
	char* subject;
};

enum class SemesterEnum {
	TERM_1,
	TERM_2
};

class GradeBook {
public:
	GradeBook(int year, SemesterEnum semester) : year(year) {
		this->semester = semester;
		this->gradesAssigned = 0;
		this->maxGrades = 5;
		this->grades = new Grade * [maxGrades];
	}

	void addGrade(Grade* grade) {
		this->grades[gradesAssigned] = new Grade(*grade);

		++gradesAssigned;
	}

	void print() {
		cout << "Gradebook for year " << year << ", semester "
			<< (semester == SemesterEnum::TERM_1 ? "1" : "2") << ": ";

		for (int i = 0; i < gradesAssigned; ++i) {
			cout << grades[i]->getValue() << "(" 
				<< grades[i]->getSubject() << ")";

			if (i != gradesAssigned - 1) {
				cout << ", ";
			}
		}

		cout << endl;
	}

	~GradeBook() {
		for (int i = 0; i < gradesAssigned; ++i) {
			delete grades[i];
		}

		delete[] grades;
	}

private:
	Grade** grades;
	int gradesAssigned;
	int maxGrades;
	const int year;
	SemesterEnum semester;
};

void printStudent(const Student& stud) {
	cout << "Student " << stud.getName()
		<< " is aged " << stud.getAge() << endl;;
}

int main() {
	Student stud1("stud1", 20);
	Student stud2("stud2", 21);
	// printStudent(stud1);
	stud1.print();
	stud2.print();

	Grade grade1(10, "oop");
	grade1.print();

	Grade* grade2 = new Grade(10, "java");
	grade2->print();

	GradeBook gradebook(2022, SemesterEnum::TERM_1);
	gradebook.addGrade(grade2);

	grade2->setSubject("not java");

	gradebook.print();

	return 0;
}