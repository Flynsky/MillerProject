FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    openssh-server \
    sudo \
    curl \
    wget \
    git \
    make \
    build-essential \
    python3 \
    python3-pip \
    python3-serial \
    gcc-riscv64-unknown-elf \
    binutils-riscv64-unknown-elf \
    picolibc-riscv64-unknown-elf \
    libusb-1.0-0 \
    libftdi1-2 \
    libhidapi-hidraw0 \
    libgpiod2t64 \
    openfpgaloader \
    tio \
    minicom \
    tmux \
    nano \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install oss-cad-suite (includes yosys with slang plugin, nextpnr-himbaechel for GateMate, gmpack, etc.)
RUN wget -q https://github.com/YosysHQ/oss-cad-suite-build/releases/download/2026-10-31/oss-cad-suite-linux-x64-20261031.tgz -O /tmp/oss-cad-suite.tgz && \
    tar -xzf /tmp/oss-cad-suite.tgz -C /opt && \
    rm /tmp/oss-cad-suite.tgz

ENV PATH="/opt/oss-cad-suite/bin:${PATH}"

RUN echo 'export PATH="/opt/oss-cad-suite/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$PATH"' > /etc/profile.d/oss-cad-suite.sh

RUN ln -s /usr/bin/openFPGALoader /usr/local/bin/openfpgaloader

RUN curl -fsSL https://code-server.dev/install.sh | sh

RUN (userdel -r ubuntu 2>/dev/null || true) && \
    useradd -m -s /bin/bash -u 1000 -G dialout,sudo miller && \
    echo 'miller ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers && \
    echo 'export PATH="/opt/oss-cad-suite/bin:$PATH"' >> /home/miller/.bashrc

RUN mkdir -p /var/run/sshd /home/miller/.ssh && \
    chmod 700 /home/miller/.ssh && \
    chown -R miller:miller /home/miller/.ssh

COPY flash-fpga.sh /usr/local/bin/flash-fpga
RUN chmod +x /usr/local/bin/flash-fpga

COPY read-uart.py /usr/local/bin/read-uart
RUN chmod +x /usr/local/bin/read-uart

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

WORKDIR /workspace
EXPOSE 8080 22

ENTRYPOINT ["/entrypoint.sh"]
