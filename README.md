# RFIDAccessControl

## How to build

### Install required libraries

#### libnfc

```
git clone https://github.com/nfc-tools/libnfc.git
cd libnfc/
autoreconf -vis
./configure --prefix=/usr
make
sudo make install
```

#### libfreefare
```
git clone https://github.com/nfc-tools/libfreefare.git
cd libfreefare/
autoreconf -vis
./configure --prefix=/usr
make
sudo make install
```

