# Created by MisterBianco

setup() {
    echo "Snicker Setup"
    echo -ne "=============\r\n"
    echo -ne "$1\r"
}

progressbar() {
    # Progress on wait for update
    sleep 3
    echo -ne "[ ###             ] (20%)\r"
    sleep 1
    echo -ne "[ ######          ] (40%)\r"
    sleep 1
    echo -ne "[ #########       ] (60%)\r"
    sleep 1
    echo -ne "[ ############    ] (80%)\r"
    sleep 1
    echo -ne "[ ############### ] (100%)\r"
}

setup "Updating system"

progressbar

echo -ne "sudo apt-get update running...      \r"
sudo apt-get update -qq

echo -ne "Installing libtins dependencies... \r"
sudo apt-get install libpcap0.8 openssl cmake -y
# valgrind

sleep 2
clear

echo "Snicker Setup"
echo -ne "=============\r\n"
echo -ne "Installing libtins\r"

progressbar

git clone https://github.com/mfontanini/libtins.git
cd libtins

mkdir build
cd build

cmake ../ -DLIBTINS_ENABLE_CXX11=1
make

sudo make install
sudo ldconfig
clear

echo "Snicker Setup"
echo -ne "=============\r\n"
echo "Cleaning up libtins"

cd ../../
rm -rf libtins/
clear

echo "Snicker Setup"
echo -ne "=============\r\n"
echo "Download and install gtests"

wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
tar xf release-1.8.0.tar.gz

cd googletest-release-1.8.0

cmake -DBUILD_SHARED_LIBS=ON .
make
sudo make install

sudo ldconfig
clear

echo "Snicker Setup"
echo -ne "=============\r\n"
echo "Snicker is ready. (In theory that is)."
