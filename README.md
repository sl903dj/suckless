# suckless
个人自用dmenu dwm slock slstatus st配置

>更新一下分支说明
>- `master` 分支是最早期配置的，使用slstatus显示状态栏信息，alacritty作为默认终端，i3lock-color作为锁屏工具，rofi作为程序选择器，已停止更新。
>- `status2d` 分支是在`master`分支上使用status2d替换slstatus，搭配`dwm/scripts/statusbar.sh/`显示状态栏信息。
>- `overview` 分支是在`status2d`分支上添加了全局预览功能，方便查看所有打开的程序。
>- `statuscmd` 分支是在`overview`分支上添加了statuscmd补丁，并换用[dmwblocks-async](https://github.com/sl903dj/dwmblocks-async)显示状态栏信息，解决了xsetroot不能以不同频率更新多个命令状态。

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
i3lock主题配置文件fork自[gxt_kt](https://github.com/gxt-kt/dwm/blob/master/i3lock/lock.sh)

## status2d
使用status2d补丁配合xsetroot在statusbar自定义显示系统相关信息，自定义脚本需要赋予755权限
```shell
chmod 755 statusbar.sh
```
