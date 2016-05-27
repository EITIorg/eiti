
# EITI User Documentation:

## Updating EITI production to the latest codebase.

```
cd /var/www/eiti-production/public_html/
git fetch --all --prune
git pull
make update
cd /var/www/eiti-production/
make fix-permissions
```
