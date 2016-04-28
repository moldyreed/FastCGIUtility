# fastcginetworkconfig

##Depencies

fcgi >= 2.4  
dbus >= 1.10  
gcc >= 5.1  

##Building
```
mkdir build
cd build
cmake ..
make
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
