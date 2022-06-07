FROM ghcr.io/armmbed/mbed-os-env:master-latest
COPY . /
RUN mbed-tools deploy
RUN mbed-tools compile -t GCC_ARM -m NUCLEO_F767ZI