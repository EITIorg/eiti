
## Avoid conflicts with files of the same name
## @see: http://www.gnu.org/savannah-checkouts/gnu/make/manual/html_node/Phony-Targets.html
.PHONY: dummy bootstrap provision


## Set environment to local if it has not been provided.
ENVIRONMENT?=local

## Provision the current host if one has not been provided.
HOSTS?=localhost

## By default provision Using the AnsibleMain.yml playbook.
PLAYBOOK?=AnsibleMain.yml


## The default target, if no target argument is provided to `make`.
## Update an environment with the latest changes from code.
dummy:
	@echo 'Here is a list of available commands:'
	@grep -iE "^[a-z_-]+:" $(lastword $(MAKEFILE_LIST)) | cut -d: -f1 | grep -v dummy | xargs -i{} echo "  $$ make {}"


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
	@test -e 'inventory.conf' && ( \
			echo 'Using local inventory.conf' && \
			ansible-playbook -vvv --inventory="inventory.conf" --extra-vars="project_environment=${ENVIRONMENT} hosts=${HOSTS}" ${PLAYBOOK} \
		) || true
	@test ! -e 'inventory.conf' && ( \
			echo 'Using default inventory' && \
			ansible-playbook -vvv  --extra-vars="{project_environment: ${ENVIRONMENT}}" ${PLAYBOOK} \
		) || true


## Provision the localhost using Ansible Playbooks.
provision-vagrant:
	@echo 'Provisioning the localhost using Ansible Playbooks:'
	@test -e 'VagrantSettings.local.yml' && ( \
			echo 'Using VagrantSettings.local.yml' && \
			ansible-playbook --extra-vars "@VagrantSettings.local.yml" -b ${PLAYBOOK} \
		) || true
	@test ! -e 'VagrantSettings.local.yml' && ( \
			echo 'Using ../VagrantSettings.yml' && \
			ansible-playbook --extra-vars "@VagrantSettings.yml" -b ${PLAYBOOK} \
		) || true