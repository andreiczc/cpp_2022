#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>

using namespace std;

enum class SeatAvailability {
	FREE,
	RESERVED, 
	PAID
};

static char* deepCopy(const char* original) {
	char* result = new char[strlen(original) + 1];
	strcpy(result, original);

	return result;
}

class Seat {
public:
	Seat(short seatId):seatId(seatId) {
		this->availability = SeatAvailability::FREE;
	}

	Seat(const Seat& seat):seatId(seat.seatId) {
		this->availability = seat.availability;
	}

	bool operator==(const Seat& anotherSeat) {
			if (this == &anotherSeat) {
					return true;
			}

			if (this->seatId != anotherSeat.seatId) {
					return false;
			}

			if (this->availability != anotherSeat.availability) {
					return false;
			}

			return true;
	}

	bool operator!=(const Seat& anotherSeat) {
			return !(*this == anotherSeat);
	}

	void setAvailability(SeatAvailability availability) {
		this->availability = availability;
	}

	short getSeatId() {
		return this->seatId;
	}

	SeatAvailability getAvailability() {
		return this->availability;
	}

	void print() {
		cout << "Seat " << this->seatId << " is " << enumToString(this->availability) << endl;
	}

private:
	string enumToString(SeatAvailability availability) {
		switch (availability) {
		case SeatAvailability::FREE:
			return "free";
		case SeatAvailability::RESERVED:
			return "reserved";
		case SeatAvailability::PAID:
			return "paid";
		default:
				return "unkown";
		}
	}

	const short seatId;
	SeatAvailability availability;
};

class Room {
public:
	Room(short roomId, int numberOfSeats): roomId(roomId) {
		this->numberOfSeats = numberOfSeats;
		this->seats = new Seat*[numberOfSeats];

		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i] = new Seat(i + 1);
		}
	}

	Room(const Room& room): roomId(room.roomId) {
		this->numberOfSeats = room.numberOfSeats;
		this->seats = new Seat * [numberOfSeats];

		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i] = new Seat(room.seats[i]->getSeatId());
			this->seats[i]->setAvailability(room.seats[i]->getAvailability());
		}
	}

	bool operator==(const Room& room) {
			if (this == &room) {
					return true;
			}

			if (this->roomId != room.roomId) {
					return false;
			}

			if (this->numberOfSeats != room.numberOfSeats) {
					return false;
			}

			for (int i = 0; i < numberOfSeats; ++i) {
					if (*this->seats[i] != *room.seats[i]) {
							return false;
					}
			}

			return true;
	}

	bool operator!=(const Room& room) {
			return !(*this == room);
	}

	short getRoomId() const {
		return this->roomId;
	}

	Room& operator=(const Room& room) {
		if (this == &room) {
			return *this;
		}

		for (int i = 0; i < numberOfSeats; ++i) {
			delete this->seats[i];
		}
		delete[] this->seats;

		this->roomId = room.roomId;
		this->numberOfSeats = room.numberOfSeats;

		this->seats = new Seat * [numberOfSeats];
		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i] = new Seat(*room.seats[i]);
		}

		return *this;
	}

	~Room() {
		for (int i = 0; i < numberOfSeats; ++i) {
			delete this->seats[i];
		}

		delete[] this->seats;
	}

	void print() {
		cout << "Room " << this->roomId << " has capacity of " << numberOfSeats << " seats." << endl;
		for (int i = 0; i < numberOfSeats; ++i) {
			this->seats[i]->print();
		}
	}

private:
	short roomId;
	int numberOfSeats;
	Seat** seats;
};

class Event {
public:
	Event(): room(0, 1) {
		this->name = nullptr;
		this->startTime = nullptr;
		
		this->runtime = -1;
	}

	Event(const char* name, int runtime, const char* startTime, Room room) : room(room) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

		this->runtime = runtime;

		this->startTime = new char[strlen(startTime) + 1];
		strcpy(this->startTime, startTime);
	}

	Event(const Event& event) : room(event.room) {
		this->runtime = event.runtime;

		this->name = new char[strlen(event.name) + 1];
		strcpy(this->name, event.name);

		this->startTime = new char[strlen(event.startTime) + 1];
		strcpy(this->startTime, event.startTime);
	}

	bool operator==(const Event& anotherEvent) {
			if (this == &anotherEvent) {
					return true;
			}

			if (strcmp(this->name, anotherEvent.name) != 0) {
					return false;
			}

			if (strcmp(this->startTime, anotherEvent.startTime) != 0) {
					return false;
			}

			if (this->runtime != anotherEvent.runtime) {
					return false;
			}

			if (this->room != anotherEvent.room) {
					return false;
			}

			return true;
	}

	bool operator!=(const Event& anotherEvent) {
			if (*this == anotherEvent) {
					return false;
			}

			return true;
	}

	Event& operator=(const Event& anotherEvent) {
		if (this == &anotherEvent) {
			return *this;
		}

		this->runtime = anotherEvent.runtime;

		delete[] this->name;
		this->name = deepCopy(anotherEvent.name);

		delete[] this->startTime;
		this->startTime = deepCopy(anotherEvent.startTime);

		this->room = anotherEvent.room;

		return *this;
	}

	string toString() {
			string result = "";
			result += "Event ";
			result += name;
			result += " runs at ";
			result += startTime;
			result += " in room ";

			char buffer[5];
			_itoa(room.getRoomId(), buffer, 10);
			result += buffer;
			result += " and lasts ";
			result += runtime;
			result += '\n';

			return result;
	}

	void print() {
		cout << "Event " << name << " runs at " << startTime << " in room "
			<< room.getRoomId() << " and lasts " << runtime << endl;
	}

	~Event() {
		delete[] this->name;
		delete[] this->startTime;
	}

private:
	char* name;
	int runtime;
	char* startTime;
	Room room;
};

class Cinema {
public:
	Cinema(const char* name, const char* address) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

		this->address = new char[strlen(address) + 1];
		strcpy(this->address, address);

		this->events = new Event[NO_EVENTS];

		this->runningEvents = 0;
	}

	bool operator==(const Cinema& otherCinema) {
			if (this == &otherCinema) {
					return true;
			}

			if (strcmp(this->name, otherCinema.name) != 0) {
					return false;
			}

			if (strcmp(this->address, otherCinema.address) != 0) {
					return false;
			}

			if (this->runningEvents != otherCinema.runningEvents) {
					return false;
			}

			for (int i = 0; i < this->runningEvents; ++i) {
					if (this->events[i] != otherCinema.events[i]) {
							return false;
					}
			}

			return true;
	}

	bool operator!=(const Cinema& anotherCinema) {
			return !(*this == anotherCinema);
	}

	Cinema& operator=(const Cinema& anotherCinema) {
		if (this == &anotherCinema) {
			return *this;
		}

		delete[] this->name;
		this->name = deepCopy(anotherCinema.name);

		delete[] this->address;
		this->address = deepCopy(anotherCinema.address);
		this->runningEvents = anotherCinema.runningEvents;

		delete[] this->events;
		this->events = new Event[NO_EVENTS];
		for (int i = 0; i < runningEvents; ++i) {
			this->events[i] = anotherCinema.events[i];
		}

		return *this;
	}

	~Cinema() {
		delete[] name;
		delete[] address;
		delete[] events;
	}

	void addEvent(Event& event) {
		this->events[runningEvents] = event;
		++runningEvents;
	}

	operator string() {
			return this->toString();
	}

	string toString() const {
			/*string result = "";
			result += "Cinema ";
			result += name;
			result += " is located at ";
			result += address;
			result += '\n';

			if (runningEvents == 0) {
					result += "No running events!\n";

					return result;
			}

			for (int i = 0; i < runningEvents; ++i) {
					result += events[i].toString();
			}

			return result;*/

			stringstream ss;
			ss << "Cinema " << name << "is located at " << address << endl;

			if (runningEvents == 0) {
					ss << "No running events!" << endl;

					return ss.str();
			}

			for (int i = 0; i < runningEvents; ++i) {
					ss << events[i].toString();
			}

			return ss.str();
	}

	void print() {
		cout << "Cinema " << name << " is located at " << address << endl;
		if (runningEvents == 0) {
			cout << "No running events!" << endl;

			return;
		}

		for (int i = 0; i < runningEvents; ++i) {
			events[i].print();
		}
		cout << endl;
	}

private:
	char* name;
	char* address;
	Event* events;
	int runningEvents;

	static const int NO_EVENTS = 10;

	friend ostream& operator<<(ostream& ostream, const Cinema& cinema);
};

ostream& operator<<(ostream& ostream, const Cinema& cinema) {
		ostream << "Cinema " << cinema.name << " is located at " << cinema.address;
		if (cinema.runningEvents == 0) {
				ostream << "No running events!\n";

				return ostream;
		}

		for (int i = 0; i < cinema.runningEvents; ++i) {
				ostream << cinema.events[i].toString();
		}

		return ostream;
}

int main() {
	Seat seat1(1);
	Seat seat2(2);

	seat1.print();
	seat2.print();

	Room room(1, 10);
	room.print();

	Event event("event1", 120, "10:20", room);
	event.print();

	event = event;

	Cinema cinema("cinema1", "address1");
	cinema.print();

	cout << "************************************" << endl;

	cinema.addEvent(event);
	cinema.print();

	cout << "************************************" << endl;

	Cinema cinema2("", "");
	cinema2 = cinema;
	cinema2.print();

	if (cinema == cinema2) {
			cout << "Cinema and cinema2 are equal" << endl;
	}
	else {
			cout << "Cinema and cinema2 are NOT equal" << endl;
	}

	cout << cinema;

	return 0;
}