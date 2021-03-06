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
SRC_FILES+=('AutonoScriptInput.cpp')
SRC_FILES+=('AutonoScriptInputReader.cpp')
SRC_FILES+=('AutonoScriptManager.cpp')
SRC_FILES+=('FieldGenerator.cpp')
SRC_FILES+=('FieldPositions.cpp')
SRC_FILES+=('FieldDefinition.cpp')
SRC_FILES+=('FacingRegulator.cpp')
SRC_FILES+=('FacingPositionalEvaluator.cpp')
SRC_FILES+=('FieldPath.cpp')
SRC_FILES+=('FieldPathGenerator.cpp')
SRC_FILES+=('FieldOutputGenerator.cpp')
SRC_FILES+=('FieldConsoleOutputGenerator.cpp')
SRC_FILES+=('FieldCsvOutputGenerator.cpp')
SRC_FILES+=('FieldGraphicsOutputGenerator.cpp')

# Dynamic Variables
BASE_DIR="$(dirname "${0}")"
SRC_DIR="${BASE_DIR}/${SRC_DIR}"
BIN_DIR="${BASE_DIR}/${BIN_DIR}"

# Base Command
BUILD_CMD=("${COMPILER}")

# Sets Debug
BUILD_CMD+=(-g)
BUILD_CMD+=(-std=c++11)

# Adds Source Files
for src_file in ${SRC_FILES[@]}; do
  BUILD_CMD+=(\"${SRC_DIR}/${src_file}\")
done

# Sets Binary
BUILD_CMD+=(-o \"${BIN_DIR}/${OUTPUT_NAME}\")

# Set Linking Options
BUILD_CMD+=($(pkg-config --cflags --libs cairo))


[ ! -d "${BIN_DIR}" ] && mkdir -pv "${BIN_DIR}"

echo ${BUILD_CMD[@]}
eval ${BUILD_CMD[@]}
