#!/bin/bash

  declare -a arr=("apache" "nginx" "sender")

  for i in "${arr[@]}"
  do
     ansible-playbook ./ansible/playbooks/regular/$i/playbook.yml -i ./ansible/playbooks/regular/$i/hosts.yml
  done