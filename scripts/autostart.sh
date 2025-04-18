#!/bin/bash

dwm_rainbarf() {
	rainstr=$(rainbarf)
	r1=$(echo $rainstr | cut -d] -f2 | cut -d'#' -f1)
	r2=$(echo $rainstr | cut -d] -f3 | cut -d'#' -f1)
	r3=$(echo $rainstr | cut -d] -f4 | cut -d'#' -f1)
	r4=$(echo $rainstr | cut -d] -f5 | cut -d'#' -f1)
	r5=$(echo $rainstr | cut -d] -f6 | cut -d'#' -f1)
	echo "x4"$r1"x5"$r2"x6"$r3"x7"$r4"x8"$r5"x1"
}

# Prints out the CPU load percentage
dwm_cpuload()
{
  # Get the first line with aggregate of all CPUs
  cpu_last=($(head -n1 /proc/stat))
  cpu_last_sum="${cpu_last[@]:1}"
  cpu_last_sum=$((${cpu_last_sum// /+}))

  sleep 0.05

  cpu_now=($(head -n1 /proc/stat))
  cpu_sum="${cpu_now[@]:1}"
  cpu_sum=$((${cpu_sum// /+}))

  cpu_delta=$((cpu_sum - cpu_last_sum))
  cpu_idle=$((cpu_now[4]- cpu_last[4]))
  cpu_used=$((cpu_delta - cpu_idle))
  cpu_usage=$((100 * cpu_used / cpu_delta))

  # Keep this as last for our next read
  cpu_last=("${cpu_now[@]}")
  cpu_last_sum=$cpu_sum

  # echo "  $cpu_usage%"
  echo "CPU $cpu_usage%"
}

# Prints the total ram and used ram in Mb
dwm_ram()
{
    TOTAL_RAM=$(free -mh --si | awk  {'print $2'} | head -n 2 | tail -1)
    USED_RAM=$(free -mh --si | awk  {'print $3'} | head -n 2 | tail -1)
    MB="MB"

    echo "   MEM $USED_RAM/$TOTAL_RAM"
}

# Prints out the volume percentage
dwm_volume(){
    volume="$(amixer get Master | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')"
    if test "$volume" -gt 0
    then
        echo "  $volume%"
    else
        echo " $volume%"
    fi
}

dwm_date () {
	printf "  %s   %s" "$(date +%Y.%m.%d)" "$(date +%H:%M)"
}

while true; do
  xsetroot -name "$(dwm_rainbarf)  $(dwm_ram)  $(dwm_cpuload)  $(dwm_volume)  $(dwm_date)"
  sleep 0.2
done

