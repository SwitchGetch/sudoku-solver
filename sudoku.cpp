#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Cell
{
public:

    int value;
    vector<int> possible;

    void erase(int& n)
    {
        if (possible.size() == 1)
        {
            value = possible[0];
        }
        else
        {
            for (int i = 0; i < possible.size(); i++)
            {
                if (possible[i] == n)
                {
                    possible.erase(possible.begin() + i);
                    break;
                }
            }
        }
    }
};

void parse(vector<vector<Cell>>& field, string file_name)
{
    ifstream ifile(file_name);

    if (ifile.is_open())
    {
        string line;

        while (getline(ifile, line))
        {
            vector<Cell> temp_line;

            for (int i = 0; i < 9; i++)
            {
                Cell temp_cell;

                temp_cell.value = line[i] - 48;

                if (!temp_cell.value)
                {
                    for (int j = 1; j <= 9; j++)
                    {
                        temp_cell.possible.push_back(j);
                    }
                }

                temp_line.push_back(temp_cell);
            }

            field.push_back(temp_line);
        }
    }
}

void output(vector<vector<Cell>>& field)
{
    cout << endl;

    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0) cout << endl;

        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0) cout << " ";

            cout << field[i][j].value << " ";
        }

        cout << endl;
    }

    cout << endl;
}

bool check(vector<vector<Cell>>& field)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!field[i][j].value) return true;
        }
    }

    return false;
}

void eraseLine(vector<vector<Cell>>& field, int& i, int& n)
{
    for (int j = 0; j < 9; j++)
    {
        field[i][j].erase(n);
    }
}

void eraseColumn(vector<vector<Cell>>& field, int& j, int& n)
{
    for (int i = 0; i < 9; i++)
    {
        field[i][j].erase(n);
    }
}

void eraseSquare(vector<vector<Cell>>& field, int& i, int& j, int& n)
{
    for (int x = i - i % 3; x < i - i % 3 + 3; x++)
    {
        for (int y = j - j % 3; y < j - j % 3 + 3; y++)
        {
            field[x][y].erase(n);
        }
    }
}

void step(vector<vector<Cell>>& field)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (field[i][j].value)
            {
                eraseLine(field, i, field[i][j].value);
                eraseColumn(field, j, field[i][j].value);
                eraseSquare(field, i, j, field[i][j].value);
            }
        }
    }
}

int main()
{
    vector<vector<Cell>> field;

    parse(field, "Test/easy test.txt");

    output(field);

    while (check(field))
    {
        step(field);
    }

    output(field);
}