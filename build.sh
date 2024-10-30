gcc main.c -o disk_monitor
sudo cp disk_monitor /usr/local/bin
echo "*/15 * * * * /usr/local/bin/disk_monitor 0.8" | sudo crontab -
