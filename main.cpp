#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

namespace fs = filesystem;

unordered_set<wchar_t> russian;

wofstream out;

bool containsRussian(wstring &s) {
    for (auto c : s) {
        if (russian.contains(c)) {
            return true;
        }
    }
    return false;
}

wstring escapedLine(wstring &line) {
    wstring escapePart[2] = {L"§\\textcolor{red}{", L"}§"};

    wstring escaped;
    bool streak = false;
    for (int i = 0; i < line.size(); i++) {
        bool isRussian = russian.contains(line[i]);
        if (streak ^ isRussian) {
            escaped += escapePart[streak];
            streak = !streak;
        }
        escaped += line[i];
    }

    return escaped;
}

void printFileContents(const fs::path& filePath) {
    wifstream file(filePath);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
    file.is_open();
    wstring line;
    while (getline(file, line)) {
        out << escapedLine(line) << '\n';
    }
    file.close();
}

void printFiles(const string &end) {
    string path = R"(C:\Users\ark13\MPU\software-design-technologies\lab6)";
    string root = "lab5";

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry.path()) and entry.path().string().ends_with(end)) {
//            out << L"\\subsection*{" << entry.path().wstring().substr(path.size() + 1 - (root.size() + 1)).replace(root.size(), 1, L"/") << L"}\n\n";
            out << L"\\subsection*{" << entry.path().wstring().substr(path.size() + 1) << L"}\n\n";
            out << "\\begin{lstlisting}\n";
            printFileContents(entry.path());
            out << "\\end{lstlisting}\n\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    out = wofstream(R"(C:\Users\ark13\MPU\software-design-technologies\output.txt)");
    out.imbue(std::locale(out.getloc(), new std::codecvt_utf8<wchar_t>));

    for (auto c : L"абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ") {
        russian.insert(c);
    }

    printFiles(".h");
    printFiles(".cpp");

    return 0;
}
