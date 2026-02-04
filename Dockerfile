FROM debian:stable-slim

# Necessary pachets for build + SDL2 + SDL2_ttf
RUN apt-get update && apt-get install -y \
  build-essential \
  libsdl2-dev \
  libsdl2-ttf-dev \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

RUN make

CMD ["./tests"]
