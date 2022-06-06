FROM ghcr.io/armmbed/mbed-os-env
RUN mkdir workspace
COPY . /workspace
WORKDIR /workspace
RUN mbed-tools deploy
RUN mbed-tools compile -t GCC_ARM -m NUCLEO_F767ZI