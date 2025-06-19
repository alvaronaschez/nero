let

  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-25.05";

  pkgs = import nixpkgs { config = {}; overlays = []; };

in
 pkgs.mkShell {
   packages = with pkgs; [
      clang-tools # this has to go first, otherwise clangd does not work, idk why

      gnumake
      cmake
      gcc
      clang
      #ninja
      glibcLocales

      gdb
      valgrind

      ncurses
      catch2_3
      lua5_4
      lager
      zug # lager dependency
      boost188
      immer
      utf8cpp
      notcurses
      libunistring
      pkg-config
   ];

   GREETING = "Hello, Nero!";

   shellHook = ''
    export CXXFLAGS="-D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700"
  '';
 }
