#!/bin/bash

dwm_lunar () {
    printf "%s" "$SEP1"
    printf "%s" "$(lunar-date | awk -F '年' 'NR == 2 {print $2}')"
    printf "%s\n" "$SEP2"
}

dwm_date () {
    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "📆 %s" "$(date +"%d-%m-%y %a %H:%M")"
    else
        printf "󰃭 %s" "$(date +"%m/%d %a 󰥔 %H:%M")"
    fi
    printf "%s\n" "$SEP2"
}

dwm_network () {
    CONNAME=$(nmcli -a | grep 'wlp0s20f3' | awk 'NR==1{print $3}')
    if [ "$CONNAME" = "" ]; then
        CONNAME=$(nmcli -t -f active,ssid dev wifi | grep '^yes' | cut -c 5-)
    fi

    PRIVATE=$(nmcli -a | grep 'inet4 192' | awk '{print $2}')
    PUBLIC=$(curl -u bd76e54350f0ef: ipinfo.io | grep '"ip' | awk -F '\"' '{print $4}')
    CITY=$(curl -u bd76e54350f0ef: ipinfo.io | grep '"city' | awk -F '\"' '{print $4}')
    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "🌐 %s %s | %s" "$CONNAME" "$PRIVATE" "$PUBLIC"
    else
        printf "󰩟 %s|%s" "$PUBLIC" "$CITY"
    fi
    printf "%s\n" "$SEP2"
}

dwm_battery () {
    # Change BAT1 to whatever your battery is identified as. Typically BAT0 or BAT1
    CAPACITY=$(cat /sys/class/power_supply/BAT0/capacity)
    STATUS=$(cat /sys/class/power_supply/BAT0/status)
    # full Not charging Discharging
    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        if [ "$STATUS" = "Not charging" ]; then
            printf "🔌 %s%% %s" "$CAPACITY" #"$STATUS"
        else
            printf "🔋 %s%% %s" "$CAPACITY" #"$STATUS"
        fi
    else
        if [ "$STATUS" = "Discharging" ]; then
            if [ "$CAPACITY" -eq 100 ]; then
                printf "󰁹 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 90 ] && [ "$CAPACITY" -le 100 ]; then
                printf "󰂂 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 80 ] && [ "$CAPACITY" -le 90 ]; then
                printf "󰂁 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 70 ] && [ "$CAPACITY" -le 80 ]; then
                printf "󰂀 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 60 ] && [ "$CAPACITY" -le 70 ]; then
                printf "󰁿 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 50 ] && [ "$CAPACITY" -le 60 ]; then
                printf "󰁾 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 40 ] && [ "$CAPACITY" -le 50 ]; then
                printf "󰁽 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 30 ] && [ "$CAPACITY" -le 40 ]; then
                printf "󰁼 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 20 ] && [ "$CAPACITY" -le 30 ]; then
                printf "󰁻 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 10 ] && [ "$CAPACITY" -le 20 ]; then
                printf "󰁺 %s%%" "$CAPACITY" #"$STATUS"
            else
                printf "󱉞 %s%%" "$CAPACITY" #"$STATUS"
                notify-send "没电了，赶紧充电啊！！！"
	    fi
        elif [ "$STATUS" = "Not charging" ]; then
            printf "󱐤 %s%%" "$CAPACITY" #"$STATUS"
        elif [ "$STATUS" = "Charging" ]; then
            if [ "$CAPACITY" -le 10 ]; then
                printf "󰢟 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 10 ] && [ "$CAPACITY" -le 20 ]; then
                printf "󰢜 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 20 ] && [ "$CAPACITY" -le 30 ]; then
                printf "󰂆 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 30 ] && [ "$CAPACITY" -le 40 ]; then
                printf "󰂇 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 40 ] && [ "$CAPACITY" -le 50 ]; then
                printf "󰂈 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 50 ] && [ "$CAPACITY" -le 60 ]; then
                printf "󰢝 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 60 ] && [ "$CAPACITY" -le 70 ]; then
                printf "󰂉 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 70 ] && [ "$CAPACITY" -le 80 ]; then
                printf "󰢞 %s%%" "$CAPACITY" #"$STATUS"
            elif [ "$CAPACITY" -gt 80 ] && [ "$CAPACITY" -le 90 ]; then
                printf "󰂊 %s%%" "$CAPACITY" #"$STATUS"
            else
                printf "󰂋 %s%%" "$CAPACITY" #"$STATUS"
            fi
        else
            printf "󰂅 %s%%" "$CAPACITY" #"$STATUS"
        fi
    fi
    printf "%s\n" "$SEP2"
}

dwm_alsa () {
    VOL=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
    VOLMUTE=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)\].*/\1/")
    printf "%s" "$SEP1"
    if [ "$VOLMUTE" = "off" ]; then
	printf "󰝟 %s%%" "$VOL"
    elif [ "$VOL" -eq 0 ]; then
        printf "󰕿"
    elif [ "$VOL" -gt 0 ] && [ "$VOL" -le 33 ]; then
        printf "󰖀 %s%%" "$VOL"
    elif [ "$VOL" -gt 33 ] && [ "$VOL" -le 66 ]; then
        printf "󰕾 %s%%" "$VOL"
    else
        printf "󱄡 %s%%" "$VOL"
    fi
    printf "%s\n" "$SEP2"
}

dwm_cpu(){
    read cpu a b c previdle rest < /proc/stat
    prevtotal=$((a+b+c+previdle))
    sleep 0.5
    read cpu a b c idle rest < /proc/stat
    total=$((a+b+c+idle))
    cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
    echo -e "󰻠 $cpu%"
}

dwm_mem(){
    mem_total=$(cat /proc/meminfo | grep "MemTotal:"| awk '{print $2}')
    mem_free=$(cat /proc/meminfo | grep "MemFree:"| awk '{print $2}')
    mem_buffers=$(cat /proc/meminfo | grep "Buffers:"| awk '{print $2}')
    mem_cached=$(cat /proc/meminfo | grep -w "Cached:"| awk '{print $2}')
    men_usage_rate=$(((mem_total - mem_free - mem_buffers - mem_cached) * 100 / mem_total))
    mem_text=$(echo $men_usage_rate | awk '{printf "%d%", $1}')
    echo -e "󰍛 $mem_text"
}

dwm_disk () {
    disk_free=$(df -hl | awk 'NR==5{print $4}')
    echo -e " $disk_free"
}
# 

black="#1e222a"
white="#D8DEE9"
grey="#373d49"
blue="#81A1C1"
blue2="#5E81AC"
blue3="#88C0D0"
blue4="#8FBCBB"
red="#d47d85"
green="#A3BE8C"
pink="#B48EAD"
yellow="#EBCB8B"
orange="#D08770"
darkblue="#7292b2"

while true; do
	xsetroot -name "^c$black^^b$blue^ 󰤼: ^b$green^ $(dwm_mem) $(dwm_cpu) $(dwm_disk) ^b$pink^^c$black^ $(dwm_alsa) $(dwm_battery) ^c$black^^b$green^ $(dwm_date) $(dwm_lunar) ^b#81A1C1^"
	sleep 1
done
