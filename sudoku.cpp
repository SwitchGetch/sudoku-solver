#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;

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

string Time(high_resolution_clock::time_point& start, high_resolution_clock::time_point& end)
{
    string result = "";


    int h = duration_cast<hours>(end - start).count();
    int m = duration_cast<minutes>(end - start).count();
    int s = duration_cast<seconds>(end - start).count();
    int ms = duration_cast<milliseconds>(end - start).count();


    int min = m - h * 60;
    int sec = s - m * 60;
    int milsec = ms - s * 1000;

    result += to_string(h) + ":";

    if (to_string(min).size() == 2) result += to_string(min) + ":";
    else result += "0" + to_string(min) + ":";

    if (to_string(sec).size() == 2) result += to_string(sec) + ":";
    else result += "0" + to_string(sec) + ":";

    if (to_string(milsec).size() == 3) result += to_string(milsec);
    else if (to_string(milsec).size() == 2) result += "0" + to_string(milsec);
    else result += "00" + to_string(milsec);


    return result;
}

int main()
{
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;

    vector<vector<Cell>> field;

    parse(field, "Test/easy test.txt");

    output(field);

    start = high_resolution_clock::now();

    while (check(field))
    {
        step(field);
    }

    end = high_resolution_clock::now();

    output(field);

    cout << endl << "solve time: " << Time(start, end) << endl;
}
