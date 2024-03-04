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

## status2d
使用status2d补丁配合xsetroot在statusbar自定义显示系统相关信息，自定义脚本需要赋予755权限
```shell
chmod 755 statusbar.sh
```
## overview
全局预览功能fork自yaocccc<https://github.com/yaocccc/dwm>

## lunar-date
添加农历显示，需要安装`lunar-date`
```shell
yay -S lunar-date
```
如果农历显示拼音，检查是否安装了`lunar-date.mo`文件:
```shell
/usr/share/locale/zh_CN/LC_MESSAGES/lunar-date.mo
/usr/share/locale/zh_HK/LC_MESSAGES/lunar-date.mo
/usr/share/locale/zh_TW/LC_MESSAGES/lunar-date.mo
```
并将luanr-date.mo文件复制到`/usr/share/locale/en_US/LC_MESSAGES`目录下
```shell
cp /usr/share/locale/zh_CN/LC_MESSAGES/lunar-date.mo /usr/share/locale/en_US/LC_MESSAGES
```

