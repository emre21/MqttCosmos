FROM ubuntu:latest

WORKDIR /app

RUN apt-get update && apt-get install -y

RUN apt-get install -y libboost-all-dev \ 
    libgtest-dev
RUN apt-get install -y libspdlog-dev
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
COPY . .

#RUN mkdir build && cd build
RUN cmake .
RUN make
CMD [ "./MqttCosmos" ]