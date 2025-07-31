#!/bin/bash

printf "[CMake] [Gen-Project.sh]\n\n"

read -p "Build Directory : " BUILD_DIRECTORY
read -p "Generator       : " GENERATOR
read -p "C Compiler      : " C_COMPILER
read -p "C++ Compiler    : " CXX_COMPILER

CMD="cmake"

if [[ -n "$BUILD_DIRECTORY" ]]; then
  CMD+=" -B \"$BUILD_DIRECTORY\""
else
  CMD+=" -B build"
fi

if [[ -n "$GENERATOR" ]]; then
  CMD+=" -G \"$GENERATOR\""
fi

if [[ -n "$C_COMPILER" ]]; then
  CMD+=" -D CMAKE_C_COMPILER=\"$C_COMPILER\""
fi

if [[ -n "$CXX_COMPILER" ]]; then
  CMD+=" -D CMAKE_CXX_COMPILER=\"$CXX_COMPILER\""
fi

printf "\nRunning : \`%s\`\n\n" "$CMD"
eval "$CMD"
