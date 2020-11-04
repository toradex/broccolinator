FROM torizon/arm64v8-debian-base:buster

# Make sure we don't get notifications we can't answer during building.
ENV DEBIAN_FRONTEND="noninteractive"

# commands that should be run before installing packages (ex: to add a feed or keys)

# your regular RUN statements here
# Install required packages
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    python3-minimal \
    python3-pip \
    python3-setuptools \
    \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --upgrade pip

COPY setup.sh /setup.sh
COPY cleanup.sh /cleanup.sh
COPY requirements.txt /requirements.txt
COPY tflite_runtime-2.1.0.post1-cp37-cp37m-linux_aarch64.whl /tflite_runtime-2.1.0.post1-cp37-cp37m-linux_aarch64.whl

WORKDIR /
RUN chmod a+x /setup.sh &&\
    chmod a+x /cleanup.sh &&\
    /setup.sh debug &&\
    pip install -r /requirements.txt &&\
    /cleanup.sh debug

COPY work/broccolinator-ml-tflite /broccolinator-ml-tflite

# commands that should be run after all packages have been installed (RUN/COPY/ADD)





USER torizon
WORKDIR /broccolinator-ml-tflite

CMD /usr/bin/python3 main.py 

# commands that will run on the target (ENTRYPOINT or CMD)

