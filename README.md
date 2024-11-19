# CSCI 2200-002 CS Extra Credit
## Description
There are 2 parts to this:
- **Disk Alerter**: Program defined in `main.c` that alerts to
`/var/log/disk_usage_alert.log` when the disk usage exceeds threshold defined
in args.
- **Service**: Effectively defined in `build.sh` and uses cron to run the [Disk
  Alerter] program every 15 minutes with a threshold of 80%.

## Usage
To run the program, first compile it with `gcc main.c -o disk_alert` and then
run `./disk_alert <threshold>`.

## Installation
To install the service, simply run `./build.sh`.

## Debugging
To debug the service, run `gcc -Og -DDEBUG main.c -o disk_alert &&
./disk_alert`. To test the program, run `gcc -Og -DDEBUG -DTEST main.c -o
disk_alert && ./disk_alert`
