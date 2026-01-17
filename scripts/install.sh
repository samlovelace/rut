#!/usr/bin/env bash

set -euo pipefail

# ---- Configuration ----
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
INSTALL_PREFIX="$HOME/.local"

echo "==> Installing rut"
echo "    Source:  $PROJECT_ROOT"
echo "    Build:   $BUILD_DIR"
echo "    Prefix:  $INSTALL_PREFIX"

# ---- Ensure dependencies exist ----
command -v cmake >/dev/null || {
    echo "cmake not found"; exit 1;
}

# ---- Configure ----
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX"

# ---- Build ----
cmake --build . --parallel

# ---- Install ----
cmake --install .

echo "==> rut installed successfully to $INSTALL_PREFIX"
