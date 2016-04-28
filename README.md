# fastcginetworkconfig



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
