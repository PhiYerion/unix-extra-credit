sudo useradd disk_monitor -s /bin/nologin 2>/dev/null
sudo mkdir /usr/src/disk_monitor 2>/dev/null

sudo cp "$(dirname "$0")"/* /usr/src/disk_monitor || exit
sudo chown -R disk_monitor:disk_monitor /usr/src/disk_monitor 2>/dev/null
cd /usr/src/disk_monitor || exit

sudo touch /var/log/disk_monitor.log
sudo chown disk_monitor:disk_monitor /var/log/disk_monitor.log

set -e
sudo -u disk_monitor gcc main.c -o disk_monitor
sudo mv disk_monitor /usr/local/bin
echo "* * * * */15 /usr/local/bin/disk_monitor 0.8" | sudo crontab -u disk_monitor -
