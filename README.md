# redis_fifo_clients
Example of using redis fifo client to implement message queue. All will run on docker.


# Requirements
* Docker:
> sudo apt install docker -y
* Docker Compose
```
    sudo apt-get remove docker-compose
    sudo curl -L "https://github.com/docker/compose/releases/download/1.23.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
    sudo chmod +x /usr/local/bin/docker-compose
    sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
```


# Test result:
* `python-push` + `python-pull` (using redis install from pip)) => delay about 750 - 1000 micro seconds
* `c++-push` + `c++-pull` (using hiredis) => delay about 400-550 micro seconds