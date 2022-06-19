#include <iostream>
#include <string>
#include <vector>

#include "server.hpp"

int main(int argc, char **argv) {
  // コマンドライン引数を扱いやすい vector<string> に入れる
  std::vector<std::string> args(argv, argv + argc);

  Server server(args);
  server.start();

  return 0;
}
