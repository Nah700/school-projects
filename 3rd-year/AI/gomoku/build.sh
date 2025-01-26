wine python -m PyInstaller --noconfirm --onefile pbrain-gomoku-ai
mv dist/pbrain-gomoku-ai.exe .
rm *.spec
rm -rf build
rm -rf dist
