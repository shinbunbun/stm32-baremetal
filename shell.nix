{ pkgs ? import <nixpkgs> {} }:

let
in pkgs.mkShell {
  buildInputs = with pkgs; [ 
    gcc-arm-embedded
    stlink
  ];
}