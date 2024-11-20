#!/bin/bash

  declare -a arr=("docker")

  for i in "${arr[@]}"
  do
     ansible-playbook ./ansible/playbooks/$i/playbook.yml -i ./ansible/playbooks/$i/hosts.yml
  done