#!/bin/bash

# Static Variables
SRC_DIR='src'
BIN_DIR='bin'
COMPILER='g++.exe'
OUTPUT_NAME='AutonoscriptCommand.exe'

SRC_FILES=()
SRC_FILES+=('AutonoscriptCommand.cpp')
SRC_FILES+=('RobotCommand.cpp')
SRC_FILES+=('AutonoscriptReader.cpp')
SRC_FILES+=('RobotCommandCollection.cpp')
SRC_FILES+=('AutonoScriptInput.h')

# Dynamic Variables
BASE_DIR="$(dirname "${0}")"
SRC_DIR="${BASE_DIR}/${SRC_DIR}"
BIN_DIR="${BASE_DIR}/${BIN_DIR}"

# Base Command
BUILD_CMD=("${COMPILER}")

# Sets Debug
BUILD_CMD+=(-g)

# Adds Source Files
for src_file in ${SRC_FILES[@]}; do
  BUILD_CMD+=(\"${SRC_DIR}/${src_file}\")
done

# Sets Binary
BUILD_CMD+=(-o \"${BIN_DIR}/${OUTPUT_NAME}\")

echo ${BUILD_CMD[@]}
eval ${BUILD_CMD[@]}
