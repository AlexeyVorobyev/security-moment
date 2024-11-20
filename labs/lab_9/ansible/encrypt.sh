cp -r ./playbooks ./playbooks-tmp/ && \
ansible-vault encrypt ./playbooks/{**/**/*.yml,*.privkey} && \
rm -rf ./playbooks-encrypted/
mv ./playbooks ./playbooks-encrypted/ && \
cp -r ./playbooks-tmp ./playbooks/ && \
rm -rf ./playbooks-tmp
