FROM gcc:latest
LABEL authors="vincentzhao"

COPY main.cpp /usr/src/dockerapp/
WORKDIR /usr/src/dockerapp

RUN g++ -o main main.cpp

CMD ["./main"]