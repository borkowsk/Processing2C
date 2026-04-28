#/bin/bash
# @date 2026 (last modification)
# ==============================
#Ten skrypt aktualizuje SymShellLight zainstalowany jako submodul innej bublioteki

cd ..
git submodule update --remote --merge --recursive
git add .
git commit -m "Aktualizacja submodułu do najnowszej wersji"
git push
