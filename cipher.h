#ifndef CIPHER_H
#define CIPHER_H
#include <iostream>
#include <string>
using namespace std;



string encryptString(string s) {
	string new_string;
	int index;
	char keys[62] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 
		'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	for (char c:s) {
		for (int count = 0; count < sizeof(keys); count++) {
			if (c == keys[count]) {
				index = (count + 3) % 62;
				continue;
			}
		}
		new_string += keys[index];

	}

	return new_string;

}


string decryptString(string s) {
	string new_string;
	int index;
	char keys[62] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
		'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	for (char c : s) {
		for (int count = 0; count < sizeof(keys); count++) {
			if (c == keys[count]) {
				index = (count - 3);
				if (index < 0) {
					index = (index + 62) % 62;
				}
				else {
					index = index % 62;
				}
				continue;
			}
		}
		new_string += keys[index];

	}

	return new_string;

}
#endif
