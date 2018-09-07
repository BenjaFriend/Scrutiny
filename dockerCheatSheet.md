# Docker and Scrutiny

## How is Docker being used in this project?

I am using Docker as a quick and easy way for me to setup ELK stack instances so that I can
test my library easily. You don't have to use Docker to use this library, but it is a great
starting point for a lot of projects if you want to test out your settings locally or
without spending money on server instances.

## Docker Compose

[Docker composer] (https://docs.docker.com/compose/) is a tool to running multi-container Docker
apps, which works pretty well with Elasticsearch, Logstash, and Kibana. Basically, it is a quick and easy way to have docker containers interface with one another so you can separate the functionality of your app. I am using [this](https://github.com/deviantony/docker-elk) setup by deviantony as a starting point.
