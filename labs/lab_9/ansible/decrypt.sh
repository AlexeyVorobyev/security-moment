cp -r ./playbooks-encrypted ./playbooks-encrypted-tmp/ && \
ansible-vault decrypt ./playbooks-encrypted/{**/**/*.yml,*.privkey} && \
rm -rf ./playbooks/
mv ./playbooks-encrypted ./playbooks/ && \
cp -r ./playbooks-encrypted-tmp ./playbooks-encrypted/ && \
rm -rf ./playbooks-encrypted-tmp
