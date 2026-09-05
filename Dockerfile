FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    qtbase5-dev \
    qtbase5-dev-tools \
    qtdeclarative5-dev \
    qtdeclarative5-dev-tools \
    qtlocation5-dev \
    qtpositioning5-dev \
    qml-module-qtquick2 \
    qml-module-qtquick-controls2 \
    qml-module-qtlocation \
    qml-module-qtpositioning \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libx11-xcb1 \
    libxcb-xinerama0 \
    libxcb-cursor0 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release

RUN cmake --build build -j$(nproc)

ENV QT_X11_NO_MITSHM=1

CMD ["./build/tlog_viewer"]
