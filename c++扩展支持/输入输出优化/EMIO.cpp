#include <bits/stdc++.h>

namespace EMIO {
	struct ENDL {
		//By ProtectEMmm
	}endl;
	class IStream {
	public:
		IStream &operator >> (int &temp) {
			temp = 0; char c = GetChar(); bool flag = false;
			while (!isdigit(c)) {
				if (c == '-')
					flag = true;
				c = GetChar();
			}
			while (isdigit(c)) {
				temp = temp * 10 + c - '0', c = GetChar();
			}
			temp = flag ? -temp : temp;
			return *this;
		}
		IStream &operator >>(char &temp) {
			temp = ' '; char c = GetChar();
			while (!ischar(c))
				c = GetChar();
			temp = c; return *this;
		}
		IStream &operator >>(double &temp) {
			temp = 0; char c = GetChar(); bool flag = false;
			while (!isdigit(c)) {
				if (c == '-')flag = true; c =
					GetChar();
			}
			while (isdigit(c)) {
				temp = temp * 10 + c - '0', c = GetChar();
			}
			if (c == '.') {
				c = GetChar();
				double point = 0.1;
				while (isdigit(c)) {
					temp += point * (c - '0');
					point *= 0.1; c = GetChar();
				}
			}
			temp = flag ? -temp : temp;
			return *this;
		}
		IStream &operator >>(long long &temp) {
			temp = 0; char c = GetChar(); bool flag = false;
			while (!isdigit(c)) {
				if (c == '-')flag = true; c =
					GetChar();
			}
			while (isdigit(c)) {
				temp = temp * 10 + c - '0', c =
					GetChar();
			}
			temp = flag ? -temp : temp; return *this;
		}
		IStream &operator >>(std::string &temp) {
			temp.clear(); char c = GetChar();
			while (!ischar(c))c = GetChar();
			while (ischar(c))temp += c, c = GetChar();
			return *this;
		}
	private:
		char BUF[1 << 20] = { 0 };
		char *POS = BUF, *END = BUF;
		inline char GetChar() {
			if (POS == END) {
				END = (POS = BUF) + fread(BUF, 1, 1 << 20, stdin);
			}
			return POS == END ? EOF : *POS++;
		}
		inline bool ischar(const char &c) {
			return c != ' ' && c != '\n';
		}
		inline bool isdigit(const char &c) {
			return '0' <= c && c <= '9';
		}
	} fin;

	class OStream {
	public:
		~OStream() {
			Flush();
		}
		inline void Flush() {
			fwrite(BUF, 1, POS - BUF, stdout); POS = BUF;
		}
		inline void SetPoint(int x) {
			point = x;
		}
		OStream &operator << (int temp) {
			int Top = 0; static int Stack[64];
			if (temp < 0) { PutChar('-'); temp = -temp; }
			do { Stack[Top++] = temp % 10; temp /= 10; } while (temp);
			while (Top) { PutChar(Stack[--Top] + '0'); } return *this;
		}
		OStream &operator << (char temp) {
			PutChar(temp); return *this;
		}
		OStream &operator << ([[maybe_unused]] ENDL temp) {
			PutChar('\n'); Flush(); return *this;
		}
		OStream &operator << (double temp) {
			if (temp < 0) {
				PutChar('-');
				temp = -temp;
			}
			long long integer = temp;
			*this << integer;
			temp -= integer;
			PutChar('.');
			for (int i = 1; i <= point; ++i) {
				temp *= 10;
				PutChar(int(temp) + '0');
				temp -= int(temp);
			}
			return *this;
		}
		OStream &operator << (long long temp) {
			int Top = 0; static int Stack[64];
			if (temp < 0) { PutChar('-'); temp = -temp; }
			do { Stack[Top++] = temp % 10; temp /= 10; } while (temp);
			while (Top) { PutChar(Stack[--Top] + '0'); } return *this;
		}
		OStream &operator <<(const std::string &temp) {
			for (auto c : temp)
			{
				PutChar(c);
			}
			return *this;
		}
		OStream &operator << (const char temp[]) {
			int p = 0;
			while (temp[p] != '\0') {
				PutChar(temp[p++]);
			}
			return *this;
		}
	private:
		int point = 6; char BUF[1 << 20] = { 0 };
		char *POS = BUF, *END = BUF + (1 << 20);
		inline void PutChar(char temp) {
			if (POS == END)
			{
				Flush();
			}
			*POS++ = temp;
		}
	} fout;
}
using EMIO::fin, EMIO::fout;

// using namespace IO;