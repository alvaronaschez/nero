 let
   nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-24.05";
   pkgs = import nixpkgs { config = {}; overlays = []; };
 in

 pkgs.mkShellNoCC {
   packages = with pkgs; [
      clang-tools # this has to go first, otherwise clangd does not work, idk why

      gnumake
      cmake
      gcc
      clang
      #ninja
      glibcLocales

      gdb
      #valgrind

      ncurses
      catch2_3
      lua5_4
      lager
      zug # lager dependency
      boost
      immer
      utf8cpp
   ];

   GREETING = "Hello, Nero!";
 }
