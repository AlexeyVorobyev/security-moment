#!/bin/bash

#  declare -a arr=("apache" "nginx" "nginx-lb-1" "nginx-lb-2" "sender")
  declare -a arr=("nginx-lb-2")


  for i in "${arr[@]}"
  do
     ansible-playbook ./ansible/playbooks/lb/$i/playbook.yml -i ./ansible/playbooks/lb/$i/hosts.yml
  done