// Linear Cipher.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <cctype>

using namespace std;

//We require a few 'global' variables
string code = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int a, b;

//we need this function to check for co-primality
int gcd(int a,int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void encrypt(string str)
{
	string process = "Encrypting...";

	for (auto i = 0; i < str.size(); i++)
		str[i] = toupper(str[i]);

	for (auto i = 0; i < process.size(); i++)
	{
		cout << process[i];
		Sleep(100);
	}
	cout << "\n\n";

	char c[sizeof(str) / sizeof(str[0])];		//character type somehow didn't accept c[str.size()]
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			c[i] = str[i];
			cout << c[i];
		}
		else
		{
			//find the letter from the alphabet list
			int pos_x = code.find((char)str[i]);
			//Encrypt using E=ax+b (mod 26)
			pos_x = (a*pos_x + b) % 26;
			//replace the letter in the current position with the position obtained from the modular equation
			c[i] = code[pos_x];
			//keep printing...
			cout << c[i];
		}
	}
}

void decrypt(string str)
{
	string process = "Decrypting...";

	for (auto i = 0; i < str.size(); i++)
		str[i] = toupper(str[i]);

	for (auto i = 0; i < process.size(); i++)
	{
		cout << process[i];
		Sleep(100);
	}
	cout << "\n\n";

	//calculates a inverse for D=a^(-1)*(x-b)
	for (int y = 0; y < 26; y++)
	{
		if (a*y % 26 == 1)
		{
			a = y;
			break;
		}
	}

	char c[sizeof(str) / sizeof(str[0])];		//character type somehow didn't accept c[str.size()]
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			c[i] = str[i];
			cout << c[i];
		}
		else
		{
			//find the letter from the alphabet list
			int pos_x = code.find((char)str[i]);
			//Decrypt using D=a^(-1)(x-b) (mod 26)
			pos_x = a * (pos_x - b);
			//if this product is negative then turn it into positive before doing mod 26
			//this is done by adding cycles of 26 to this pos_x value
			while (pos_x < 0)
				pos_x += 26;
			//now perform modulo division
			pos_x %= 26;
			//replace the letter in the current position with the position obtained from the modular equation
			c[i] = code[pos_x];
			//keep printing...
			cout << c[i];
		}
	}
}

int main()
{
	//variables_list_start
	string intro_1 = "Linear Cipher Program v1.01";
	string intro_2 = "Coded by Awnon Bhowmik\n\n";
	
	string plain_text;
	
	//variables_list_end;

	for (auto i = 0; i < intro_1.size(); i++)
	{
		cout << intro_1[i];
		Sleep(100);
	}
	cout << endl;
	for (auto i = 0; i < intro_2.size(); i++)
	{
		cout << intro_2[i];
		Sleep(100);
	}

	cout << "Enter linear variables a,b such that 1<=a<=25 and 0<=b<=25:";
	cin >> a >> b;
	if (a < 1 && a > 25) 
	{
		cout << endl << "We require 1<=a<=25";
		return 0;
	}
	if (b < 0 && b > 25)
	{
		cout << "We require 0<=b<=25";
		return 0;
	}
	if (gcd(a, 26) != 1)
	{
		cout << "a and m must be coprime in the equation E = ax+b (mod m)";
		return 0;
	}

	cout << endl << "Enter string: ";
	cin.ignore();
	getline(cin, plain_text);

	cout << "1. Encrypt\n2. Decrypt";
	cout << "\n\n Choose one:";
	int choice;
	cin >> choice;
	//While we may have done it using logical if statements, I chose to use switch statement since we are dealing with only 2 cases
	//the other cases are by default unimportant to us
	switch (choice)
	{
	case 1:
		encrypt(plain_text);
		break;
	case 2:
		decrypt(plain_text);
		break;
	default:
		cout << "Wrong input!";
		break;
	}
	return 0;
}