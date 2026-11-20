#!/usr/bin/env bash
# Installs versefetch for the current user.
#   binary   -> $PREFIX/bin/versefetch                 (default PREFIX: ~/.local)
#   database -> ${XDG_DATA_HOME:-~/.local/share}/versefetch/bible.tsv
# The database location matches the default versefetch looks in at runtime.
# Uninstall with --uninstall.
set -euo pipefail

cd "$(dirname "$0")"

PREFIX="${PREFIX:-$HOME/.local}"
BIN_DIR="$PREFIX/bin"
if [[ "${XDG_DATA_HOME:-}" == /* ]]; then
	DATA_DIR="$XDG_DATA_HOME/versefetch"
else
	DATA_DIR="$HOME/.local/share/versefetch"
fi

if [[ "${1:-}" == "--uninstall" ]]; then
	rm -f "$BIN_DIR/versefetch"
	rm -rf "$DATA_DIR"
	echo "versefetch uninstalled."
	exit 0
fi

command -v forge >/dev/null || { echo "error: forge not found in PATH" >&2; exit 1; }
[[ -f bible.tsv ]] || { echo "error: bible.tsv not found" >&2; exit 1; }

echo "==> Building (release)"
forge build --release

BUILT=".forge/bin/release/versefetch.bin"
[[ -x "$BUILT" ]] || { echo "error: build output $BUILT missing" >&2; exit 1; }

echo "==> Installing to $BIN_DIR and $DATA_DIR"
mkdir -p "$BIN_DIR" "$DATA_DIR"
install -m 755 "$BUILT" "$BIN_DIR/versefetch"
install -m 644 bible.tsv "$DATA_DIR/bible.tsv"

echo "==> Installed versefetch"
case ":$PATH:" in
	*":$BIN_DIR:"*) ;;
	*) echo "note: $BIN_DIR is not in your PATH; add it to use 'versefetch'." ;;
esac
