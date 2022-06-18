#include <iostream>
#include <string>
#include <vector>

#include "server.hpp"

int main(int argc, char **argv)
{
  // コマンドライン引数を扱いやすい vector<string> に入れる
  std::vector<std::string> args(argv, argv + argc);

  // コマンドライン引数によって処理を変更する
  // -debug : debug mode

  Server server = Server();
  server.start();

  // Server Initialize

  // Server Run

  return 0;
}
