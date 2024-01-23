{ pkgs ? import <nixpkgs> {} }:

let
  sdl2 = pkgs.SDL2;  # Add the correct package reference if needed
  jack = pkgs.jack2;  # Add the correct package reference if needed
  libjack = pkgs.libjack2;  # Add the correct package reference if needed
in

pkgs.mkShell {
  buildInputs = [
    sdl2
    jack
    pkgs.hello
    pkgs.raylib
    pkgs.bashInteractive
    pkgs.pkg-config
    pkgs.glfw
    pkgs.glfw-wayland
  ];

  # Set PKG_CONFIG_PATH to include SDL2.pc
  shellHook = ''
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${sdl2.dev}/lib/pkgconfig
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${jack}/lib/pkgconfig
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${pkgs.pkg-config}
    export LD_LIBRARY_PATH=${pkgs.SDL2}/lib
    export CMAKE_MODULE_PATH=${pkgs.raylib}/lib:${jack}/lib:$CMAKE_MODULE_PATH
    export raylib_DIR=${pkgs.raylib}/lib/cmake/raylib/
    export raylib_LIBRARY=${pkgs.raylib}/lib
    export raylib_INCLUDE_DIR=${pkgs.raylib}/include

    export CMAKE_PREFIX_PATH=${sdl2}:${jack}:${pkgs.raylib}:${libjack}:$CMAKE_PREFIX_PATH
  '';
}


