cp ./vars.encrypted.tfvars ./vars.tmp.tfvars && \
ansible-vault decrypt ./vars.encrypted.tfvars && \
rm -rf ./vars.tfvars
mv ./vars.encrypted.tfvars ./vars.tfvars && \
cp ./vars.tmp.tfvars ./vars.encrypted.tfvars && \
rm -rf ./vars.tmp.tfvars
