FROM gcc:11.2.0


RUN apt-get -qq update \
    && apt-get -qq install --no-install-recommends openssh-server \
    && apt-get -qq install --no-install-recommends sudo \
    && apt-get -qq install --no-install-recommends cmake \
    && apt-get -qq install --no-install-recommends rsync \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# setup ssh for use ubuntu, password 1234
RUN useradd -rm -d /home/ubuntu -s /bin/bash -g root -G sudo -u 1000 ubuntu 
RUN  echo 'ubuntu:1234' | chpasswd
RUN service ssh start
EXPOSE 22

# install google test
WORKDIR /usr/src/libraries
# ENV HTTP_PROXY=http://host.docker.internal:7890
# ENV HTTPS_PROXY=http://host.docker.internal:7890
RUN git config --global https.proxy "127.0.0.1:7890"
RUN git config --global http.proxy "127.0.0.1:7890"
# ENV http_proxy=http://127.0.0.1:7890
# ENV https_proxy=https://127.0.0.1:7890
# RUN echo $http_proxy
# RUN curl -x http://127.0.0.1:7890 https://github.com/google/googletest.git
RUN git clone --depth=1 -b main https://github.com/google/googletest.git
WORKDIR /usr/src/libraries/googletest/build
RUN cmake .. \
    && make \
    && make install

# build the project
WORKDIR /usr/src/app
COPY . .
RUN rm -rf build
RUN mkdir build
WORKDIR /usr/src/app/build
RUN cmake ..
RUN make

# CMD ["/usr/sbin/sshd","-D"]
CMD ["./main"]
