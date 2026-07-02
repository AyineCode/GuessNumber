#!/bin/bash
set -e

# GuessNumber uninstall script

INSTALL_BIN_DIR="${HOME}/.local/bin"
INSTALL_DATA_DIR="${HOME}/.local/share/.guessnumber"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "${SCRIPT_DIR}")"

echo "Deleting user data..."
if cd "${INSTALL_DATA_DIR}" >/dev/null 2>&1; then
    rm -rf * || true
fi
echo "Done."