#!/bin/bash

## The good way to do set the date is using ntp date and chrony, but sometimes the ports used by 
## NTP servers (13 I think) is blocked by the service provider and this way always work because 
## it uses the http port

date -s "$(curl -s --head http://google.com | grep ^Date: | sed 's/Date: //g')"
