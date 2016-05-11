# FastCGIUtility
Cuncurrent utility returns network settings in json format through FastCGI written in C++11. Network settings provided by NetworkManager via dbus. 

##Dependencies

fcgi >= 2.4  
dbus >= 1.10  
gcc >= 5.1  
pkg-config  
networkmanager >= 1.0  
cmake >= 2.8

##Building
```
git clone https://github.com/sickevilfuck/FastCGIUtility.git --recursive
cd FastCGIUtility
mkdir build
cd build
cmake ..
make
```

##Start
Use parameter -n to define thread number
```
./fastcgi -n4
```
Do not forget to start DBus, NetworkMananger and nginx services!

## Usage
curl request example  

```
curl "localhost:9001/config"
{
    "gateway": "192.168.1.1",
    "ip": "192.168.1.212",
    "netmask": "255.255.252.0"
}
```

wildcard request example  

```
curl "localhost:9001/v1/*/config"
{
    "gateway": "192.168.1.1",
    "ip": "192.168.1.212",
    "netmask": "255.255.252.0"
}
```

Tested with following nginx config
```
server { 
    server_name localhost; 
    listen 9001;    

    location / { 
        fastcgi_pass 127.0.0.1:9000; 
        include fastcgi_params; 
    }   
}
```
