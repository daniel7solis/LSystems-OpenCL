/*
 * Alphabet.h
 *
 *  Created on: 04/07/2014
 *      Author: dani
 */

#ifndef ALPHABET_H_
#define ALPHABET_H_


class Alphabet {
private:
public:
//	char V[14]={'C','\0','A','\0','D','\0','E','\0','N','\0','O','\0'};
	char V[7]={'C','A','D','E','N','O'};
	char temp[2];
	Alphabet();
	virtual ~Alphabet();
	bool verifiSymbol(char *s);
};

#endif /* ALPHABET_H_ */
