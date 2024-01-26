# suckless
个人自用dmenu dwm slock slstatus st配置

## slock troubleshooting
If you get this error `slock: getgrnam nogroup: group entry not found`, then you might want to apply this:
```shell
sed -i 's|static const char \*group = "nogroup";|static const char *group = "nobody";|' config.def.h
sed -ri 's/((CPP|C|LD)FLAGS) =/\1 +=/g' config.mk

``` 
