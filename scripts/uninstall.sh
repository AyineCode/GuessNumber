#!/bin/bash
set -e

# GuessNumber uninstall script

INSTALL_BIN_DIR="${HOME}/.local/bin"
INSTALL_DATA_DIR="${HOME}/.local/share/.guessnumber"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "${SCRIPT_DIR}")"

echo "Uninstalling guessNumber..."

cd "${PROJECT_DIR}"
make clean >/dev/null 2>&1 || true

rm "${INSTALL_BIN_DIR}/guessnumber" || true
echo "Done."