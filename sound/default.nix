{ lib, buildSDLPackage }:

buildSDLPackage rec {
  pname = "my-sdl-app";
  version = "1.0";

  src = ./.;

  nativeBuildInputs = [
    lib.makeWrapper
  ];

  buildInputs = [
    buildSDL2  # SDL2 library
    buildSDL2_ttf  # SDL2 TrueType Font library
    # Add other SDL-related dependencies as needed
  ];

  meta = with lib; {
    description = "My SDL Application";
    license = licenses.mit;
  };
}
