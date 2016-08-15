
## Avoid conflicts with files of the same name
## @see: http://www.gnu.org/savannah-checkouts/gnu/make/manual/html_node/Phony-Targets.html
.PHONY: dummy bootstrap-el7 provision provision-vagrant


## Set environment to local if it has not been provided.
ENVIRONMENT?=local

## Provision the devel hosts group if one has not been provided.
HOSTS?=devel

## By default provision Using the AnsibleMain.yml playbook.
PLAYBOOK?=AnsibleMain.yml

## By default use the vagrant specific inventory.
INVENTORY?="/vagrant/inventory.vagrant.conf"


## The default target, if no target argument is provided to `make`.
## Update an environment with the latest changes from code.
dummy:
	@echo 'Here is a list of available commands:'
	@grep -iE "^[a-z0-9_-]+:" $(lastword $(MAKEFILE_LIST)) | cut -d: -f1 | grep -v dummy | xargs -i{} echo "  $$ make {}"


## Bootstrap Ansible on a local EL7 machine.
bootstrap-el7:
	@echo 'Bootstrapping Ansible:'
	@echo 'Installing the EPEL repository.'
	@rpm --quiet --force -Uh https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
	@gpg --import /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7
	@echo 'Install Ansible from EPEL.'
	@yum -y install ansible
	@echo 'Update Ansible configuration.'
	@sudo mkdir -p /etc/ansible/
	@sudo cp inventory.sample.conf /etc/ansible/hosts


## Provision environment using Ansible Playbooks.
provision:
	@echo 'Provisioning the localhost using Ansible Playbooks:'
	@ansible-playbook -v --inventory="${INVENTORY}" --extra-vars="project_environment=${ENVIRONMENT} hosts=${HOSTS}" ${PLAYBOOK}


## Provision the localhost using Ansible Playbooks.
provision-vagrant:
	@echo 'Provisioning the local Vagrant VM using Ansible Playbooks:'
	@test -e 'VagrantSettings.local.yml' && ( \
			echo 'Using VagrantSettings.local.yml' && \
			ansible-playbook -v --inventory="${INVENTORY}" --extra-vars="project_environment=${ENVIRONMENT} hosts=${HOSTS}" --extra-vars="@VagrantSettings.local.yml" ${PLAYBOOK} \
		) || true
	@test ! -e 'VagrantSettings.local.yml' && ( \
			echo 'Using VagrantSettings.yml' && \
			ansible-playbook -v --inventory="${INVENTORY}" --extra-vars="project_environment=${ENVIRONMENT} hosts=${HOSTS}" --extra-vars="@VagrantSettings.yml"  ${PLAYBOOK} \
		) || true
