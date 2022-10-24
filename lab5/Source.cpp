#include <iostream>

using namespace std;

class Student {
public:
	Student(const string& name, float age): id(sequence) {
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
	Grade(float value, SubjectEnum subject) {
		this->value = value;
		this->subject = subject;
	}

	void print() {
		cout << "Grade for " << (subject == SubjectEnum::JAVA ? "Java" : "OOP")
			<< " is " << value << endl;
	}

private:
	float value;
	SubjectEnum subject;
};

enum class SemesterEnum {
	TERM_1,
	TERM_2
};

class GradeBook {
public:
	GradeBook(int year, SemesterEnum semester): year(year) {
		this->semester = semester;
		this->gradesAssigned = 0;
		this->maxGrades = 5;
		this->grades = new Grade*[maxGrades];
	}

	void addGrade(Grade* grade) {
		this->grades[gradesAssigned] = grade;

		++gradesAssigned;
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

	Grade grade1(10, SubjectEnum::OOP);
	grade1.print();

	return 0;
}