sudo dpkg --add-architecture i386
sudo apt update
sudo apt install -y software-properties-common wget
wget -nc https://dl.winehq.org/wine-builds/winehq.key
sudo apt-key add winehq.key
sudo add-apt-repository 'deb https://dl.winehq.org/wine-builds/ubuntu/ jammy main'
sudo apt update
sudo apt install --install-recommends winehq-stable
wine --version

