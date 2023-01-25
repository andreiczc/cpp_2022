#include <iostream>
#include <cmath>

using namespace std;

enum class Color {
		WHITE,
		BLACK
};

class Piece {
public:
		virtual int move() = 0;

		virtual int* getAvailableMoves() = 0;

		virtual ~Piece() noexcept {
				delete[] this->modifier;
		}

protected:

		Piece(Color color) {
				this->position = 0;
				this->color = color;
				this->modifier = new int[this->modifierLength];

				for (int i = 0; i < this->modifierLength; ++i) {
						this->modifier[i] = i * 5;
				}
		}

		int* modifier;
		const int modifierLength = 3;
		int position;
		Color color;
};

class SimplePiece : public Piece {
public:
		SimplePiece(Color color) : Piece(color) {
				this->specialModifier = new int[3];
				for (int i = 0; i < this->modifierLength; ++i) {
						this->specialModifier[i] = i * 10;
				}
		}

		int move() override {
				int idx = rand() % this->modifierLength;
				this->position += 1 + this->modifier[idx] + this->specialModifier[idx];

				return this->position;
		}

		int* getAvailableMoves() override {
				int* result = new int[1];
				result[0] = position + 1;

				return result;
		}

		~SimplePiece() {
				delete[] this->specialModifier;
		}

private:
		int* specialModifier;
};

int main() {
		SimplePiece* simplePiecePtr = new SimplePiece(Color::WHITE);
		cout << "New position for simple piece ptr: " << simplePiecePtr->move() << endl;

		delete simplePiecePtr;
}