#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// 7 ��� -> 17
// ��������� ������� ��������� ;
// ���� ��������;

class EncryptClassTrisemus
{
private:

	//string alphabet = "�������������������������������� .,";
	//string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,-0123456789";
	string alphabet = "0123456789+-";
	int rows;
	int cols;
	vector<vector<char>> table;

	void buildTable(string keyword)
	{
		string tableString;
		for (char c : keyword)
		{
			if (tableString.find(c) == string::npos)
			{
				tableString += c;
			}
		}

		cols = tableString.size();
		rows = (alphabet.size() + cols - 1) / cols;
		table = vector<vector<char>>(rows, vector<char>(cols, ' '));

		for (char c : alphabet)
		{
			if (tableString.find(c) == string::npos)
			{
				tableString += c;
			}
		}

		int index = 0;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (index < tableString.size())
				{
					table[i][j] = tableString[index++];
				}
			}
		}
	}

	struct Position
	{
		int x, y;
	};
	Position FindPosition(char c)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (table[i][j] == c)
				{
					Position pos;
					pos.x = i;
					pos.y = j;
					return pos;
				}
			}
		}
	}

public:

	EncryptClassTrisemus()
	{

	}

	string encrypt(string text, string keyword)
	{
		buildTable(keyword);

		string encryptedText;
		for (char c : text)
		{
			// ������� ������� ������� � ������� � �������� �� ���� ������ ���� 
			Position pos = FindPosition(c);
			encryptedText += table[(pos.x + 1) % rows][pos.y];
		}
		return encryptedText;
	}

	string decrypt(string encryptedText, string keyword)
	{
		buildTable(keyword);
		string decryptedText;
		for (char c : encryptedText)
		{
			// ������� ������� ������� � ������� � �������� �� ���� ������ �����
			Position pos = FindPosition(c);
			// �������� �� ���� ������ �����, ���� ������ ������ ����� 0, ��������� � ��������� ������
			decryptedText += table[(pos.x - 1 + rows) % rows][pos.y];
		}
		return decryptedText;
	}
};

class EncryptClassScytale
{
private:
	int rows, cols;
public:
	EncryptClassScytale()
	{

	}

	string encrypt(string text)
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] == ' ')
			{
				text[i] = '_';
			}
		}

		rows = sqrt(text.size());
		cols = (text.size() - 1) / rows + 1;

		vector<vector<char>> table(rows, vector<char>(cols));

		// ��������� ������� ���������
		int index = 0;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (index < text.size())
				{
					table[i][j] = text[index++];
				}
			}
		}

		// ��������� ������� �� ��������
		string encryptedText;
		for (int j = 0; j < cols; ++j)
		{
			for (int i = 0; i < rows; ++i)
			{
				encryptedText += table[i][j];
			}
		}

		return encryptedText;
	}

	string decrypt(string encryptedText)
	{
		rows = sqrt(encryptedText.size());
		cols = (encryptedText.size() - 1) / rows + 1;

		vector<vector<char>> table(rows, vector<char>(cols));

		// ��������� ������� �� ��������
		int index = 0;
		for (int j = 0; j < cols; ++j)
		{
			for (int i = 0; i < rows; ++i)
			{
				if (index < encryptedText.size())
				{
					table[i][j] = encryptedText[index++];
				}
			}
		}

		// ��������� ������� ���������
		string decryptedText;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				decryptedText += table[i][j];
			}
		}

		for (int i = 0; i < decryptedText.size(); i++)
		{
			for (int i = 0; i < decryptedText.size(); i++)
			{
				if (decryptedText[i] == '_')
				{
					decryptedText[i] = ' ';
				}
			}
		}
		return decryptedText;
	}
};

int main()
{
	system("chcp 1251");
	system("cls");

	EncryptClassTrisemus a;
	EncryptClassScytale b;
	string text = "123456789+-";
	string keyword = "11122";

	/*string encryptedText = b.encrypt(text);
	cout << "������������� �����: " << encryptedText << endl;
	cout << "�������������� �����: " << b.decrypt(encryptedText) << endl;*/

	string encryptedText = a.encrypt(text, keyword);
	cout << "������������� �����1: " << encryptedText << endl;

	string encryptedText2 = b.encrypt(encryptedText);
	cout << "������������� �����2: " << encryptedText2 << endl;

	string decryptedText1 = b.decrypt(encryptedText2);
	cout << "�������������� �����2: " << decryptedText1 << endl;

	string decryptedText2 = a.decrypt(decryptedText1, keyword);
	cout << "�������������� �����1: " << decryptedText2;

	return 0;
}