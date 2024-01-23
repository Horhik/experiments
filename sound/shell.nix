# shell.nix

{ pkgs ? import <nixpkgs> {} }:

let
  sdl2 = pkgs.SDL2;  # Add the correct package reference if needed
  jack = pkgs.jack2;  # Add the correct package reference if needed
in

pkgs.mkShell {
  buildInputs = [
    sdl2
    jack

    pkgs.SDL2  # SDL2 library
    # Add other SDL-related dependencies as needed
  ];

  # Set PKG_CONFIG_PATH to include SDL2.pc
  shellHook = ''
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${sdl2.dev}/lib/pkgconfig
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${jack}/lib/pkgconfig
    export LD_LIBRARY_PATH=${pkgs.SDL2}/lib
  '';
}



#{ pkgs ? import <nixpkgs> {} }:
#with pkgs;
#mkShell {
#  buildInputs =  [
#    SDL2
#    SDL
#    SDL2_gfx
#      ];
#  shellHook = ''
#   LD_LIBRARY_PATH=${pkgs.SDL2}/lib
#   PKG_CONFIG_PATH=${pkgs.SDL2}/lib
#   echo $LD_LIBRARY_PATH
#   echo $PKG_CONFIG_PATH
#'';
#}
#
## /home/user/${julia}/packages/GR/cRdXQ/deps/gr/bin/gksqt
#

