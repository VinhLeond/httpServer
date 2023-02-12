FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN mkdir -p /home/
RUN apt-get update && apt install -y tzdata;

RUN \
# Tools
apt-get install -y --no-install-recommends build-essential cmake apt-utils doxygen \
  g++ git octave python-dev python-setuptools wget mlocate openssl curl;

RUN \
# Libraries
apt-get install -y --no-install-recommends ann-tools libann-dev \
libassimp-dev libavcodec-dev libavformat-dev libeigen3-dev libfaac-dev \
libflann-dev libfreetype6-dev liblapack-dev libglew-dev libgsm1-dev \
libmpfi-dev  libmpfr-dev liboctave-dev libode-dev libogg-dev libpcre3-dev  \
libqhull-dev libswscale-dev libtinyxml-dev libvorbis-dev libx264-dev  \
libxml2-dev libxvidcore-dev libbz2-dev pkg-config libsoqt520-dev libccd-dev libcollada-dom2.4-dp-dev liblog4cxx-dev libminizip-dev octomap-tools;

RUN apt reinstall ca-certificates && update-ca-certificates

RUN \
# Boost
# Clean old boost
rm -rf /usr/include/boost;\
cd / && wget https://boostorg.jfrog.io/artifactory/main/release/1.72.0/source/boost_1_72_0.tar.gz;\
tar xvf boost_1_72_0.tar.gz && rm boost_1_72_0.tar.gz;\
cd boost_1_72_0;\
./bootstrap.sh --prefix=/usr/;\
./b2 install;\
rm -rf ../boost_1_72_0

RUN \
# FCL - The Flexible Collision Library
cd / && git clone https://github.com/flexible-collision-library/fcl;\
cd fcl; git reset --hard 0.5.0;\
mkdir build; cd build;\
cmake .. -DFCL_BUILD_TESTS=OFF;\
make -j `nproc`;\
make install;\
cd / && rm -rf ../fcl

RUN \
# OpenSceneGraph
cd / && git clone https://github.com/openscenegraph/OpenSceneGraph.git;\
cd OpenSceneGraph;\
mkdir build; cd build;\
cmake -DDESIRED_QT_VERSION=4 ..;\
make -j `nproc`;\
make install;\
make install_ld_conf;\
cd / && rm -rf ../OpenSceneGraph

RUN \
# Python
  apt-get install -y --no-install-recommends python2;\
  curl https://bootstrap.pypa.io/pip/2.7/get-pip.py --output get-pip.py;\
  python2 get-pip.py;\
  pip install ipython h5py numpy scipy wheel pyopengl;

RUN \
# RapidJSON
cd / && git clone https://github.com/Tencent/rapidjson.git;\
cd rapidjson;\
mkdir build && cd build;\
cmake .. && make -j `nproc` &&  make install;\
cd / && rm -rf ../rapidjson

# openRave
RUN cd /home/ && git clone https://github.com/VinhLeond/openrave.git;\
cd /home/openrave && git checkout feature/building_success;\
mkdir build && cd build;\
cmake -DODE_USE_MULTITHREAD=ON -DOSG_DIR=/usr/local/lib64/ \
	-DUSE_PYBIND11_PYTHON_BINDINGS:BOOL=FALSE 			   \
	-DBoost_NO_BOOST_CMAKE=1 ..;\
make -j `nproc`;\
make install;\
cd /home && rm -rf openrave;

RUN \
cd /home/ && git clone https://github.com/VinhLeond/httpServer.git;\
cd httpServer && ./build.sh 1;

CMD "./home/httpServer/build/src/main"
EXPOSE 9000