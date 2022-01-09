#!/bin/bash
# https://stackoverflow.com/questions/27599839/how-to-wait-for-an-open-port-with-netcat
# https://stackoverflow.com/questions/29627936/create-a-new-file-each-time-through-a-bash-for-loop
i=0

while true
do
  if ! nc -z localhost 8000 
  then 
    echo "Waiting..."
  else
    metrics=$(curl http://localhost:8000/)
	  if [ ! -z "$metrics" ] 
    then
      echo "$metrics" > "./files/$((i++)).txt"
      # sleep 2s --> merge_sort
      sleep 2s
    fi  
  fi
done
