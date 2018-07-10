# Docker Cheat Sheet

These are some docker commands that I have found useful as I am creating my docker image for development.

The way that I create the Docker container for elasticsearch will need to use `systemctl` and some other commands that you need systemd for, so I made a

Run the docker container with systemd enabled

`docker run -itd --privileged --name=yourName local/c7-systemd`

Attatch the the shell of the running docker container

`docker exec -i -t loving_heisenberg /bin/bash #by Name`

Commit the changes to a docker container to be an image:

[Official Docker on Commit](https://docs.docker.com/engine/reference/commandline/commit/)

`docker commit -a "Ben Hoffman benjafriend@gmail.com" 0e022f267ec7 local/scrutiny:latest`


Save a current docker image to a tar ball that can be used by others:

`docker save --output latestversion-1.0.0.tar dockerregistry/latestversion:1.0.0`

Load in said tar ball from above onto your local machine:

`docker load --input latestversion-1.0.0.tar`


Use these commands to get some simple net tools in the centos docker
```
yum install -y net-tools

yum install -y iproute
``


My installation script:
```
##################################### Install Java ##################################
yum install wget -y

cd /opt
wget --no-cookies --no-check-certificate --header "Cookie: gpw_e24=http%3A%2F%2Fwww.oracle.com%2F; oraclelicense=accept-securebackup-cookie" "http://download.oracle.com/otn-pub/java/jdk/8u102-b14/jre-8u102-linux-x64.rpm"
rpm -Uvh jre-8u102-linux-x64.rpm
rm -rf jre-8u102-linux-x64.rpm
yum install java-devel -y


##################################### Install/Setup Elasticsearch #####################################
 rpm --import https://artifacts.elastic.co/GPG-KEY-elasticsearch

echo '[elasticsearch-5.x]
name=Elasticsearch repository for 5.x packages
baseurl=https://artifacts.elastic.co/packages/5.x/yum
gpgcheck=1
gpgkey=https://artifacts.elastic.co/GPG-KEY-elasticsearch
enabled=1
autorefresh=1
type=rpm-md
' |  tee /etc/yum.repos.d/elasticsearch.repo
 yum -y install elasticsearch

sed -i 's/#network.host: 192.168.0.1/network.host: 0.0.0.0/g' /etc/elasticsearch/elasticsearch.yml

systemctl enable elasticsearch
systemctl start elasticsearch

##################################### Install/Setup Kibana #####################################
echo '[kibana-4.4]
name=Kibana repository for 4.4.x packages
baseurl=http://packages.elastic.co/kibana/4.4/centos
gpgcheck=1
gpgkey=http://packages.elastic.co/GPG-KEY-elasticsearch
enabled=1
' |  tee /etc/yum.repos.d/kibana.repo

 yum -y install kibana

 vi /opt/kibana/config/kibana.yml
## In the kibana config file, find the line that specifies server.host and replace the ip with "localhost"
## server.host: "localhost"


 systemctl start kibana
 chkconfig kibana on


##################################### Install/Setup Nginx #####################################
yum -y install epel-release
yum -y install nginx httpd-tools
 htpasswd -c /etc/nginx/htpasswd.users kibanaadmin
cp /etc/nginx/nginx.conf /etc/nginx/nginx.conf.bak

# Delete server block  in default config
sed -i -e '38,87d' /etc/nginx/nginx.conf

mkdir /etc/nginx/conf.d

  cat > /etc/nginx/conf.d/kibana.conf << EOF
server {
    listen 80;
    server_name example.com;
    auth_basic "Restricted Access";
    auth_basic_user_file /etc/nginx/htpasswd.users;
    location / {
        proxy_pass http://localhost:5601;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_cache_bypass $http_upgrade;
    }
}
EOF

mkdir /etc/nginx/ssl

 openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt

 systemctl start nginx
 systemctl enable nginx
 setsebool -P httpd_can_network_connect 1


##################################### Install/Setup Logstash #####################################
echo '[logstash-5.x]
name=Elastic repository for 5.x packages
baseurl=https://artifacts.elastic.co/packages/5.x/yum
gpgcheck=1
gpgkey=https://artifacts.elastic.co/GPG-KEY-elasticsearch
enabled=1
autorefresh=1
type=rpm-md
' |  tee /etc/yum.repos.d/logstash.repo

 yum -y install logstash

systemctl restart logstash
systemctl enable logstash



```
