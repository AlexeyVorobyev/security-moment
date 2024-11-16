cp ./vars.tfvars ./vars.tmp.tfvars && \
ansible-vault encrypt ./vars.tfvars && \
rm -rf ./vars.encrypted.tfvars
mv ./vars.tfvars  ./vars.encrypted.tfvars && \
cp ./vars.tmp.tfvars ./vars.tfvars && \
rm -rf ./vars.tmp.tfvars
