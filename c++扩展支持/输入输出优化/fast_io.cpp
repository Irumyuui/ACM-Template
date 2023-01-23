#include <bits/stdc++.h>

// Error
namespace _FIO {
	constexpr int BUFFER = 1 << 18;
	struct ostream {
		char buffer[BUFFER], *pos = buffer, *end = buffer + BUFFER;
		~ostream() { flush(); }
		void flush() {
			fwrite(buffer, 1, pos - buffer, stdout), pos = buffer;
		}
		void put(char ch) {
			if (pos == end) flush(); *(pos++) = ch;
		}
		template <typename T> void put(T num) {
			if (num) put(num / 10), put((char)(num % 10 + '0'));
		}
		ostream &operator << (char s) {
			return put(s), *this;
		}
		ostream &operator << (const char *s) {
			while (*s) put(*(s++));
			return *this;
		}
		template <typename T> ostream &operator << (T num) {
			if (num < 0) put('-'), put(-num);
			else if (num == 0) put('0'); 
			else put(num);
			return *this;
		}
	};
	struct istream { 
		char buffer[BUFFER], *pos = buffer, *end = buffer;
		int get() {
			if (pos == end) end = buffer + fread(buffer, 1, BUFFER, stdin), pos = buffer;
			if (pos == end) return 0;
			return *(pos++);
		}
		istream &operator>>(char &ch) {
			while ((ch = get()) <= ' ')
				;
			return *this;
		}
		template <typename T> istream &operator >> (T &num) {
			int sign = 0, ch, done = 0;
			num = 0;
			while (ch = get())
				if (ch == '-') sign = 1;
				else if ('-' < ch) num = 10 * num + ch - '0', done = 1;
				else if (done) break;
			if (sign) num = -num;
			return *this;
		}
	};
	struct iostream {
		ostream out;
		istream in;
		template <typename T> iostream& operator >> (T &num) {
			this->in >> num;
			return *this;
		}
		template <typename T> iostream& operator << (T num) {
			this->out << num;
			return *this;
		}
	} fio;
}
using _FIO::fio;