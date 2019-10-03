FROM ubuntu:16.04 as test_redis_pull
RUN apt update && apt upgrade -y
RUN apt install python3.5 python3-dev python3-pip -y
RUN pip3 install redis

WORKDIR /src
COPY pull.py .
CMD ["python3", "-u", "pull.py"]