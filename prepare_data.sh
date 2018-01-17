# Download and extract data
wget https://www.dropbox.com/s/a40dhhfchojyf0c/consenus_input.zip?dl=0
unzip consenus_input.zip
rm consenus_input.zip

# Install graphmap
git clone https://github.com/isovic/graphmap.git
cd graphmap
make modules
make
cd ..