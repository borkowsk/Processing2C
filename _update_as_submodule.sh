#/bin/bash
# @date 2026-04-28 (last modification)
# ==============================
#Ten skrypt aktualizuje ten projekt zainstalowany jako submodul innego repozytorium

cd ..
git submodule update --remote --merge --recursive
git add .
git commit -m "Aktualizacja submodułu do najnowszej wersji"
git push
