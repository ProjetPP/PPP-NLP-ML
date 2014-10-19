wget http://attempto.ifi.uzh.ch/site/downloads/files/clex-6.0-080806.zip
#Specification : http://attempto.ifi.uzh.ch/site/docs/ace_lexicon.html

mkdir vienneCL
cd vienneCL
wget http://downloads.sourceforge.net/project/viennacl/1.5.x/ViennaCL-1.5.2.tar.gz?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fviennacl%2F&ts=1413732515&use_mirror=cznic -O ViennaCL-1.5.2.tar.gz
gunzip ViennaCL-1.5.2.tar.gz
tar -xf ViennaCL-1.5.2.tar
cmake . -DENABLE_OPENCL=0
make
sudo make install
cd ..
rm vienneCL -r -f
