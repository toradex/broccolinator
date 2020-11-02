FROM sha256:c5756d6e8bf68ed2256339deb063935cdba02d49f52378087f36cd87f9f53d45

# This is required to allow regular user inside the container to access docker socket
RUN addgroup docker && groupmod --non-unique --gid 0 docker && adduser torizon docker
