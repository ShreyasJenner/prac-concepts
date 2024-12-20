#include <clocale>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  std::wstring a, b;

  a = L"\u30FF";

  std::wcout << a << '\n';

  return 0;
}
