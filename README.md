# suckless
个人自用dmenu dwm slock slstatus st配置

## slock troubleshooting
If you get this error `slock: getgrnam nogroup: group entry not found`, then you might want to apply this:
```shell
sed -i 's|static const char \*group = "nogroup";|static const char *group = "nobody";|' config.def.h
sed -ri 's/((CPP|C|LD)FLAGS) =/\1 +=/g' config.mk
``` 
## i3lock
为使锁屏界面显示自定义脚本图案，需要安装`i3lock-color`
```shell
pacman -S i3lock-color
```
自定义脚本需要赋予755权限
```shell
chmod 755 lock.sh
```
i3lock主题配置文件fork自gxt_kt<https://github.com/gxt-kt/dwm/blob/master/i3lock/lock.sh>