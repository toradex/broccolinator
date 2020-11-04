FROM sha256:3f704a35b280b7019b2dceca976e596334832323e455f28b26d8af360a9c673f

# add automake/autoconf to our base SDK container
RUN apt-get update && apt-get install -y \
    --no-install-recommends --no-install-suggests \
    pkg-config cmake curl\
    && apt-get clean && apt-get autoremove \
    && rm -rf /var/lib/apt/lists/*

# This is required to allow regular user inside the container to access docker socket
RUN addgroup docker && groupmod --non-unique --gid 0 docker && adduser torizon docker
