#include <iostream>

using namespace std;

static char* deepCopyString(const char* original) {
	char* result = new char[strlen(original) + 1];
	strcpy(result, original);

	return result;
}

static int* deepCopyInt(int* original, int size) {
	int* result = new int[size];
	for (int i = 0; i < size; ++i) {
		result[i] = original[i];
	}

	return result;
}

class Gradebook {
public:
	Gradebook(const char* name, int* avgGradeSubjects, int noSubjects): name(deepCopyString(name)),
																		avgGradeSubjects(deepCopyInt(avgGradeSubjects, noSubjects)), 
																		noSubjects(noSubjects) { }

	char* getName() const {
		return deepCopyString(this->name);
	}

	int getNoSubjects() const {
		return this->noSubjects;
	}

	int* getAvgGradeSubjects() const {
		return deepCopyInt(this->avgGradeSubjects, this->noSubjects);
	}

	void setName(const char* name) {
		if (name == nullptr || strlen(name) <= 0) {
			throw exception();
		}

		delete[] this->name;
		this->name = deepCopyString(name);
	}

	void setNoSubjects(int noSubjects) {
		if (noSubjects <= 0) {
			throw exception();
		}

		this->noSubjects = noSubjects;
	}

	void setAvgGradeSubjects(int* avgGradeSubjects, int size) {
		if (avgGradeSubjects == nullptr || size != this->noSubjects) {
			throw exception();
		}

		delete[] this->avgGradeSubjects;
		this->avgGradeSubjects = deepCopyInt(avgGradeSubjects, size);
	}

	~Gradebook() {
		delete[] this->name;
		delete[] this->avgGradeSubjects;
	}

private:
	char* name;
	int* avgGradeSubjects;
	int noSubjects;
};

ostream& operator<<(ostream& out, const Gradebook& obj) {
	// Gradebook <name> has <noSubjects> subjects: <avgGradeSubjects, comma separated>
	char* name = obj.getName();
	int* avgGradeSubjects = obj.getAvgGradeSubjects();
	int noSubjects = obj.getNoSubjects();

	out << "Gradebook " << name << " has " << noSubjects << ": ";
	for (int i = 0; i < noSubjects; ++i) {
		out << avgGradeSubjects[i];
		if (i == noSubjects - 1) {
			continue;
		}
		out << ",";
	}

	return out;
}

istream& operator>>(istream& in, Gradebook& obj) {
	// name,noSubjects,avgGradeSubjects(9,8,7)
	char buffer[128];
	in.getline(buffer, 128);

	char* current = strtok(buffer, ",");
	obj.setName(current);
	
	current = strtok(nullptr, ",");
	obj.setNoSubjects(atoi(current));

	int noSubjects = obj.getNoSubjects();
	int* avgGradeSubjects = new int[noSubjects];
	for (int i = 0; i < noSubjects; ++i) {
		current = strtok(nullptr, ",");
		avgGradeSubjects[i] = atoi(current);
	}
	obj.setAvgGradeSubjects(avgGradeSubjects, noSubjects);
	delete[] avgGradeSubjects;

	return in;
}

int main() {
	const char* name = "gradebook1";
	int avgGradeSubjects[]{ 9, 8, 7 };
	// int noSubjects = sizeof(avgGradeSubjects) / sizeof(avgGradeSubjects[0]);
	int noSubjects = 3;

	Gradebook gradebook(name, avgGradeSubjects, noSubjects);
	cin >> gradebook;
	cout << gradebook;

	return 0;
}