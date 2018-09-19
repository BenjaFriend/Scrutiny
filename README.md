# Scrutiny

Scrutiny is a library that uses sockets and the Elasticsearch REST API
in C++ to provide a simple interface between a game and the ELK stack.

Scrutiny gives the user all the power of Elasticsearch while doing all formatting
and web requests for them.  

I believe that every game developer should have access to the analytics of their
game, not just in terms of performance, but also custom reporting.

Data like what level the average player is when they complete an objective,
how fast players complete levels, or what weapons are equipped most often.
All of this can be reported quickly and easily with Scrutiny, and visualized
with the power of Kibana.

### <span style="color: orange; font-weight: bold;">Under Construction!</span>

Scrutiny is currently being developed and is incomplete! The goal is to have
the core of the project up and running and have some examples in Unity
by October 5, 2018.

## Why is this interesting?

Scrutiny will allow developers to easily implement the ELK _(Elasticsearch,
Logstash, Kibana)_ stack into their games by providing an interface layer
that will automatically format the data for the REST API from Elasticsearch.

There are other options available for interfacing with Elasticsearch, but many
of them are barebones still require the user to have a pretty good understanding
of how the ELK stack works. My goal is to make this library as accessible as
possible to any developer with a small level of abstraction.

The library will feature serialization of basic types used in common game
engines like Unity and Unreal, as well as provide more advanced options for
sending custom ELK requests.

## Documentation

If you want to see the source code documentation, then you can check it out
on the Git Pages for the project: https://benjafriend.github.io/Scrutiny/

## Quick Start Guide

### Setting up your ELK Stack

There are a ton of options for setting up your ELK stack, which is fantastic.
If you want a quick-start option for your stack, however, I have forked a
[docker-compose ELK stack here](https://github.com/BenjaFriend/docker-elk) to
make it easier for you.   

### Code Examples

Here are some guides for how to use Scrutiny in both Unity and Unreal, along
with some code examples!

#### Unity _(Coming Soon)_

Simply import the Unity package into your project and add the C# script to your
game somewhere, and you are off to the races!

```C#
// Coming Soon
```

#### Unreal Engine _(Coming Soon)_

```C#
// Coming Soon
```

#### Useful ELK links

If you want to learn more about how this library works or more about Elasticsearch,
I have comprised some links and guides that you may find useful!

* [Index API reference](https://www.elastic.co/guide/en/elasticsearch/reference/current/docs-index_.html)
* [List All Indices Command](https://www.elastic.co/guide/en/elasticsearch/reference/current/_list_all_indices.html)
