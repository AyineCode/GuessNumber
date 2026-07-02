#!/bin/bash
set -e

# GuessNumber install script

INSTALL_BIN_DIR="${HOME}/.local/bin"
INSTALL_DATA_DIR="${HOME}/.local/share/.guessnumber"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "${SCRIPT_DIR}")"
MAKE_CXX="g++"

SHELL_NAME="$(basename "$SHELL")"
SH_PROFILE="${HOME}/.profile"
case "${SHELL_NAME}" in
bash)
    SH_PROFILE="${HOME}/.profile"
    ;;
zsh)
    SH_PROFILE="${HOME}/.zprofile"
    ;;
*)
    SH_PROFILE="{HOME}/.profile"
    ;;
esac

HAS_LOCAL_BIN=0
test -d "${INSTALL_BIN_DIR}" || HAS_LOCAL_BIN="$?"

echo "===== GuessNumber Installer ====="
echo ""

echo "[1/5] Checking for C++ compiler..."
if command -v g++ >/dev/null 2>&1; then
    echo "  Found g++: $(g++ --version | head -1)"
elif command -v clang++ >/dev/null 2>&1; then
    echo "  Found clang++: $(clang++ --version | head -1)"
    MAKE_CXX="clang++"
else
    echo -e "  \033[0;31mError: No C++ compiler found. Install g++ or clang++.\033[0m"
    echo "  For example, you can:"
    echo "    sudo apt install g++"
    exit 1
fi

echo "[2/5] Checking for nlohmann/json.hpp..."
JSON_HPP="${PROJECT_DIR}/third_party/nlohmann/json.hpp"
if [ -f "${JSON_HPP}" ]; then
    echo "  Found."
else
    echo "  Not found, downloading..."
    mkdir -p "$(dirname "$JSON_HPP")"
    if command -v wget >/dev/null 2>&1; then
        wget -q https://github.com/nlohmann/json/releases/latest/download/json.hpp -O "$JSON_HPP"
    elif command -v curl >/dev/null 2>&1; then
        curl -sL https://github.com/nlohmann/json/releases/latest/download/json.hpp -o "$JSON_HPP"
    else
        echo "  \033[0;31mError: need wget or curl to download json.hpp. Please install one.\033[0m"
        exit 1
    fi
    echo "  Downloaded."
fi

echo "[3/5] Building the project..."
cd "${PROJECT_DIR}"
make clean >/dev/null 2>&1 || true
make CXX="${MAKE_CXX}" BUILD_TYPE=release >"${PROJECT_DIR}/temp_build.log" 2>&1
if [ $? -ne 0 -a $? -ne 1 ]; then
    echo "  \033[0;31mError: Failed to build guessnumber. See more details in temp_build.log\033[0m"
    exit 1
fi
rm "${PROJECT_DIR}/temp_build.log"
echo "  Build complete."

echo "[4/5] Installing binary to ${INSTALL_BIN_DIR}..."
mkdir -p "${INSTALL_BIN_DIR}"
if [ -f "${INSTALL_BIN_DIR}/guessnumber" ]; then
    echo "  The binary is already installed, skipping."
else
    install -m 755 build/bin/guessnumber "${INSTALL_BIN_DIR}/guessnumber"
    echo "  Installed."
fi

echo "[5/5] Setting up data directory..."
mkdir -p "${INSTALL_DATA_DIR}"
if [ -f "${INSTALL_DATA_DIR}/config.json" ]; then
    echo "  Config already exists, skipping."
else
    install -m 755 data/config_example.json "${INSTALL_DATA_DIR}/config.json"
    echo "  Created default config at ${INSTALL_DATA_DIR}/config.json"
fi

if [ -f "${INSTALL_DATA_DIR}/history.json" ]; then
    echo "  History already exists, skipping."
else
    install -m 755 data/history_example.json "${INSTALL_DATA_DIR}/history.json"
    echo "  Created default history at ${INSTALL_DATA_DIR}/history.json"
fi

echo ""
echo -e "\033[0;32m===== Installation successful! =====\033[0m"
echo ""
echo "You can now run: guessnumber"
echo "Or with options: guessnumber --help"
echo ""
echo "Data stored in: ${INSTALL_DATA_DIR}"
echo ""

source "${SH_PROFILE}" >/dev/null 2>&1 || true
if ! echo "${PATH}" | grep -q "${INSTALL_BIN_DIR}"; then
    $(echo -e "if [ -d \"${INSTALL_BIN_DIR}\" ] ; then\nexport PATH=\"${INSTALL_BIN_DIR}:\$PATH\"\nfi\n" >> "${SH_PROFILE}") >/dev/null 2>&1 || true
    source "${SH_PROFILE}" >/dev/null 2>&1 || true
    if ! echo "${PATH}" | grep -q "${INSTALL_BIN_DIR}"; then
        echo -e "\033[0;33mWARNING: ${INSTALL_BIN_DIR} is not in your PATH.\033[0m"
        echo "Add this to your ~/.bashrc or ~/.zshrc:"
        echo "  export PATH=\"${INSTALL_BIN_DIR}:\$PATH\""
        echo ""
        HAS_LOCAL_BIN=0
    else
        echo -e "\033[0;33mAdded ${INSTALL_BIN_DIR} PATH adder to ${SH_PROFILE}.\033[0m"
        echo ""
    fi
fi

if [ "${HAS_LOCAL_BIN}" -ne 0 ]; then
    echo -e "\033[0;33mNOTICE: This is you first time install sth in ${INSTALL_BIN_DIR}.\033[0m"
    echo -e "\033[0;33mPlease run the following command:\033[0m"
    echo "    source ${SH_PROFILE}"
fi