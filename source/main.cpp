#include <iostream>
#include <string>

#include "CLI11.hpp"
#include "lib.hpp"

auto main(int argc, char** argv) -> int
{
  CLI::App app("Threading libraries benchmark application");
  app.set_help_all_flag("--help-all", "Expand all help");

  CLI::App* sc_seq =
      app.add_subcommand("seq_for", "Do not use parallelisation");
  CLI::App* sc_std =
      app.add_subcommand("std_for", "Use STD parallelized templates");
  CLI::App* sc_tbb =
      app.add_subcommand("tbb_for", "Use Threading Building Blocks");
  CLI::App* sc_omp = app.add_subcommand("omp_for", "Use OpenMP library");

  app.require_subcommand();

  CLI11_PARSE(app, argc, argv);

  auto lib = library {};
  std::string op(argv[1]);
  return lib.run(op);
  }
