#!/bin/bash

  declare -a arr=("nginx")

  for i in "${arr[@]}"
  do
     ansible-playbook ./ansible/playbooks/first/$i/playbook.yml -i ./ansible/playbooks/first/$i/hosts.yml
  done