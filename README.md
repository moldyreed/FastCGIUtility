# FastCGIUtility

##Dependencies

fcgi >= 2.4  
dbus >= 1.10  
gcc >= 5.1  
networkmanager >= 1.0

##Building
```
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
