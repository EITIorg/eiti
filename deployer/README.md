

### Install ansible on a Enterprise Linux 7 host
```
make bootstrap-el7
```

### Provision a Vagrant VM using the extra vagrant files
```
ansible-playbook --extra-vars="@VagrantSettings.yml" AnsibleMain.yml
# OR:
ansible-playbook --extra-vars="@VagrantSettings.local.yml" AnsibleMain.yml
```

### Provision remote preprod hosts
```
ansible-playbook --inventory="inventory.conf" --extra-vars="hosts=preprod" AnsibleMain.yml
```

### Discover information from systems
see: http://docs.ansible.com/ansible/playbooks_variables.html#information-discovered-from-systems-facts
```
ansible all --inventory inventory.conf -m setup
ansible preprod --inventory inventory.conf -m setup
```
